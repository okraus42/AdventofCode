#!/usr/bin/python3

FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read().strip()

modified = ''
i = 0  # Index pointer

while i < len(content):
	if content[i] == '(':
		# Find the closing parenthesis for the marker
		end_marker = content.find(')', i)
		if end_marker == -1:
			# If no closing parenthesis is found, break out or handle the error
			print("Malformed marker: no closing ')'")
			break

		# Extract the marker and split by 'x'
		marker = content[i+1:end_marker]
		try:
			num_chars, repeat = map(int, marker.split('x'))
		except ValueError:
			print("Malformed marker: expected two integers separated by 'x'")
			break

		# Move index to the start of the sequence to be repeated
		i = end_marker + 1
		# Get the substring that needs to be repeated
		segment = content[i:i+num_chars]
		# Append the repeated segment to modified
		modified += segment * repeat

		# Move the index past the processed segment
		i += num_chars
	else:
		# If it's not a marker, just copy the character to modified
		modified += content[i]
		i += 1

result = len(modified)
print(result)