#!/usr/bin/python3

import itertools

FILE_NAME = 'input.txt'

def get_sum(containers, uses):
	sum = 0
	for c, u in zip(containers, uses):
		if u:
			sum += c
	return sum

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = file.readlines()

# Initialize variables
containers = []
uses = []

# Parse ingredients from the file
for line in lines:
	containers.append(int(line))
	uses.append(False)
containers.sort(reverse=True)
# Initialize scores
result = 0

for n in range(1048576):
	uses = [bit == '1' for bit in bin(n)[2:].zfill(20)]
	if get_sum(containers, uses) == 150:
		result += 1
print(result)
