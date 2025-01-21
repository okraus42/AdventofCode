#!/usr/bin/python3

FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()
	number = ''
	result = 0
	for char in content:
		if char.isdigit() or (char == '-' and not number):  # Check for digit or leading '-'
			number += char
		elif number:  # If we reach a non-digit and a number is being formed
			result += int(number)
			number = ''
print(result)