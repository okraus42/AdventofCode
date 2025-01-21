#!/usr/bin/python3

import itertools

FILE_NAME = 'input.txt'

def get_sum(containers, uses):
	sum = 0
	for c, u in zip(containers, uses):
		if u:
			sum += c
	return sum

def count_bits(uses):
	bits = 0
	for u in uses:
		if u:
			bits += 1
	return bits

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
min = 20
for n in range(1048576):
	uses = [bit == '1' for bit in bin(n)[2:].zfill(20)]
	if get_sum(containers, uses) == 150:
		if count_bits(uses) < min:
			min = count_bits(uses)
			result = 0
		if count_bits(uses) == min:
			result += 1
print(result)
