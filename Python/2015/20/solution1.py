#!/usr/bin/python3

def factors_sieve(limit):
	factors = [[] for _ in range(limit + 1)]  # Array to store factors for each number
	for i in range(1, limit + 1):
		for j in range(i, limit + 1, i):
			factors[j].append(i)
	return factors



FILE_NAME = 'input.txt'

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = file.readlines()

# Parse ingredients from the file
input = int(lines[0])

combos = set()
result = 0
presents = 0
house = 1
limit = 10**6
all_factors = factors_sieve(limit)
while (presents < input and house < limit):
	presents = 0
	for factor in all_factors[house]:
		presents += 10 * factor
	house += 1

result = house - 1
print(result)


#   786241 too high