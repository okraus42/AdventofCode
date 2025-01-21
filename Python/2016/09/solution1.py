#!/usr/bin/python3


import itertools
FILE_NAME = 'input.txt'

def add_distance(distances, location1, location2, distance):
	key = tuple(sorted([location1, location2]))  # Ensure consistent key order
	distances[key] = distance

def get_distance(distances, location1, location2):
	key = tuple(sorted([location1, location2]))  # Ensure consistent key order
	return distances.get(key, "Distance not found")

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

locations = set()
distances = {}
result = 99999999
# Now, 'content' contains the file's content as a string
for line in lines:
	parts = line.split(" to ")
	location1 = parts[0]  # "London"
	rest = parts[1].split(" = ")
	location2 = rest[0]  # "Dublin"
	locations.add(location1)
	locations.add(location2)
	distance = int(rest[1])  # 464 (convert to integer)
	add_distance(distances, location1, location2, distance)

permutations = itertools.permutations(locations)

# Print each permutation
for perm in permutations:
	previous_location = perm[0]
	distance = 0
	for location in perm[1:]:
		distance += get_distance(distances, previous_location, location)
		previous_location = location
	if distance < result:
		result = distance
print(result)