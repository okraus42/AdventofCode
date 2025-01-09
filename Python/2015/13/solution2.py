#!/usr/bin/python3

import itertools
FILE_NAME = 'input.txt'

# Function to extract data
def extract_data(sentence):
	words = sentence.split()		# Split the sentence into words
	person1 = words[0]				# First word is the first person's name
	gain_or_lose = words[2]			# Third word indicates 'gain' or 'lose'
	value = int(words[3])			# Fourth word is the numerical value
	if gain_or_lose == "lose":
		value = -value				# Make the value negative if 'lose'
	person2 = words[-1].strip('.')	# Last word (before the period) is the second person's name
	return person1, person2, value

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()
names = set()
relations = {}
result = 0

for line in lines:
	person1, person2, value = extract_data(line)
	names.add(person1)
	relations[(person1, person2)] = value

for name in names:
	relations[("me", name)] = 0
	relations[(name, "me")] = 0

names.add("me")
permutations = itertools.permutations(names)

for perm in permutations:
	happiness = 0
	for i in range(len(perm)):
		person1 = perm[i]
		if (i == len(perm) - 1):
			person2 = perm[0]
		else:
			person2 = perm[i + 1]
		if (i == 0):
			person3 = perm[-1]
		else:
			person3 = perm[i - 1]
		happiness += relations[(person1, person2)]
		happiness += relations[(person1, person3)]
	if (happiness > result):
		result = happiness
print(result)