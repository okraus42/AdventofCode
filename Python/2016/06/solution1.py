#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

lights = [[False] * 1000 for _ in range(1000)]
result = ''
# Now, 'content' contains the file's content as a string
counts = [
	{},
	{},
	{},
	{},
	{},
	{},
	{},
	{}
]
for line in lines:
	line = line.strip()
	for index, char in enumerate(line):
		if char in counts[index]:
			counts[index][char] += 1
		else:
			counts[index][char] = 1
for c in counts:
	result += max(c, key=c.get)
print(result)