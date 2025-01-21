#!/usr/bin/python3

import math
import sys
FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

lights = [[0] * 1000 for _ in range(1000)]
result = 0
# Now, 'content' contains the file's content as a string
for line in lines:
	if "turn on" in line:
		action = "turn on"
	elif "turn off" in line:
		action = "turn off"
	elif "toggle" in line:
		action = "toggle"
	# Remove the action from the line
	parts = line.replace(action, "").strip().split(" through ")
	# Extract coordinates
	x1, y1 = map(int, parts[0].split(","))
	x2, y2 = map(int, parts[1].split(","))
	if (action == "toggle"):
		for y in range(y1, y2 + 1):
			for x in range(x1, x2 + 1):
				lights[y][x] += 2
	if (action == "turn on"):
		for y in range(y1, y2 + 1):
			for x in range(x1, x2 + 1):
				lights[y][x] += 1
	if (action == "turn off"):
		for y in range(y1, y2 + 1):
			for x in range(x1, x2 + 1):
				if lights[y][x] != 0:
					lights[y][x] -= 1
for y in range(0, 1000):
	for x in range(0, 1000):
		result += lights[y][x]
print(result)