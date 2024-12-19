#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

#define MAP 71
#define FILE "input.txt"
#define BYTES 1024
// #define MAP 7
// #define FILE "test"
// #define BYTES 12
#define WIDTH 101
#define HEIGHT 103
// #define FILE "test"
// #define WIDTH 11
// #define HEIGHT 7
#define MOVES 100

#define EAST 1
#define WEST 2
#define NORTH 4
#define SOUTH 8



void	ok_score(std::vector<std::string> &map, size_t y, size_t x, std::vector<std::vector<long long>> &score, long long s, int dir)
{
	// std::cout << s << " " << dir << " y " << y << " x " << x << std::endl;
	// std::cout << " pos " << map[y][x] << " score " << score[y][x] << std::endl;
	if (score[y][x] <= s)
		return ;
	if (map[y][x] == '#')
		return ;
	score[y][x] = s;
	// std::cout << s << std::endl;
	if (map[y][x] == 'E')
		return ;
	if (dir & EAST)
	{
		ok_score(map, y, x + 1, score, s + 1, EAST);
		ok_score(map, y - 1, x, score, s + 1, NORTH);
		ok_score(map, y + 1, x, score, s + 1, SOUTH);
	}
	if (dir & WEST)
	{
		ok_score(map, y, x - 1, score, s + 1, WEST);
		ok_score(map, y - 1, x, score, s + 1, NORTH);
		ok_score(map, y + 1, x, score, s + 1, SOUTH);
	}
	if (dir & NORTH)
	{
		ok_score(map, y - 1, x, score, s + 1, NORTH);
		ok_score(map, y, x - 1 , score, s + 1, WEST);
		ok_score(map, y, x + 1, score, s + 1, EAST);
	}
	if (dir & SOUTH)
	{
		ok_score(map, y + 1, x, score, s + 1, SOUTH);
		ok_score(map, y, x - 1 , score, s + 1, WEST);
		ok_score(map, y, x + 1, score, s + 1, EAST);
	}
}

void	update_map(std::vector<std::string> &map, size_t y, size_t x, std::vector<std::vector<long long>> &score, long long s, int dir)
{
	// std::cout << s << " " << dir << " y " << y << " x " << x << std::endl;
	// std::cout << " pos " << map[y][x] << " score " << score[y][x] << std::endl;
	if (score[y][x] > s)
		return ;
	if (map[y][x] == '#')
		return ;
	map[y][x] = 'O';
	// std::cout << " hello? " << std::endl;
	if (dir & EAST)
	{
		update_map(map, y, x + 1, score, s - 1, EAST);
		update_map(map, y - 1, x, score, s - 1001, NORTH);
		update_map(map, y + 1, x, score, s - 1001, SOUTH);
	}
	if (dir & WEST)
	{
		update_map(map, y, x - 1, score, s - 1, WEST);
		update_map(map, y - 1, x, score, s - 1001, NORTH);
		update_map(map, y + 1, x, score, s - 1001, SOUTH);
	}
	if (dir & NORTH)
	{
		update_map(map, y - 1, x, score, s - 1, NORTH);
		update_map(map, y, x - 1 , score, s - 1001, WEST);
		update_map(map, y, x + 1, score, s - 1001, EAST);
	}
	if (dir & SOUTH)
	{
		update_map(map, y + 1, x, score, s - 1, SOUTH);
		update_map(map, y, x - 1 , score, s - 1001, WEST);
		update_map(map, y, x + 1, score, s - 1001, EAST);
	}
}

void	init_memory(std::vector<std::string> &lines, std::vector<std::vector<int>> &memory)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		size_t commaPos = lines[i].find(',');
		int firstNumber = std::stoi(lines[i].substr(0, commaPos));
		int secondNumber = std::stoi(lines[i].substr(commaPos + 1));
		memory.push_back({firstNumber, secondNumber});
		}
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
	std::vector<std::vector<int>> memory;
	std::vector<std::string> map;
	std::vector<std::vector<long long>> score;
	std::string			line;
	std::vector<long long> zeroes;
	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	// while (std::getline(file, line) && line[0]) {
	// 	// std::cout << line << std::endl;  // Prlong long each line to the console
	// 	lines.push_back(line);
	// }
	init_memory(lines, memory);
	size_t	i;
	size_t	j;
	for (i = 0; i < MAP + 2; i++)
	{
		line.clear();
		for (j = 0; j < MAP + 2; j++)
		{
			if (i == 0 || j == 0 || i == MAP + 1 || j == MAP + 1)
				line += '#';
			else if (i == MAP && j == MAP)
				line += 'E';
			else
				line += '.';
		}
		map.push_back(line);
	}
	for (i = 0; i < map.size(); i++)
	{
		std::cout << map[i] << std::endl;
	}
	for (i = 0; i < BYTES; i++)
	{
		std::cout << i <<std::endl;
		std::cout << memory[i][1] <<std::endl;
		std::cout << memory[i][0] <<std::endl;
		map[memory[i][1] + 1][memory[i][0] + 1] = '#';
		std::cout << i <<std::endl;
	}
	for (i = 0; i < map.size(); i++)
	{
		std::cout << map[i] << std::endl;
	}
	for (i = 0; i < map.size(); i++)
	{
		zeroes.clear();
		for (j = 0; j < map[i].size(); j++)
		{
			zeroes.push_back(999999999999999LL);
		}
		score.push_back(zeroes);
	}
	ok_score(map, 1, 1, score, 0LL, EAST);
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'E')
			{
				result = score[i][j];
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

	std::vector<std::string> lines;
	std::vector<std::vector<int>> memory;
	std::vector<std::string> map;
	std::vector<std::vector<long long>> score;
	std::string			line;
	std::vector<long long> zeroes;
	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	// while (std::getline(file, line) && line[0]) {
	// 	// std::cout << line << std::endl;  // Prlong long each line to the console
	// 	lines.push_back(line);
	// }
	init_memory(lines, memory);
	size_t	i;
	size_t	j;
	for (i = 0; i < MAP + 2; i++)
	{
		line.clear();
		for (j = 0; j < MAP + 2; j++)
		{
			if (i == 0 || j == 0 || i == MAP + 1 || j == MAP + 1)
				line += '#';
			else if (i == MAP && j == MAP)
				line += 'E';
			else
				line += '.';
		}
		map.push_back(line);
	}
	for (i = 0; i < BYTES; i++)
	{
		map[memory[i][1] + 1][memory[i][0] + 1] = '#';
	}
	size_t iter;
	for (iter = BYTES; ; iter++)
	{
		map[memory[iter][1] + 1][memory[iter][0] + 1] = '#';
		for (i = 0; i < map.size(); i++)
		{
			std::cout << map[i] << std::endl;
		}
		score.clear();
		for (i = 0; i < map.size(); i++)
		{
			zeroes.clear();
			for (j = 0; j < map[i].size(); j++)
			{
				zeroes.push_back(999999999999999LL);
			}
			score.push_back(zeroes);
		}
		ok_score(map, 1, 1, score, 0LL, EAST);
		for (i = 0; i < map.size(); i++)
		{
			for (j = 0; j < map[i].size(); j++)
			{
				if (map[i][j] == 'E')
				{
					result = score[i][j];
				}
			}
		}
		if (result == 999999999999999LL)
			break ;
	}
	std::cout << memory[iter][0] << "," << memory[iter][1] <<std::endl;
	file.close();
}

int	main(void)
{
	//part1
	part1();
	//part2
	part2();
	return (0);
}