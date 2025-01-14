#!/usr/bin/python3

import os
import time
import copy

def clear_terminal():
	# Check the operating system and use the appropriate command
	os.system('cls' if os.name == 'nt' else 'clear')


FILE_NAME = 'input.txt'

def print_array(array_2d, i, c):
	time.sleep(0.05)
	clear_terminal()
	print(i, "\t", c)
	for row in array_2d:
		# Join characters in the row into a single string and print
		print(''.join(row))

def count_hashes(array_2d):
	count = 0
	for row in array_2d:
		count += row.count('#')  # Count '#' in each row
	return count

def animate(array_2d, r):
	for i in range(r):
		array_2d[1][1] = '#'
		array_2d[1][100] = '#'
		array_2d[100][1] = '#'
		array_2d[100][100] = '#'
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
					elif y == 1 and x == 1:
						array_2d[y][x] = '#'
						c += 1
					elif y == 1 and x == 100:
						array_2d[y][x] = '#'
						c += 1
					elif y == 100 and x == 1:
						array_2d[y][x] = '#'
						c += 1
					elif y == 100 and x == 100:
						array_2d[y][x] = '#'
						c += 1
					else:
						array_2d[y][x] = '.'
		# print_array(array_2d, i, c)
	# print_array(array_2d, i, c)
	# c = count_hashes(array_2d)
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

# 865 too low
# 890 too high


# import numpy as np


# class Game(object):
#     def __init__(self, initial_state, broken=False):
#         self._state = self.parse(initial_state)
#         shape = self.state.shape
#         self.x_max = shape[0] - 1
#         self.y_max = shape[1] - 1
#         self.broken = broken
#         self._set_broken_lights()

#     def _set_broken_lights(self):
#         if self.broken:
#             for x in (0, self.x_max):
#                 for y in (0, self.y_max):
#                     self.state[x, y] = 1

#     @property
#     def state(self):
#         return self._state[1:-1, 1:-1]

#     @state.setter
#     def state(self, new_state):
#         self._state[1:-1, 1:-1] = new_state

#     @staticmethod
#     def parse(initial_state):
#         size_x = initial_state.index("\n")
#         size_y = initial_state.strip().count("\n") + 1
#         state = np.zeros((size_x + 2, size_y + 2), dtype=np.uint8)
#         for i, line in enumerate(initial_state.strip().split("\n")):
#             for j, char in enumerate(line):
#                 state[i + 1, j + 1] = 0 if char == "." else 1
#         return state

#     def get_n_neighbours(self):
#         return (self._state[0:-2, 0:-2] + self._state[0:-2, 1:-1] +
#                 self._state[0:-2, 2:] + self._state[1:-1, 0:-2] +
#                 self._state[1:-1, 2:] + self._state[2:, 0:-2] +
#                 self._state[2:, 1:-1] + self._state[2:, 2:])

#     def step(self, n_steps=1):
#         for i in range(n_steps):
#             n_neighbours = self.get_n_neighbours()

#             birth = (n_neighbours == 3) & (self._state[1:-1, 1:-1] == 0)
#             survive = (((n_neighbours == 2) | (n_neighbours == 3)) &
#                     (self._state[1:-1, 1:-1] == 1))

#             self._state[...] = 0
#             self._state[1:-1, 1:-1][birth | survive] = 1
#             self._set_broken_lights()

#     @property
#     def n_lights_on(self):
#         return np.sum(self.state)


# def part_one():
#     with open("input.txt") as fin:
#         game = Game(fin.read())
#     game.step(100)
#     print("{} lights on".format(game.n_lights_on))


# def part_two():
#     with open("input.txt") as fin:
#         game = Game(fin.read(), broken=True)
#     game.step(100)
#     print("{} lights on".format(game.n_lights_on))


# if __name__ == '__main__':
#     part_one()
#     part_two()