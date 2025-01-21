#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()

i = 0
x1 = 0
y1 = 0
x2 = 0
y2 = 0
houses = set()
houses.add((0, 0))
# Now, 'content' contains the file's content as a string
for char in content:
	if i % 2:
		if char == '^':
			y1 -= 1
		elif char == 'v':
			y1 += 1
		elif char == '<':
			x1 -= 1
		elif char == '>':
			x1 += 1
		houses.add((x1, y1))
	else:
		if char == '^':
			y2 -= 1
		elif char == 'v':
			y2 += 1
		elif char == '<':
			x2 -= 1
		elif char == '>':
			x2 += 1
		houses.add((x2, y2))
	i += 1
	
print(len(houses))