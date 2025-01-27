#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()
numpad = 	[
				[' ', ' ', ' ', ' ', ' ', ' ', ' '],
				[' ', ' ', ' ', '1', ' ', ' ', ' '],
				[' ', ' ', '2', '3', '4', ' ', ' '],
				[' ', '5', '6', '7', '8', '9', ' '],
				[' ', ' ', 'A', 'B', 'C', ' ', ' '],
				[' ', ' ', ' ', 'D', ' ', ' ', ' '],
				[' ', ' ', ' ', ' ', ' ', ' ', ' ']
			]
y = 3
x = 3
result = ''
for line in lines:
	for char in line:
		if char == 'D' and numpad[y + 1][x] != ' ':
			y += 1
		elif char == 'U' and numpad[y - 1][x] != ' ':
			y -= 1
		elif char == 'R' and numpad[y][x + 1] != ' ':
			x += 1
		elif char == 'L' and numpad[y][x - 1] != ' ':
			x -= 1
	result += numpad[y][x]
# need to update
print(result)