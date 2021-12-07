#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <string>
#include <vector>

using AdvanceHeapFunc = uintptr_t (*)(uintptr_t);

extern "C" {
void *alloc_mem(size_t cnt);
extern AdvanceHeapFunc advance_heap_to_func;
}

struct FakeBrk {
  size_t max_allocation;
  uintptr_t cur;
  void *begin;
};

static FakeBrk fake_brk;

static uintptr_t AdvanceHeapToHook(uintptr_t addr) {
  if (addr == 0) {
    return fake_brk.cur;
  }
  assert(addr >= fake_brk.cur);
  if (addr - fake_brk.cur > fake_brk.max_allocation) {
    return fake_brk.cur;
  }
  fake_brk.cur = addr;
  return addr;
}

struct FreelistNodeHeader {
  size_t size;
  FreelistNodeHeader *next;
};

static FreelistNodeHeader *MakeNode(size_t size) {
  assert(size >= 8);
  auto p = (FreelistNodeHeader *)malloc(size);
  new (p) FreelistNodeHeader;
  p->size = size - 4;
  return p;
}

static std::vector<FreelistNodeHeader *> freelist_items;
FreelistNodeHeader *freelist;

static void SetupFreelist(std::vector<size_t> const &raw_blocks) {
  freelist = nullptr;
  std::vector<size_t> blocks = raw_blocks;
  std::reverse(blocks.begin(), blocks.end());
  for (size_t s : blocks) {
    FreelistNodeHeader *v = MakeNode(s);
    freelist_items.push_back(v);
    v->next = freelist;
    freelist = v;
  }
  std::reverse(freelist_items.begin(), freelist_items.end());
}

static size_t GetFreeListSize() {
  FreelistNodeHeader *p = freelist;
  size_t cnt = 0;
  while (p) {
    {
      auto it = std::find(freelist_items.begin(), freelist_items.end(), p);
      assert(it != freelist_items.end());
    }
    ++cnt;
    FreelistNodeHeader *v = p->next;
    p = v;
  }
  return cnt;
}

static void FreeFreelist() {
  while (freelist) {
    {
      auto it =
          std::find(freelist_items.begin(), freelist_items.end(), freelist);
      assert(it != freelist_items.end());
      freelist_items.erase(it);
    }
    FreelistNodeHeader *v = freelist->next;
    freelist->~FreelistNodeHeader();
    free(freelist);
    freelist = v;
  }
}

class Target {
  enum class Kind { Freelist, Offset, Null };
  size_t mFreelist;
  Kind mKind;

public:
  static Target Freelist(size_t idx) {
    Target t;
    t.mFreelist = idx;
    t.mKind = Kind::Freelist;
    return t;
  }
  static Target Address() {
    Target t;
    t.mKind = Kind::Offset;
    return t;
  }
  static Target Null() {
    Target t;
    t.mKind = Kind::Null;
    return t;
  }
  bool IsFreelist() const { return mKind == Kind::Freelist; }

  void *Get() const {
    if (mKind == Kind::Null) {
      return nullptr;
    }
    if (mKind == Kind::Offset) {
      return (void *)(fake_brk.cur + 4);
    }
    return (char *)(freelist_items[mFreelist]) + 4;
  }
};

struct TestCase {
  std::vector<size_t> initial;
  size_t max_brk_allocation;
  std::vector<size_t> requests;
  std::vector<Target> expected;
  std::string name = "";
};

static void RunTest(TestCase const &tc) {
  assert(!tc.name.empty());
  fprintf(stderr, "Running test case %s\n", tc.name.c_str());
  assert(tc.requests.size() == tc.expected.size());
  SetupFreelist(tc.initial);
  static void *virtual_brk_buf = nullptr;
  if (virtual_brk_buf == nullptr) {
    virtual_brk_buf = malloc(256 * 1024 * 1024);
  }
  fake_brk.begin = virtual_brk_buf;
  fake_brk.cur = (uintptr_t)virtual_brk_buf;
  fake_brk.max_allocation = tc.max_brk_allocation;
  size_t freelist_len = tc.initial.size();
  for (size_t i = 0; i < tc.requests.size(); ++i) {
    void *old_brk = (void *)fake_brk.cur;
    void *expected = tc.expected[i].Get();
    void *res;
    {
      __int64_t x = 0xbebebebebebebebe;
      __int64_t y = 0xbfbfbfbfbfbfbfbf;
      res = alloc_mem(tc.requests[i]);
      assert(x == 0xbebebebebebebebe);
      assert(y == 0xbfbfbfbfbfbfbfbf);
    }
    assert(res == expected);
    if (res) {
      size_t sz = *((size_t *)(res)-1);
      assert(sz >= tc.requests[i]);
    }
    if (tc.expected[i].IsFreelist() || !res) {
      assert(fake_brk.cur == (uintptr_t)(old_brk));
    }
    if (tc.expected[i].IsFreelist()) {
      --freelist_len;
    } else if (res) {
      size_t sz = *((size_t *)(res)-1);
      size_t actual =
          std::max<size_t>(4, tc.requests[i] + ((4 - tc.requests[i]) % 4));
      assert(sz == actual);
      assert(fake_brk.cur == (uintptr_t)old_brk + sz + 4);
    }
    size_t actual_freelist_len = GetFreeListSize();
    assert(actual_freelist_len == freelist_len);
  }
  FreeFreelist();
}

void SimpleNativeBreak() {
  alloc_mem(0);
  alloc_mem(0);
  char *p1 = (char *)alloc_mem(16);
  assert(*(int *)(p1 - 4) == 16);
  char *p2 = (char *)alloc_mem(93);
  assert(*(int *)(p2 - 4) == 96);
  char *p3 = (char *)alloc_mem(5);
  assert(*(int *)(p3 - 4) == 8);
  for (size_t i = 0; i < 16; ++i) {
    p1[i] = 1;
  }
  for (size_t i = 0; i < 93; ++i) {
    p2[i] = 2;
  }
  for (size_t i = 0; i < 5; ++i) {
    p3[i] = 3;
  }
  for (size_t i = 0; i < 16; ++i) {
    assert(p1[i] == 1);
  }
  for (size_t i = 0; i < 93; ++i) {
    assert(p2[i] == 2);
  }
  for (size_t i = 0; i < 5; ++i) {
    assert(p3[i] == 3);
  }
}

int main(int argc, char **argv) {
  if (argc > 1) {
    fprintf(stderr, "running tests with a native brk()\n");
    SimpleNativeBreak();
    return 0;
  }
  advance_heap_to_func = AdvanceHeapToHook;
  RunTest(TestCase{
      .initial = {},
      .max_brk_allocation = 4096,
      .requests = {4, 16, 32},
      .expected = {Target::Address(), Target::Address(), Target::Address()},
      .name = "SimpleBrk"});

  char const *s = "BrkAlignAndOom";
  RunTest(TestCase{.initial = {},
                   .max_brk_allocation = 35,
                   .requests = {28, 29},
                   .expected = {Target::Address(), Target::Null()},
                   .name = s});

  RunTest(TestCase{.initial = {31, 32, 16},
                   .max_brk_allocation = 0,
                   .requests = {4, 12, 28, 12},
                   .expected = {Target::Freelist(0), Target::Freelist(1),
                                Target::Null(), Target::Freelist(2)},
                   .name = "FreelistSimple"});

  RunTest(TestCase{.initial = {8, 32, 16},
                   .max_brk_allocation = 16,
                   .requests = {4, 12, 12, 12, 12, 12},
                   .expected = {Target::Freelist(0), Target::Freelist(1),
                                Target::Freelist(2), Target::Address(),
                                Target::Address(), Target::Address()},
                   .name = "FreelistFallback"});
  RunTest(TestCase{.initial = {128},
                   .max_brk_allocation = SIZE_MAX,
                   .requests = {0xfffffff9, 0xfffffff8},
                   .expected = {Target::Null(), Target::Null()},
                   .name = "HugeAllocation"});

  RunTest(TestCase{.initial = {8, 32, 16},
                   .max_brk_allocation = 32,
                   .requests = {4, 12, 28, 12, 32},
                   .expected = {Target::Freelist(0), Target::Freelist(1),
                                Target::Address(), Target::Freelist(2),
                                Target::Null()},
                   .name = "Simple"});

  RunTest(TestCase{.initial = {},
                   .max_brk_allocation = 32,
                   .requests = {8, 32, 8, 29, 8, 28},
                   .expected = {Target::Address(), Target::Null(),
                                Target::Address(), Target::Null(),
                                Target::Address(), Target::Address()},
                   .name = "GracefulOom"});

  RunTest(TestCase{.initial = {8, 8, 8, 8},
                   .max_brk_allocation = 0,
                   .requests = {0, 1, 2, 3},
                   .expected = {Target::Freelist(0), Target::Freelist(1),
                                Target::Freelist(2), Target::Freelist(3)},
                   .name = "SmallFreelist"});
  RunTest(TestCase{.initial = {},
                   .max_brk_allocation = 8,
                   .requests = {0, 1, 2, 3},
                   .expected = {Target::Address(), Target::Address(),
                                Target::Address(), Target::Address()},
                   .name = "SmallBrk"});

  printf("ok\n");
  return 0;
}