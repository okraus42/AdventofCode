#!/usr/bin/python3

import itertools

FILE_NAME = 'input.txt'

# Function to extract data from a line
def extract_data(sentence):
	words = sentence.split()        # Split the sentence into words
	name = words[0][:-1]
	capacity = int(words[2][:-1])
	durability = int(words[4][:-1])
	flavor = int(words[6][:-1])
	texture = int(words[8][:-1])
	calories = int(words[10])
	return {
		"name": name,
		"capacity": capacity,
		"durability": durability,
		"flavor": flavor,
		"texture": texture,
		"calories": calories,
		"quantity": 25  # Initial quantity
	}

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = file.readlines()

# Initialize variables
ingredients = []
names = set()

# Parse ingredients from the file
for line in lines:
	ingredient = extract_data(line)
	names.add(ingredient["name"])
	ingredients.append(ingredient)

# Initialize scores
result = 0
best_perm = None

# Compute initial score
def compute_score(ingredients):
	s_capacity = sum(ingredient["capacity"] * ingredient["quantity"] for ingredient in ingredients)
	s_durability = sum(ingredient["durability"] * ingredient["quantity"] for ingredient in ingredients)
	s_flavor = sum(ingredient["flavor"] * ingredient["quantity"] for ingredient in ingredients)
	s_texture = sum(ingredient["texture"] * ingredient["quantity"] for ingredient in ingredients)

	# Ensure no negative scores
	s_capacity = max(s_capacity, 0)
	s_durability = max(s_durability, 0)
	s_flavor = max(s_flavor, 0)
	s_texture = max(s_texture, 0)

	return s_capacity * s_durability * s_flavor * s_texture

# Calculate initial score
result = compute_score(ingredients)

oldscore = 0
while oldscore < result:
	oldscore = result
	permutations = itertools.permutations(names, 2)
	for perm in permutations:
		# Adjust quantities based on permutations
		for ingredient in ingredients:
			if ingredient["name"] == perm[0]:
				ingredient["quantity"] -= 1
			elif ingredient["name"] == perm[1]:
				ingredient["quantity"] += 1

		# Calculate the new score
		score = compute_score(ingredients)

		# Update result and best_perm if a better score is found
		if score > result:
			result = score
			best_perm = perm

		# Revert the quantities after processing
		for ingredient in ingredients:
			if ingredient["name"] == perm[0]:
				ingredient["quantity"] += 1
			elif ingredient["name"] == perm[1]:
				ingredient["quantity"] -= 1

	# After determining the best_perm, update the quantities permanently
	for ingredient in ingredients:
		if ingredient["name"] == best_perm[0]:
			ingredient["quantity"] -= 1
		elif ingredient["name"] == best_perm[1]:
			ingredient["quantity"] += 1

print(result)
