#!/usr/bin/python3

from enum import Enum

class Direction(Enum):
	NORTH = 0
	EAST = 1
	SOUTH = 2
	WEST = 3

	@staticmethod
	def turn_clockwise(direction):
		# Increase the direction by 1 (modulo 4)
		return Direction((direction.value + 1) % 4)

	@staticmethod
	def turn_anticlockwise(direction):
		# Decrease the direction by 1 (modulo 4)
		return Direction((direction.value - 1) % 4)


FILE_NAME = 'input.txt'

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	content = file.read()

parts = content.split(', ')
directions = []
for part in parts:
	letter = part[0]
	value = int(part[1:])
	directions.append((letter, value))
result = 0
current_direction = Direction.NORTH
y = 0
x = 0
for direction in directions:
	if direction[0] == 'R':
		current_direction = Direction.turn_clockwise(current_direction)
	else:
		current_direction = Direction.turn_anticlockwise(current_direction)
	if current_direction == Direction.NORTH:
		y += direction[1]
	elif current_direction == Direction.EAST:
		x += direction[1]
	elif current_direction == Direction.SOUTH:
		y -= direction[1]
	elif current_direction == Direction.WEST:
		x -= direction[1]
result = abs(x) + abs(y)
print(result)