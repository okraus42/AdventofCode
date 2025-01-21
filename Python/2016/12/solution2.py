#!/usr/bin/python3

FILE_NAME = 'input.txt'

def braces_and_brackets(str, b):
	# Find the positions of the outermost braces
	looking = b
	found = False
	number = ''
	result = 0
	braces = 0
	brackets = 0
	substr = ''
	i = -1
	while i < len(str) - 1:
		i += 1
		if str[i] == '{':
			braces += 1
		elif str[i] == '[':
			brackets += 1
		elif str[i] == '}':
			braces -= 1
			if (braces == 0 and brackets == 0):
				result += braces_and_brackets(substr[1:], True)
				substr = ''
		elif str[i] == ']':
			brackets -= 1
			if (braces == 0 and brackets == 0):
				result += braces_and_brackets(substr[1:], False)
				substr = ''
		if (braces > 0 or brackets > 0):
			substr += str[i]
		else:
			if str[i] == 'r' and str[i + 1] == 'e' and str[i + 2] == 'd':
				found = True
			if str[i].isdigit() or (str[i] == '-' and not number):  # Check for digit or leading '-'
				number += str[i]
			elif number:  # If we reach a non-digit and a number is being formed
				result += int(number)
				number = ''
	if (len(number) > 0):
		result += int(number)
	if looking and found:
		result = 0
	return (result)

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()
	result = braces_and_brackets(content, True)
print(result)