#!/usr/bin/python3

FILE_NAME = 'input.txt'
substrings = ['abc', 'bcd', 'cde', 'def', 'efg', 'fgh', 'ghj', 'hjk', 'jkm',  'kmn', 'mnp', 'npq', 'pqr', 'qrs', 'rst', 'stu', 'tuv',  'uvw', 'vwx', 'wxy', 'xyz']


def invalid(pwd):
	pairs = 0
	i = 0
	if any(sub in pwd for sub in substrings):
		while i < len(pwd) - 1:
			if pwd[i] == pwd[i + 1]:  # Check for a pair
				pairs += 1  # Store the index of the pair
				i += 1  # Skip the next character to ensure non-overlapping pairs
			i += 1
		if pairs > 1 :
			return False
	return True

def next_pass(pwd):
	pwd = list(pwd)
	carry = True
	for i in range(len(pwd) - 1, -1, -1):
		if (carry == False):
			break
		if pwd[i] == 'z':
			pwd[i] = 'a'
		else:
			carry = False
			if pwd[i] in ['i', 'l', 'o']:
				pwd[i] = chr(ord(pwd[i]) + 2)
			else:
				pwd[i] = chr(ord(pwd[i]) + 1)
	return ''.join(pwd)

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()

while invalid(content):
	content = next_pass(content)
result = content
print(result)