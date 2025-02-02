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
	inside = 0
	abba = False
	inner = False
	for i in range(len(line) - 3):
		sus = line[i:i+4]
		if sus[0] == '[':
			inside += 1
			continue
		elif sus[0] == ']':
			inside -= 1
			continue
		if sus.islower():
			if sus[0] == sus [3] and sus[0] != sus[1] and sus[2] == sus[1]:
				if inside > 0:
					inner = True
				else:
					abba = True
	if abba and not inner:
		result += 1
print(result)