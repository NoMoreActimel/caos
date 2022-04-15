#!/usr/bin/python3
import os
from functools import reduceA = list(map(int, input().split()))print(1)
print(reduce((lambda x, y: x * y), A))
os.remove('my.py')
