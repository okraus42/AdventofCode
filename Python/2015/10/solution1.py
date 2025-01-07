#!/usr/bin/python3

FILE_NAME = 'input.txt'

def sequence_generator(n, start):
	# Start with the first term
	current = start

	# Generate the sequence iteratively up to n
	for _ in range(1, n + 1):
		next_seq = ""
		i = 0
		while i < len(current):
			count = 1
			# Count consecutive digits
			while i + 1 < len(current) and current[i] == current[i + 1]:
				i += 1
				count += 1
			# Append count and digit to the next sequence
			next_seq += str(count) + current[i]
			i += 1
		# Move to the next sequence
		current = next_seq

	return current

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()
result = len(sequence_generator(40, content))
print(result)