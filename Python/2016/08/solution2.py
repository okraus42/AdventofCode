#!/usr/bin/python3

import math
import sys
import functools
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

lights = [[False] * 1000 for _ in range(1000)]
result = 0
real_chars = 0
printed_chars = 0
# Now, 'content' contains the file's content as a string
for line in lines:
	position = 0
	real_chars += 2
	while position < len(line) - 1:
		character = line[position]
		print(character)
		if character == '\"':
			real_chars += 2
		elif character == '\\':
			real_chars += 2
		else:
			real_chars += 1
		printed_chars += 1
		position += 1

result = real_chars - printed_chars
print(result)