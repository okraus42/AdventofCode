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

for line in lines:
	name, speed, time1, time2 = extract_data(line)
	deers.append((name, speed, time1, time2))
for deer in deers:
	name, speed, time1, time2 = deer
	distance = 0
	time = 0
	moving = True
	resting = time2
	flying = time1
	while (time < 2503):
		time += 1
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
	if distance > result:
		result = distance
print(result)