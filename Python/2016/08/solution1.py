#!/usr/bin/python3

FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

result = 0
# Now, 'content' contains the file's content as a string
for line in lines:
	line = line.strip()

result = real_chars - printed_chars
print(result)