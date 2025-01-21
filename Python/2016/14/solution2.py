#!/usr/bin/python3

import itertools
FILE_NAME = 'input.txt'

def extract_data(sentence):
	words = sentence.split()		# Split the sentence into words
	name = words[0]
	speed = int(words[3])
	time1 = int(words[6])
	time2 = int(words[13])
	return name, speed, time1, time2

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()
result = 0
deers = []

# Initialize deers list
for line in lines:
	name, speed, time1, time2 = extract_data(line)
	deers.append([name, speed, time1, time2, time1, time2, True, 0, 0])  # Use list instead of tuple for mutability

time = 0
while time < 2503:
	time += 1
	temp = 0
	for i, deer in enumerate(deers):  # Use enumerate to track index
		name, speed, time1, time2, flying, resting, moving, distance, stars = deer

		if moving:
			flying -= 1
			distance += speed
		else:
			resting -= 1

		if flying == 0:
			moving = False
			resting = time2
			flying = time1

		if resting == 0:
			moving = True
			flying = time1
			resting = time2
		
		if distance > temp:
			temp = distance

		# Update the original deer in the list
		deers[i] = [name, speed, time1, time2, flying, resting, moving, distance, stars]
	for i, deer in enumerate(deers):
		name, speed, time1, time2, flying, resting, moving, distance, stars = deer
		if (distance == temp):
			stars += 1
		deers[i] = [name, speed, time1, time2, flying, resting, moving, distance, stars]
for deer in deers:
	name, speed, time1, time2, flying, resting, moving, distance, stars = deer
	if (stars > result):
		result = stars
print(result)