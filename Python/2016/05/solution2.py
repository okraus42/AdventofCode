#!/usr/bin/python3

import math
import sys
import hashlib

FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()

extra = 0
test = ['.', '.', '.', '.', '.', '.', '.', '.']
while True:
	md5_hash = hashlib.md5((content + str(extra)).encode()).hexdigest()
	if md5_hash[:5] == '00000' and md5_hash[5] in "01234567":
		pos = int(md5_hash[5])
		if test[pos] == '.':
			test[pos] = md5_hash[6]
	if '.' not in test:
		break
	extra += 1
result = ''.join(test)
print(result)