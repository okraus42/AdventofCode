#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()

result = 0
floor = 0
# Now, 'content' contains the file's content as a string
for char in content:
	result += 1
	if char == '(':
		floor += 1
	if char == ')':
		floor -= 1
	if (floor == -1):
		print(result)
		break