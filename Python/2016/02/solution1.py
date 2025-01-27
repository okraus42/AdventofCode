#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()
numpad = [	[1, 2, 3],
			[4, 5, 6],
			[7, 8, 9]]
y = 1
x = 1
result = 0
for line in lines:
	for char in line:
		if char == 'D' and y < 2:
			y += 1
		elif char == 'U' and y > 0:
			y -= 1
		elif char == 'R' and x < 2:
			x += 1
		elif char == 'L' and x > 0:
			x -= 1
	result *= 10
	result += numpad[y][x]
# need to update
print(result)