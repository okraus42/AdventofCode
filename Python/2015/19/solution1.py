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

combos = set()
result = 0

for pair in pairs:
	start = 0
	while True:
		 # Find the next occurrence of 'to_find'
		index = original.find(pair[0], start)
		if index == -1:
			# No more occurrences found
			break

		# Replace the found occurrence
		modified = (original[:index] + pair[1] + original[index + len(pair[0]):])

		# Add the new string to the list
		combos.add(modified)

		# Move start index to the next character after the current match
		start = index + 1
result = len(combos)
print(result)
