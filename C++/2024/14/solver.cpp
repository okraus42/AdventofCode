#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

#define MAP 50
#define FILE "input.txt"
#define WIDTH 101
#define HEIGHT 103
// #define FILE "test"
// #define WIDTH 11
// #define HEIGHT 7
#define MOVES 100

void	extract_numbers(std::string line, long long &x, long long &y, long long &vx, long long &vy)
{
	line = line.substr(line.find('=') + 1);
	x = std::stoi(line);
	line = line.substr(line.find(',') + 1);
	y = std::stoi(line);
	line = line.substr(line.find('=') + 1);
	vx = std::stoi(line);
	line = line.substr(line.find(',') + 1);
	vy = std::stoi(line);
}

int	find_quadrant(std::string line)
{
	long long x;
	long long y;
	long long vx;
	long long vy;


	extract_numbers(line, x, y, vx, vy);
	std::cout << "x " << x << ", y " << y << ", vx " << vx << ", vy " << vy << std::endl;
	x += (vx * MOVES);
	y += (vy * MOVES);
	x %= WIDTH;
	y %= HEIGHT;
	if (x < 0)
		x += WIDTH;
	if (y < 0)
		y += HEIGHT;
	std::cout << "x " << x << ", y " << y << std::endl;
	if (x < WIDTH / 2 && y < HEIGHT / 2)
		return (1);
	if (x > WIDTH / 2 && y < HEIGHT / 2)
		return (2);
	if (x < WIDTH / 2 && y > HEIGHT / 2)
		return (3);
	if (x > WIDTH / 2 && y > HEIGHT / 2)
		return (4);
	return (0);
}

std::vector<int>	find_coords(std::string line, size_t iter)
{
	long long x;
	long long y;
	long long vx;
	long long vy;
	std::vector<int> coords;


	extract_numbers(line, x, y, vx, vy);
	// std::cout << "x " << x << ", y " << y << ", vx " << vx << ", vy " << vy << std::endl;
	x += (vx * iter);
	y += (vy * iter);
	x %= WIDTH;
	y %= HEIGHT;
	if (x < 0)
		x += WIDTH;
	if (y < 0)
		y += HEIGHT;
	// std::cout << "x " << x << ", y " << y << std::endl;
	coords.push_back(y);
	coords.push_back(x);
	return (coords);
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

	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	size_t i;
	long long	quadrant1 = 0;
	long long	quadrant2 = 0;
	long long	quadrant3 = 0;
	long long	quadrant4 = 0;
	int			q;
	std::set<long long> locations;
	for (i = 0; i < lines.size(); i++)
	{
		q = find_quadrant(lines[i]);
		if (q == 1)
			quadrant1++;
		else if (q == 2)
			quadrant2++;
		else if (q == 3)
			quadrant3++;
		else if (q == 4)
			quadrant4++;
	}
	result = quadrant1 * quadrant2 * quadrant3 * quadrant4;
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
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	size_t i;
	size_t j;
	std::vector<std::string> map;
	std::string str;
	std::vector<int> coords;
	std::set<long long> locations;
	for (j = 0; j < 10000; j++)
	{
		map.clear();
		str.clear();
		for (i = 0; i < WIDTH; i++)
		{
			str += " ";
		}
		for (i = 0; i < HEIGHT; i++)
		{
			map.push_back(str);
		}
		for (i = 0; i < lines.size(); i++)
		{
			coords = find_coords(lines[i], j);
			map[coords[1]][coords[0]] = '#';
		}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << j << std::endl;
		for (i = 0; i < map.size(); i++)
		{
			std::cout << map[i] << std::endl;
		}
		std::cout << std::endl;
	}
	result = j;
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