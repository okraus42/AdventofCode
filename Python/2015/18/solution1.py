#!/usr/bin/python3

import os
import time
import copy

def clear_terminal():
	# Check the operating system and use the appropriate command
	os.system('cls' if os.name == 'nt' else 'clear')


FILE_NAME = 'input.txt'

def print_array(array_2d, c):
	time.sleep(0.1)
	clear_terminal()
	print(c)
	for row in array_2d:
		# Join characters in the row into a single string and print
		print(''.join(row))

def animate(array_2d, r):
	for _ in range(r):
		old_arr = copy.deepcopy(array_2d)
		c = 0
		for y in range(len(old_arr)):  # Iterate over rows (y-coordinates)
			for x in range(len(old_arr[y])):  # Iterate over columns (x-coordinates)
				if old_arr[y][x] != ' ':
					n = 0
					if old_arr[y - 1][x - 1] == '#':
						n += 1
					if old_arr[y - 1][x] == '#':
						n += 1
					if old_arr[y - 1][x + 1] == '#':
						n += 1
					if old_arr[y][x - 1] == '#':
						n += 1
					if old_arr[y][x + 1] == '#':
						n += 1
					if old_arr[y + 1][x - 1] == '#':
						n += 1
					if old_arr[y + 1][x] == '#':
						n += 1
					if old_arr[y + 1][x + 1] == '#':
						n += 1
					if old_arr[y][x] == '#' and n == 2:
						array_2d[y][x] = '#'
						c += 1
					elif n == 3:
						array_2d[y][x] = '#'
						c += 1
					else:
						array_2d[y][x] = '.'
		# print_array(array_2d, c)
	return c

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = file.readlines()

# Initialize variables
array_2d = [[' '] * 102]

# Parse ingredients from the file
for line in lines:
	padded_row = [' '] + list(line.strip()) + [' ']
	array_2d.append(padded_row)
array_2d.append([' '] * 102)
# Initialize scores
result = 0

result = animate(array_2d, 100)
print(result)
