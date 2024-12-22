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


void	part1()
{
	long long	result = 0;
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
	size_t	j;
	for (i = 0; i < lines.size(); i++)
	{
		long long	secret_number = std::stoi(lines[i]);
		long long	mix;

		// std::cout << secret_number << std::endl;
		for (j = 0; j < 2000; j++)
		{
			mix = secret_number * 64;
			secret_number ^= mix;
			secret_number %= 16777216;
			mix = secret_number / 32;
			secret_number ^= mix;
			secret_number %= 16777216;
			mix = secret_number * 2048;
			secret_number ^= mix;
			secret_number %= 16777216;
		}
		// std::cout << secret_number << std::endl;
		result += secret_number;
	}
	file.close();
	std::cout << result << std::endl;
}
void	part2()
{
	long long	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	
	std::string			line;
	int					sequence[4];
	int					orig;
	int					dif;
	std::map<int, int>	bananas;
	std::map<int, int>	skip;
	// Read the file line by line"

	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	size_t	i;
	size_t	j;
	for (i = 0; i < lines.size(); i++)
	{
		long long	secret_number = std::stoi(lines[i]);
		long long	mix;
		int			magic_key;

		// std::cout << secret_number << std::endl;
		skip.clear();
		for (j = 0; j < 2000; j++)
		{
			orig = secret_number % 10;
			mix = secret_number * 64;
			secret_number ^= mix;
			secret_number %= 16777216;
			mix = secret_number / 32;
			secret_number ^= mix;
			secret_number %= 16777216;
			mix = secret_number * 2048;
			secret_number ^= mix;
			secret_number %= 16777216;
			dif = secret_number % 10 - orig;
			if (j == 0)
				sequence[0] = dif;
			else if (j == 1)
				sequence[1] = dif;
			else if (j == 2)
				sequence[2] = dif;
			else
			{
				sequence[3] = dif;
				magic_key = (sequence[0] + 10) * 32 * 32 * 32 + (sequence[1] + 10) * 32 * 32 + (sequence[2] + 10) * 32 + (sequence[3] + 10);
				if (skip.find(magic_key) == skip.end())
				{
					skip[magic_key] = 1;
					// std::cout << "adding bananas" << std::endl;
					if (bananas.find(magic_key) == bananas.end())
					{
						bananas[magic_key] = secret_number % 10;
					}
					else
					{
						// std::cout << "before: " << bananas[magic_key] << std::endl;
						bananas[magic_key] += secret_number % 10;
						// std::cout << "after: " << bananas[magic_key] << std::endl;
					}
				}
				sequence[0] = sequence[1];
				sequence[1] = sequence[2];
				sequence[2] = sequence[3];
			}
		}
		// std::cout << "2: " << secret_number << std::endl;
	}
	int max = 0;
	int num = 0;
	for (std::map<int, int>::iterator it = bananas.begin(); it != bananas.end(); ++it)
	{
		num++;
		if (it->second > max)
		{
			max = it->second;
		}
	}
	// std::cout << num << std::endl;
	result = max;
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