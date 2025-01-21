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
	s1 = a*b
	s2 = a*c
	s3 = b*c
	result += 2*s1 + 2*s2 + 2*s3 + min(s1,s2,s3)
print(result)