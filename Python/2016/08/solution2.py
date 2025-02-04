#!/usr/bin/python3

FILE_NAME = 'input.txt'

def parse_instruction(line):
	parts = line.split()

	if parts[0] == "rect":
		first, second = map(int, parts[1].split("x"))
		return "rect", first, second

	elif parts[0] == "rotate" and parts[1] == "row":
		first = int(parts[2][2:])  # Extract number after "y="
		second = int(parts[4])     # Number after "by"
		return "rotate row", first, second

	elif parts[0] == "rotate" and parts[1] == "column":
		first = int(parts[2][2:])  # Extract number after "x="
		second = int(parts[4])     # Number after "by"
		return "rotate column", first, second

	return None  # Invalid instruction
# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

result = 0
# Create a 2D array filled with '.'
grid = [['.' for _ in range(50)] for _ in range(6)]

# Now, 'content' contains the file's content as a string
for line in lines:
	line = line.strip()
	instruction, a, b = parse_instruction(line)
	if instruction == "rect":
		for y in range(b):
			for x in range(a):
				grid[y][x] = '#'
	elif instruction == "rotate row":
		grid[a] = grid[a][-b % 50:] + grid[a][:-b % 50]
	elif instruction == "rotate column":
		column = [grid[i][a] for i in range(6)]  # Extract column
		# Rotate the column (shift down)
		column = column[-b % 6:] + column[:-b % 6]
		# Put rotated values back in the grid
		for i in range(6):
			grid[i][a] = column[i]
for row in grid:
	print(''.join(row))
print(result)