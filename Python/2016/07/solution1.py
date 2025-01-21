#!/usr/bin/python3

import math
import sys
import functools
FILE_NAME = 'input.txt'
parsed_lines = []
@functools.lru_cache(maxsize=None) 
# Example: Find a specific result in parsed data
def find_result(target_result):
	for entry in parsed_lines:
		if entry["outcome"] == target_result:
			print(f"1:{entry}")
			if entry["operatorB"].isdigit():
				b = int(entry["operatorB"]) & 0xFFFF
			else:
				print(f"looking for b: {entry['operatorB']}")
				b = find_result(entry["operatorB"]) & 0xFFFF
			if entry["operatorA"]:
				if entry["operatorA"].isdigit():
					a = int(entry["operatorA"]) & 0xFFFF
				else:
					print(f"looking for a: {entry['operatorA']}")
					a = find_result(entry["operatorA"]) & 0xFFFF
			if entry["operation"]:
				if entry["operation"] == "AND" :
					return (a & b) & 0xFFFF
				elif entry["operation"] == "OR" :
					return (a | b) & 0xFFFF
				elif entry["operation"] == "LSHIFT" :
					return (a << b) & 0xFFFF
				elif entry["operation"] == "RSHIFT" :
					return (a >> b) & 0xFFFF
				elif entry["operation"] == "NOT" :
					return (~b) & 0xFFFF
			else :
				return b & 0xFFFF
	print (f"{target_result} not found")
	return None  # Return None if the result is not found

# Open the file in read mode
with open(FILE_NAME, 'r') as file:
	# Read the entire content of the file into a string
	lines = file.readlines()

lights = [[False] * 1000 for _ in range(1000)]
result = 0

# Now, 'content' contains the file's content as a string
for line in lines:
	if "->" in line:
		expression, outcome = line.split("->")
		outcome = outcome.strip()
		parts = expression.strip().split()

		# Parsing the expression
		if len(parts) == 1:  # Example: "123 -> x"
			operatorA = ""
			operation = ""
			operatorB = parts[0]
		elif len(parts) == 2:  # Example: "NOT x -> h"
			operatorA = ""
			operation = parts[0]
			operatorB = parts[1]
		elif len(parts) == 3:  # Example: "x AND y -> d"
			operatorA, operation, operatorB = parts
		parsed_lines.append({
			"operatorA": operatorA,
			"operation": operation,
			"operatorB": operatorB,
			"outcome": outcome,
		})
result = find_result("a")
print(result)