#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

disallowed = ["ab", "cd", "pq", "xy"]
vowels = "aeiou"
result = 0
# Now, 'content' contains the file's content as a string
for line in lines:
	v = 0
	doubles = False
	for i in range(len(line)):
		if i > 0:
			if line[i] == line[i - 1]:
				doubles = True
		if line[i] in vowels:
			v += 1
	if (v >= 3 and doubles and not any(substring in line for substring in disallowed)):
		result += 1
print(result)