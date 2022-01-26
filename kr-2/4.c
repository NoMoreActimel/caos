#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    char* token;
    size_t sz;
    struct Node* next;
} Node_t;

void freeList(Node_t* node) {
    if (!node) {
        return;
    }

    if (node->next) {
        freeList(node->next);
    }

    free(node->token);
    free(node);
}

bool is_digit(const char* c) {
	return (*c >= 48) && (*c <= 57);
}

Node_t* get_next_token(char** v) {
	if (**v == '\0') {
		return NULL;
	}

	char* start = *v;
	while (*start != '\0' && !is_digit(start)) {
		++start;
	}

	if (*start == '\0') {
		return NULL;
	}

	if (*start == '0') {
		while (*start != '\0' && *start == '0') {
			++start;
		}
		if (!is_digit(start)) {
			--start;
		}
	}

	char* end = start;

	while (*end != '\0' && is_digit(end)) {
		++end;
	}

	Node_t* token_node = malloc(sizeof(Node_t));
	if (token_node == NULL) {
		return NULL;
	}

	token_node->next = NULL;
	token_node->token = malloc((end - start) * sizeof(char));
	if (token_node->token == NULL) {
		return NULL;
	}
	token_node->sz = end - start;

	for (size_t i = 0; i != end - start; ++i) {
		token_node->token[i] = *(start + i);
	}

	*v = end;
	return token_node;
}

Node_t* get_tokens(const char* v) {
	char* cur = (char*)v;

	Node_t* head_token_node = get_next_token(&cur);
	if (!head_token_node) {
		return NULL;
	}
	Node_t* cur_token_node = head_token_node;

	while ((cur_token_node->next = get_next_token(&cur))) {
		cur_token_node = cur_token_node->next;
	}

	return head_token_node;
}

int token_cmp(Node_t* token1, Node_t* token2) {
	if (token1->sz < token2->sz) {
		return -1;
	} else if (token1->sz > token2->sz) {
		return 1;
	}

	size_t sz = token1->sz;
	for (size_t i = 0; i != sz; ++i) {
		if (token1->token[i] < token2->token[i]) {
			return -1;
		} else if (token1->token[i] > token2->token[i]) {
			return 1;
		}
	}

	return 0;
}

int vercmp(const char* v1, const char* v2) {
	Node_t* v1_tokens_head = get_tokens(v1);
	Node_t* v2_tokens_head = get_tokens(v2);

	Node_t* token1 = v1_tokens_head;
	Node_t* token2 = v2_tokens_head;

	int ans = 0;
	while (token1 && token2) {
		int sign = token_cmp(token1, token2);
		if (sign) {
			ans = sign;
			break;
		} else {
			token1 = token1->next;
			token2 = token2->next;
		}
	}

	if (!token1 && token2) {
		ans = -1;
	} else if (token1 && !token2) {
		ans = 1;
	}

	freeList(v1_tokens_head);
	freeList(v2_tokens_head);
	return ans;
}
