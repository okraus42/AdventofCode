#!/usr/bin/python3

import itertools

FILE_NAME = 'input.txt'

# Function to extract data from a line
def extract_data(sentence):
	words = sentence.split()  # Split the sentence into words
	name = int(words[1][:-1])
	word1 = words[2][:-1]
	num1 = int(words[3][:-1])
	word2 = words[4][:-1]
	num2 = int(words[5][:-1])
	word3 = words[6][:-1]
	num3 = int(words[7])

	# Initialize all categories to -1
	categories = {
		"children": -1,
		"cats": -1,
		"samoyeds": -1,
		"pomeranians": -1,
		"akitas": -1,
		"vizslas": -1,
		"goldfish": -1,
		"trees": -1,
		"cars": -1,
		"perfumes": -1
	}

	# Map the words to their corresponding category
	items_to_update = [word1, word2, word3]
	numbers = [num1, num2, num3]

	# Update the categories dictionary with the corresponding values
	for word, num in zip(items_to_update, numbers):
		if word in categories:
			categories[word] = num

	# Return the result as a dictionary, including the "name" field
	result = {"name": name}
	result.update(categories)

	return result

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = file.readlines()

# Initialize variables
aunts = []

# Parse ingredients from the file
for line in lines:
	aunt = extract_data(line)
	aunts.append(aunt)

# Define the predefined criteria
predefined_criteria = {
	"children": 3,
	"cats": 7,
	"samoyeds": 2,
	"pomeranians": 3,
	"akitas": 0,
	"vizslas": 0,
	"goldfish": 5,
	"trees": 3,
	"cars": 2,
	"perfumes": 1
}

# Initialize scores
result = 0
for aunt in aunts:
	match = True
	for category, value in predefined_criteria.items():
		if aunt[category] != -1 and aunt[category] != value:
			match = False
			break
	if match:
		result = aunt["name"]

print(result)
