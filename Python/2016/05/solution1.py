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
result = ''
while True:
	md5_hash = hashlib.md5((content + str(extra)).encode()).hexdigest()
	if md5_hash[:5] == '00000':
		result += md5_hash[5]
	if (len(result) == 8):
		break
	extra += 1
print(result)