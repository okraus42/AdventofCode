#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

#define MAP 50
#define FILE "input.txt"

void	verify1(std::set<int> &locations, int i, int j, int y, int x)
{
	int dx = x - j;
	int dy = y - i;
	int y1 = i - dy;
	int x1 = j - dx;
	int y2 = y + dy;
	int x2 = x + dx;
	if (x1 >= 0 && x1 < MAP && y1 >= 0 && y1 < MAP)
	{
		locations.insert(x1 * 2500 + y1);
	}
	if (x2 >= 0 && x2 < MAP && y2 >= 0 && y2 < MAP)
	{
		locations.insert(x2 * 2500 + y2);
	}
}

void	verify2(std::set<int> &locations, int i, int j, int y, int x)
{
	int dx = x - j;
	int dy = y - i;
	int y1 = i - dy;
	int x1 = j - dx;
	int y2 = y + dy;
	int x2 = x + dx;
	locations.insert(x * 2500 + y);
	locations.insert(j * 2500 + i);
	while (x1 >= 0 && x1 < MAP && y1 >= 0 && y1 < MAP)
	{
		locations.insert(x1 * 2500 + y1);
		y1 -= dy;
		x1 -= dx;
	}
	while (x2 >= 0 && x2 < MAP && y2 >= 0 && y2 < MAP)
	{
		locations.insert(x2 * 2500 + y2);
		y2 += dy;
		x2 += dx;
	}
}

void	part1()
{
	int	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	size_t i;
	size_t j;
	size_t	x = lines[0].size();
	size_t y = lines.size();
	std::cout << x << " " << y << std::endl;
	(void)x;
	(void)y;
	std::set<int> locations;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[0].size(); j++)
		{
			if (std::isalnum(lines[i][j]))
			{
				for (y = i; y < lines.size(); y++)
				{
					for (x = 0; x < lines[0].size(); x++)
					{
						if (lines[y][x] == lines[i][j])
						{
							if (y > i || x > j)
							{
								verify1(locations, i, j, y, x);
							}
						}
					}
				}
			}
		}
	}
	result = locations.size();
	file.close();
	std::cout << result << std::endl;
}
void	part2()
{
	int	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	size_t i;
	size_t j;
	size_t	x = lines[0].size();
	size_t y = lines.size();
	std::cout << x << " " << y << std::endl;
	(void)x;
	(void)y;
	std::set<int> locations;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[0].size(); j++)
		{
			if (std::isalnum(lines[i][j]))
			{
				// std::cout << lines[i][j] << std::endl;
				for (y = i; y < lines.size(); y++)
				{
					for (x = 0; x < lines[0].size(); x++)
					{
						if (lines[y][x] == lines[i][j])
						{
							if (y > i || x > j)
							{
								// std::cout << lines[y][x] << std::endl;
								verify2(locations, i, j, y, x);
							}
						}
					}
				}
			}
		}
	}
	result = locations.size();
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