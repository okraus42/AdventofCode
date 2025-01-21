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
	pairs = False
	doubles = False
	for i in range(len(line)):
		if i > 1:
			if line[i] == line[i - 2]:
				doubles = True
			pair = str(line[i - 2]) + str(line[i - 1])
			if (not pairs):
				pairs = pair in line[i:]
	if (doubles and pairs):
		result += 1
print(result)