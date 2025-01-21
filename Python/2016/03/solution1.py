#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()

result = 0
x = 0
y = 0
houses = set()
houses.add((0, 0))
# Now, 'content' contains the file's content as a string
for char in content:
	if char == '^':
		y -= 1
	elif char == 'v':
		y += 1
	elif char == '<':
		x -= 1
	elif char == '>':
		x += 1
	houses.add((x, y))
print(len(houses))