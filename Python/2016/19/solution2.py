#!/usr/bin/python3

FILE_NAME = 'input.txt'

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = file.readlines()

# Initialize variables
pairs = []

# Parse ingredients from the file
for line in lines:
	words = line.split()
	if len(words) == 3:
		pairs.append((words[0], words[2]))

	elif len(words) == 1:
		original = words[0]

result = 0

atoms = 0
Ys = 0
Ars = 0
Rns = 0

# Iterate through the string to count uppercase atoms
for char in original:
	if char.isupper():
		atoms += 1

# Manually check for 'Y', 'Ar', and 'Rn' occurrences
i = 0
while i < len(original):
	# Check for 'Rn' first
	if original[i:i+2] == 'Rn':
		Rns += 1
		i += 2  # Skip the next character since 'Rn' is 2 characters long
	# Check for 'Ar'
	elif original[i:i+2] == 'Ar':
		Ars += 1
		i += 2  # Skip the next character since 'Ar' is 2 characters long
	# Check for 'Y'
	elif original[i:i+1] == 'Y':
		Ys += 1
		i += 1  # Move by one character since 'Y' is 1 character long
	else:
		i += 1  # Move to the next character
print("atoms: ", atoms, ", Ars ", Ars, ", Rns ", Rns, ", Ys ", Ys)
result = atoms - Ars - Rns - 2 * Ys - 1
print(result)
