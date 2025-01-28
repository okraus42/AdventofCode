#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

result = 0
matrix = [list(map(int, line.split())) for line in lines]
rows = len(matrix)
columns = len(matrix[0])
for x in range(columns):
	y = 0
	while y != rows:
		if y == rows:
			y = 0
		num1 = matrix[y][x]
		num2 = matrix[y + 1][x]
		num3 = matrix[y + 2][x]
		y += 3
		sides = sorted([num1, num2, num3])
		if (sides[0] + sides[1] > sides[2]):
			result += 1
print(result)