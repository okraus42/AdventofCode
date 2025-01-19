#!/usr/bin/python3

from itertools import combinations

FILE_NAME = 'input.txt'

# Read the file
with open(FILE_NAME, 'r') as file:
	lines = file.readlines()

# Parse stats from the file
boss_stats = {"hp": int(lines[0].split()[-1]), "damage": int(lines[1].split()[-1]), "armor": int(lines[2].split()[-1])}


# Define the items
weapons = [
	{"name": "Dagger", "cost": 8, "damage": 4, "armor": 0},
	{"name": "Shortsword", "cost": 10, "damage": 5, "armor": 0},
	{"name": "Warhammer", "cost": 25, "damage": 6, "armor": 0},
	{"name": "Longsword", "cost": 40, "damage": 7, "armor": 0},
	{"name": "Greataxe", "cost": 74, "damage": 8, "armor": 0},
]

armors = [
	{"name": "None", "cost": 0, "damage": 0, "armor": 0},  # Include "no armor" option
	{"name": "Leather", "cost": 13, "damage": 0, "armor": 1},
	{"name": "Chainmail", "cost": 31, "damage": 0, "armor": 2},
	{"name": "Splintmail", "cost": 53, "damage": 0, "armor": 3},
	{"name": "Bandedmail", "cost": 75, "damage": 0, "armor": 4},
	{"name": "Platemail", "cost": 102, "damage": 0, "armor": 5},
]

rings = [
	{"name": "None", "cost": 0, "damage": 0, "armor": 0},  # Include "no ring" option
	{"name": "Damage +1", "cost": 25, "damage": 1, "armor": 0},
	{"name": "Damage +2", "cost": 50, "damage": 2, "armor": 0},
	{"name": "Damage +3", "cost": 100, "damage": 3, "armor": 0},
	{"name": "Defense +1", "cost": 20, "damage": 0, "armor": 1},
	{"name": "Defense +2", "cost": 40, "damage": 0, "armor": 2},
	{"name": "Defense +3", "cost": 80, "damage": 0, "armor": 3},
]

# Generate all combinations of 0-2 rings
ring_combinations = [list(combinations(rings[1:], i)) for i in range(3)]  # Exclude the "None" ring option
ring_combinations = [item for sublist in ring_combinations for item in sublist]  # Flatten the list
ring_combinations.append((rings[0],))  # Add the "None" option as a tuple

# Generate all possible equipment combinations
combinations_list = []
for weapon in weapons:
	for armor in armors:
		for ring_comb in ring_combinations:
			combination = [weapon, armor] + list(ring_comb)
			total_cost = sum(item["cost"] for item in combination)
			total_damage = sum(item["damage"] for item in combination)
			total_armor = sum(item["armor"] for item in combination)
			combinations_list.append({
				"items": combination,
				"total_cost": total_cost,
				"total_damage": total_damage,
				"total_armor": total_armor
			})

# Sort combinations by total cost
combinations_list.sort(key=lambda x: x["total_cost"])

# Print the sorted combinations
for combination in combinations_list:
	boss = dict(boss_stats)
	player = {"hp": 100, "damage": combination["total_damage"], "armor": combination["total_armor"]}
	result = combination["total_cost"]
	while (player["hp"] > 0 and boss["hp"] > 0):
		# print("player", player)
		# print("boss", boss)
		hit = max(1, player["damage"] - boss["armor"])
		boss["hp"] -= hit
		if (boss["hp"] > 0):
			hit = max(1, boss["damage"] - player["armor"])
			player["hp"] -= hit
	if (player["hp"] > 0):
		break

print(result)
