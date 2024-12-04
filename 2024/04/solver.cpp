#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

int	find_up(std::vector<std::string> lines, size_t y, size_t x)
{
	if (y > 2 && lines[y - 1][x] == 'M' && lines[y - 2][x] == 'A' && lines[y - 3][x] == 'S')
		return (1);
	return (0);
}

int	find_down(std::vector<std::string> lines, size_t y, size_t x)
{
	if (y < lines.size() - 3 && lines[y + 1][x] == 'M' && lines[y + 2][x] == 'A' && lines[y + 3][x] == 'S')
		return (1);
	return (0);
}

int	find_right(std::vector<std::string> lines, size_t y, size_t x)
{
	if (x < lines[y].size() - 3 && lines[y][x + 1] == 'M' && lines[y][x + 2] == 'A' && lines[y][x + 3] == 'S')
		return (1);
	return (0);
}

int	find_left(std::vector<std::string> lines, size_t y, size_t x)
{
	if (x > 2 && lines[y][x - 1] == 'M' && lines[y][x - 2] == 'A' && lines[y][x - 3] == 'S')
		return (1);
	return (0);
}

int	find_upright(std::vector<std::string> lines, size_t y, size_t x)
{
	if (y > 2 && x < lines[y].size() - 3 && lines[y - 1][x + 1] == 'M' && lines[y - 2][x + 2] == 'A' && lines[y - 3][x + 3] == 'S')
		return (1);
	return (0);
}

int	find_upleft(std::vector<std::string> lines, size_t y, size_t x)
{
	if (y > 2 && x > 2 && lines[y - 1][x - 1] == 'M' && lines[y - 2][x - 2] == 'A' && lines[y - 3][x - 3] == 'S')
		return (1);
	return (0);
}

int	find_downright(std::vector<std::string> lines, size_t y, size_t x)
{
	if (y < lines.size() - 3 && x < lines[y].size() - 3 && lines[y + 1][x + 1] == 'M' && lines[y + 2][x + 2] == 'A' && lines[y + 3][x + 3] == 'S')
		return (1);
	return (0);
}

int	find_downleft(std::vector<std::string> lines, size_t y, size_t x)
{
	if (y < lines.size() - 3 && x > 2 && lines[y + 1][x - 1] == 'M' && lines[y + 2][x - 2] == 'A' && lines[y + 3][x - 3] == 'S')
		return (1);
	return (0);
}

int	find2_up(std::vector<std::string> lines, size_t y, size_t x)
{
	if (lines[y - 1][x - 1] == 'M' && lines[y - 1][x + 1] == 'M' && lines[y + 1][x - 1] == 'S' && lines[y + 1][x + 1] == 'S')
		return (1);
	return (0);
}

int	find2_down(std::vector<std::string> lines, size_t y, size_t x)
{
	if (lines[y - 1][x - 1] == 'S' && lines[y - 1][x + 1] == 'S' && lines[y + 1][x - 1] == 'M' && lines[y + 1][x + 1] == 'M')
		return (1);
	return (0);
}

int	find2_right(std::vector<std::string> lines, size_t y, size_t x)
{
	if (lines[y - 1][x - 1] == 'M' && lines[y - 1][x + 1] == 'S' && lines[y + 1][x - 1] == 'M' && lines[y + 1][x + 1] == 'S')
		return (1);
	return (0);
}

int	find2_left(std::vector<std::string> lines, size_t y, size_t x)
{
	if (lines[y - 1][x - 1] == 'S' && lines[y - 1][x + 1] == 'M' && lines[y + 1][x - 1] == 'S' && lines[y + 1][x + 1] == 'M')
		return (1);
	return (0);
}

void	part1()
{
	int	result = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == 'X')
			{
				result += find_up(lines, i, j);
				// std::cout << i << ":" << j << "u   " << result << std::endl;
				result += find_down(lines, i, j);
				result += find_right(lines, i, j);
				result += find_left(lines, i, j);
				// std::cout << i << ":" << j << "l   " << result << std::endl;
				result += find_upright(lines, i, j);
				result += find_upleft(lines, i, j);
				result += find_downright(lines, i, j);
				result += find_downleft(lines, i, j);
				std::cout << i << ":" << j << "   " << result << std::endl;
			}
		}
	}
	// Close the file
	file.close();
	std::cout << result << std::endl;
}

void	part2()
{
	int	result = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	for (size_t i = 0; i < lines.size(); i++)
	{
		for (size_t j = 0; j < lines[i].size(); j++)
		{
			if (i > 0 && j > 0 && i < lines.size() - 1 && j < lines[i].size() - 1 && lines[i][j] == 'A')
			{
				result += find2_up(lines, i, j);
				result += find2_down(lines, i, j);
				result += find2_right(lines, i, j);
				result += find2_left(lines, i, j);
				std::cout << i << ":" << j << "   " << result << std::endl;
			}
		}
	}
	// Close the file
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