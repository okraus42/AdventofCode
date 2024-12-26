#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

#define MAP 50
#define FILE "input.txt"

int	move(std::vector<std::string> &lines, std::set<int> &coordinates, int y, int x, char last)
{
	int res = 0;
	if (y < 0 || x < 0 || y >= (int)lines.size() || x >= (int)lines[y].size())
		return (0);
	if (last == '8' && lines[y][x] == '9')
	{
		coordinates.insert(y*100 + x);
		return (1);
	}
	if (lines[y][x] != last + 1)
		return (0);
	last = lines[y][x];
	res += move(lines, coordinates, y + 1, x, last);
	res += move(lines, coordinates, y - 1, x, last);
	res += move(lines, coordinates, y, x + 1, last);
	res += move(lines, coordinates, y, x - 1, last);
	return (res);
}

void	part1()
{
	long long	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string>	lines;
	std::string					line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	size_t i;
	size_t j;
	std::set<int>			coordinates;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '0')
			{
				coordinates.clear();
				std::cout << i << "   " << j <<std::endl;
				move(lines, coordinates, i + 1, j, '0');
				move(lines, coordinates, i - 1, j, '0');
				move(lines, coordinates, i, j + 1, '0');
				move(lines, coordinates, i, j - 1, '0');
				result += coordinates.size();
				std::cout << result << std::endl;
			}
		}
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

	std::vector<std::string>	lines;
	std::string					line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	size_t i;
	size_t j;
	std::set<int>			coordinates;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '0')
			{
				coordinates.clear();
				std::cout << i << "   " << j <<std::endl;
				result += move(lines, coordinates, i + 1, j, '0');
				result += move(lines, coordinates, i - 1, j, '0');
				result += move(lines, coordinates, i, j + 1, '0');
				result += move(lines, coordinates, i, j - 1, '0');
				std::cout << result << std::endl;
			}
		}
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