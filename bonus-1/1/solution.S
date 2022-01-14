    .global rop
rop:
    pushl $str2
    pushl $f1 + 1
    pushl $str1
    pushl $f1 + 1
    ret