#!/usr/bin/python3

FILE_NAME = 'input.txt'

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = [line.strip() for line in file.readlines()]

registers = {'a': 1, 'b': 0}
index = 0

instructions = []

# Parse instructions from the file
for line in lines:
	parts = line.replace(',', '').split()
	instr = {'name': parts[0]}
	
	if parts[0] in {'hlf', 'tpl', 'inc'}:
		instr['register'] = parts[1]
	elif parts[0] == 'jmp':
		instr['offset'] = int(parts[1])
	elif parts[0] in {'jie', 'jio'}:
		instr['register'] = parts[1]
		instr['offset'] = int(parts[2])
	
	instructions.append(instr)

running = True
next = 0
max = len(instructions)
while running:
	i = instructions[next]
	if i['name'] == 'hlf':
		next += 1
		registers[i['register']] /= 2
	elif i['name'] == 'tpl':
		next += 1
		registers[i['register']] *= 3
	elif i['name'] == 'inc':
		next += 1
		registers[i['register']] += 1
	elif i['name'] == 'jmp':
		next += i['offset']
	elif i['name'] == 'jie' and registers[i['register']] % 2 == 0:
		next += i['offset']
	elif i['name'] == 'jio' and registers[i['register']] == 1:
		next += i['offset']
	else:
		next += 1
	if next < 0 or next >= max:
		running = False
result = registers['b']

print(result)
