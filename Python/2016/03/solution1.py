#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

result = 0
for line in lines:
	sides = sorted(list(map(int, line.split())))
	if (sides[0] + sides[1] > sides[2]):
		result += 1
print(result)