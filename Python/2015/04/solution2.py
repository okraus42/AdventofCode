#!/usr/bin/python3

import math
import sys
import hashlib

FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()

result = 0

while True:
	md5_hash = hashlib.md5((content + str(result)).encode()).hexdigest()
	if md5_hash[:6] == '000000':
		break
	result += 1
print(result)