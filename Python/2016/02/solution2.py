#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

result = 0
# Now, 'content' contains the file's content as a string
for line in lines:
	numbers = line.split('x')
	a, b, c = map(int, numbers)
	a, b, c = sorted([a, b, c])
	result += 2*a + 2*b + a*b*c
print(result)