#!/usr/bin/python3

from itertools import combinations
from math import prod

def find_best_group(packages, num_groups):
	target_weight = sum(packages) // num_groups
	
	for group_size in range(1, len(packages)):
		valid_groups = []
		
		for group in combinations(packages, group_size):
			if sum(group) == target_weight:
				valid_groups.append(group)
		
		if valid_groups:
			min_qe = float('inf')
			for group in valid_groups:
				qe = prod(group)
				if qe < min_qe:
					min_qe = qe
			return min_qe
	
	return None

FILE_NAME = 'input.txt'

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = [line.strip() for line in file.readlines()]

index = 0
total = 0
packages = []

# Parse instructions from the file
for line in lines:
	package = int(line)
	total += package
	packages.append(package)
groups = 3
result = find_best_group(packages, groups)
print(result)