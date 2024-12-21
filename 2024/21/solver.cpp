#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


#define FILE "input.txt"
#define SAVE 100
#define PICO 20
#define DEPTH1 2
#define DEPTH2 25


#define EAST 1
#define WEST 2
#define NORTH 4
#define SOUTH 8

#define ROBOTA 0
#define ROBOTB 1
#define ROBOTC 2
#define ME 3


bool	invalid_rperm(std::string perm, int y, int x)
{
	for (size_t i = 0; perm[i] != 'A'; i++)
	{
		if (y < 0 || x < 0 || y > 1 || x > 2)
		{
			std::cerr << "SUS: " << perm << std::endl;
		}
		if (y == 0 && x == 0)
		{
			// std::cerr << "INVALID: " << perm << std::endl;
			return (true);
		}
		if (perm[i] == '^')
			y--;
		else if (perm[i] == 'v')
			y++;
		else if (perm[i] == '<')
			x--;
		else if (perm[i] == '>')
			x++;
	}
	return (false);
}

bool	invalid_perm(std::string perm, int y, int x)
{
	int ox = x;
	int oy = y;
	for (size_t i = 0; perm[i] != 'A'; i++)
	{
		if (y < 0 || x < 0 || y > 3 || x > 2)
		{
			std::cerr << "SUS: " << perm << std::endl;
		}
		if (y == 3 && x == 0)
		{
			std::cerr << "INVALID: " << perm << "y: " << oy << "x: " << ox << std::endl;
			return (true);
		}
		if (perm[i] == '^')
			y--;
		else if (perm[i] == 'v')
			y++;
		else if (perm[i] == '<')
			x--;
		else if (perm[i] == '>')
			x++;
	}
	return (false);
}

long long	ok_rpushes(std::string str, std::vector<std::array<int, 2>> &rcoords, std::map<std::pair<std::string, int>, long long> &hashmap, std::map<char, std::array<int, 2>> &keypad, int depth)
{
	(void)rcoords;
	if (depth == 0)
		return (str.size());
	// int	pos = coords[depth][0] * 256 * 256 +  coords[depth][1] * 256 + depth;
	int	coords[2] = {0, 2};
	int pos = depth;
	int y;
	int x;
	std::pair<std::string, int> combo = std::make_pair(str, pos);
	if (hashmap.find(combo) != hashmap.end())
	{
		// std::cout << "hash " << depth << " " << str << std::endl;
		return(hashmap[combo]);
	}
	long long	pushes = 0;
	// while (rcoords[depth][0] > keypad[c][0])
	// {
	// 	pushes += ok_rpushes('^', rcoords, hashmap, keypad, depth - 1);
	// 	rcoords[depth][0]--;
	// }
	// while (rcoords[depth][0] < keypad[c][0])
	// {
	// 	pushes += ok_rpushes('v', rcoords, hashmap, keypad, depth - 1);
	// 	rcoords[depth][0]++;
	// }
	// while (rcoords[depth][1] > keypad[c][1])
	// {
	// 	pushes += ok_rpushes('<', rcoords, hashmap, keypad, depth - 1);
	// 	rcoords[depth][1]--;
	// }
	// while (rcoords[depth][1] < keypad[c][1])
	// {
	// 	pushes += ok_rpushes('>', rcoords, hashmap, keypad, depth - 1);
	// 	rcoords[depth][1]++;
	// }
	// pushes += ok_rpushes('A', rcoords, hashmap, keypad, depth - 1);
	for (size_t i = 0; i < str.size(); i++)
	{
		y = coords[0];
		x = coords[1];
		std::string s = "";
		while (coords[0] > keypad[str[i]][0])
		{
			s += '^';
			(coords[0])--;
		}
		while (coords[0] < keypad[str[i]][0])
		{
			s += 'v';
			(coords[0])++;
		}
		while (coords[1] > keypad[str[i]][1])
		{
			s += '<';
			(coords[1])--;
		}
		while (coords[1] < keypad[str[i]][1])
		{
			s += '>';
			(coords[1])++;
		}

		std::set<std::string> permutations;  // Using set to store unique permutations
		// Sort the string to ensure next_permutation generates permutations in lexicographical order
		std::sort(s.begin(), s.end());
		// Generate all permutations and store them in the set
		do
		{
			permutations.insert(s);  // insert will automatically ignore duplicates
		}
		while (std::next_permutation(s.begin(), s.end()));

		// Print the unique permutations
		long long min = 999999999999999LL;
		long long temp = 0;
		for (const auto& perm : permutations)
		{
			std::string permutation = perm + 'A';
			// std::cout << str << " " << depth << std::endl;
			// std::cout << "PERM " << depth << ": " << permutation << std::endl;
			//
			// NEED TO REMOVE INVALID PERMUTATIONS !!!
			//
			if (invalid_rperm(permutation, y, x))
				continue ;
			temp = ok_rpushes(permutation, rcoords, hashmap, keypad, depth - 1);
			// std::cout << temp << std::endl;
			if (temp < min)
				min = temp;
		}
		pushes += min;
	}
	hashmap[combo] = pushes;
	return (pushes);
}

long long	ok_pushes2(std::string s)
{
	int					coords[2] = {3, 2};
	int y;
	int x;
	std::vector<std::array<int, 2>> rcoords;
	long long			pushes = 0;
	std::map<char, std::array<int, 2>> numpad;
	std::map<char, std::array<int, 2>>	keypad;
	keypad['^'] = {0, 1};
	keypad['A'] = {0, 2};
	keypad['<'] = {1, 0};
	keypad['v'] = {1, 1};
	keypad['>'] = {1, 2};
	std::map<std::pair<std::string, int>, long long>	hashmap;
	std::string	str;

	numpad['7'] = {0, 0};
	numpad['8'] = {0, 1};
	numpad['9'] = {0, 2};
	numpad['4'] = {1, 0};
	numpad['5'] = {1, 1};
	numpad['6'] = {1, 2};
	numpad['1'] = {2, 0};
	numpad['2'] = {2, 1};
	numpad['3'] = {2, 2};
	numpad['0'] = {3, 1};
	numpad['A'] = {3, 2};

	for (size_t i = 0; i <= DEPTH2 + 1; i++)
		rcoords.push_back({0, 2});
	for (size_t i = 0; i < s.size(); i++)
	{
		y = coords[0];
		x = coords[1];
		str = "";
		while (coords[0] > numpad[s[i]][0])
		{
			str += '^';
			(coords[0])--;
		}
		while (coords[0] < numpad[s[i]][0])
		{
			str += 'v';
			(coords[0])++;
		}
		while (coords[1] > numpad[s[i]][1])
		{
			str += '<';
			(coords[1])--;
		}
		while (coords[1] < numpad[s[i]][1])
		{
			str += '>';
			(coords[1])++;
		}

		std::set<std::string> permutations;  // Using set to store unique permutations
		// Sort the string to ensure next_permutation generates permutations in lexicographical order
		std::sort(str.begin(), str.end());
		// Generate all permutations and store them in the set
		do
		{
			permutations.insert(str);  // insert will automatically ignore duplicates
		}
		while (std::next_permutation(str.begin(), str.end()));

		// Print the unique permutations
		long long min = 999999999999999LL;
		long long temp = 0;
		for (auto& perm : permutations)
		{
			std::string permutation = perm + 'A';
			// std::cout << "PERM: " << permutation << std::endl;
			//
			// NEED TO REMOVE INVALID PERMUTATIONS !!!
			//
			if (invalid_perm(permutation, y, x))
				continue ;
			temp = ok_rpushes(permutation, rcoords, hashmap, keypad, DEPTH2);
			// std::cout << temp << std::endl;
			if (temp < min)
				min = temp;
		}
		pushes += min;
		// std::cout << str << std::endl;
	}
	// std::cout << std::endl;
	return (pushes);
}


long long	ok_pushes(std::string s)
{
	int					coords[2] = {3, 2};
	int y;
	int x;
	std::vector<std::array<int, 2>> rcoords;
	long long			pushes = 0;
	std::map<char, std::array<int, 2>> numpad;
	std::map<char, std::array<int, 2>>	keypad;
	keypad['^'] = {0, 1};
	keypad['A'] = {0, 2};
	keypad['<'] = {1, 0};
	keypad['v'] = {1, 1};
	keypad['>'] = {1, 2};
	std::map<std::pair<std::string, int>, long long>	hashmap;
	std::string	str;

	numpad['7'] = {0, 0};
	numpad['8'] = {0, 1};
	numpad['9'] = {0, 2};
	numpad['4'] = {1, 0};
	numpad['5'] = {1, 1};
	numpad['6'] = {1, 2};
	numpad['1'] = {2, 0};
	numpad['2'] = {2, 1};
	numpad['3'] = {2, 2};
	numpad['0'] = {3, 1};
	numpad['A'] = {3, 2};

	for (size_t i = 0; i <= DEPTH1 + 1; i++)
		rcoords.push_back({0, 2});
	for (size_t i = 0; i < s.size(); i++)
	{
		y = coords[0];
		x = coords[1];
		str = "";
		while (coords[0] > numpad[s[i]][0])
		{
			str += '^';
			(coords[0])--;
		}
		while (coords[0] < numpad[s[i]][0])
		{
			str += 'v';
			(coords[0])++;
		}
		while (coords[1] > numpad[s[i]][1])
		{
			str += '<';
			(coords[1])--;
		}
		while (coords[1] < numpad[s[i]][1])
		{
			str += '>';
			(coords[1])++;
		}

		std::set<std::string> permutations;  // Using set to store unique permutations
		// Sort the string to ensure next_permutation generates permutations in lexicographical order
		std::sort(str.begin(), str.end());
		// Generate all permutations and store them in the set
		do
		{
			permutations.insert(str);  // insert will automatically ignore duplicates
		}
		while (std::next_permutation(str.begin(), str.end()));

		// Print the unique permutations
		long long min = 999999999999999LL;
		long long temp = 0;
		for (auto& perm : permutations)
		{
			std::string permutation = perm + 'A';
			// std::cout << "PERM: " << permutation << std::endl;
			//
			// NEED TO REMOVE INVALID PERMUTATIONS !!!
			//
			if (invalid_perm(permutation, y, x))
				continue ;
			temp = ok_rpushes(permutation, rcoords, hashmap, keypad, DEPTH1);
			// std::cout << temp << std::endl;
			if (temp < min)
				min = temp;
		}
		pushes += min;
		// std::cout << str << std::endl;
	}
	// std::cout << std::endl;
	return (pushes);
}

void	part1()
{
	long long	result = 0;
	long long	moves = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	
	std::string			line;
	
	// Read the file line by line"

	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	size_t	i;
	for (i = 0; i < lines.size(); i++)
	{
		moves = ok_pushes(lines[i]);
		// std::cout << lines[i] << std::endl;
		// std::cout << moves << std::endl;
		result += moves * std::stoi(lines[i]);
	}
	file.close();
	std::cout << result << std::endl;
}
void	part2()
{
	long long	result = 0;
	long long	moves = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	
	std::string			line;
	
	// Read the file line by line"

	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	size_t	i;
	for (i = 0; i < lines.size(); i++)
	{
		moves = ok_pushes2(lines[i]);
		// std::cout << lines[i] << std::endl;
		// std::cout << moves << std::endl;
		result += moves * std::stoi(lines[i]);
	}
	file.close();
	std::cout << result << std::endl;
}

int	main(void)
{
	//part1
	part1();
	//part2
	part2();
	return (0);
}