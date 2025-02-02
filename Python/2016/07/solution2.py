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
	aba = set()
	bab = set()
	ssl = False
	for i in range(len(line) - 2):
		sus = line[i:i+3]
		if sus[0] == '[':
			inside += 1
			continue
		elif sus[0] == ']':
			inside -= 1
			continue
		if sus.islower():
			if sus[0] == sus [2] and sus[0] != sus[1]:
				if inside > 0:
					bab.add(sus)
				else:
					aba.add(sus)
	for a in aba:
		for b in bab:
			if a[0] == b[1] and a[1] == b[0]:
				ssl = True
	if ssl:
		result += 1
print(result)