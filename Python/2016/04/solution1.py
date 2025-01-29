#!/usr/bin/python3

from collections import Counter

FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

result = 0
for line in lines:
	main_part, room_name = line.split('[')
	room_name = room_name.strip('\n')
	# Remove the closing bracket from room name
	room_name = room_name.strip(']')
	# Split the main part into words and room id
	parts = main_part.rsplit('-', maxsplit=1)
	# The words are all parts except the last one
	words = parts[0].split('-')
	# The room ID is the last part
	room_id = int(parts[1])
	letters = ''.join(words)
	freq = Counter(letters)
	name = ''.join(sorted(set(letters), key=lambda x: (-freq[x], x)))
	if name[:len(room_name)] == room_name:
		result += room_id
print(result)