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
	name = parts[0].replace("-", " ")
	# The room ID is the last part
	room_id = int(parts[1])
	secret_name = []
	for char in name:
		if char == ' ':
			secret_name.append(' ')
			continue
		num = ord(char) - ord('a')
		num += room_id
		num %= 26
		new_char = chr(num + ord('a'))
		secret_name.append(new_char)
	secret_name = ''.join(secret_name)
	if "north" in secret_name:
		result = room_id
print(result)