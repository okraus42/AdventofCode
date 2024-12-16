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

#define EAST 1
#define WEST 2
#define NORTH 4
#define SOUTH 8



void	ok_score(std::vector<std::string> &map, size_t y, size_t x, std::vector<std::vector<long long>> &score, long long s, int dir)
{
	// std::cout << s << " " << dir << " y " << y << " x " << x << std::endl;
	// std::cout << " pos " << map[y][x] << " score " << score[y][x] << std::endl;
	if (score[y][x] < s)
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
		ok_score(map, y - 1, x, score, s + 1001, NORTH);
		ok_score(map, y + 1, x, score, s + 1001, SOUTH);
	}
	if (dir & WEST)
	{
		ok_score(map, y, x - 1, score, s + 1, WEST);
		ok_score(map, y - 1, x, score, s + 1001, NORTH);
		ok_score(map, y + 1, x, score, s + 1001, SOUTH);
	}
	if (dir & NORTH)
	{
		ok_score(map, y - 1, x, score, s + 1, NORTH);
		ok_score(map, y, x - 1 , score, s + 1001, WEST);
		ok_score(map, y, x + 1, score, s + 1001, EAST);
	}
	if (dir & SOUTH)
	{
		ok_score(map, y + 1, x, score, s + 1, SOUTH);
		ok_score(map, y, x - 1 , score, s + 1001, WEST);
		ok_score(map, y, x + 1, score, s + 1001, EAST);
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

void	part1()
{
	long long	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	// std::vector<std::string> lines;
	std::vector<std::string> map;
	std::vector<std::vector<long long>> score;
	std::string			line;
	std::vector<long long> zeroes;
	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		map.push_back(line);
	}
	// while (std::getline(file, line) && line[0]) {
	// 	// std::cout << line << std::endl;  // Prlong long each line to the console
	// 	lines.push_back(line);
	// }
	size_t	i;
	size_t	j;
	for (i = 0; i < map.size(); i++)
	{
		zeroes.clear();
		for (j = 0; j < map[i].size(); j++)
		{
			zeroes.push_back(999999999999999LL);
		}
		score.push_back(zeroes);
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'S')
			{
				ok_score(map, i, j, score, 0LL, EAST);
			}
		}
	}
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

	// std::vector<std::string> lines;
	std::vector<std::string> map;
	std::vector<std::vector<long long>> score;
	std::string			line;
	std::vector<long long> zeroes;
	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		map.push_back(line);
	}
	// while (std::getline(file, line) && line[0]) {
	// 	// std::cout << line << std::endl;  // Prlong long each line to the console
	// 	lines.push_back(line);
	// }
	size_t	i;
	size_t	j;
	for (i = 0; i < map.size(); i++)
	{
		zeroes.clear();
		for (j = 0; j < map[i].size(); j++)
		{
			zeroes.push_back(999999999999999LL);
		}
		score.push_back(zeroes);
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'S')
			{
				ok_score(map, i, j, score, 0LL, EAST);
			}
		}
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'E')
			{
				map[i][j] = 'O';
				update_map(map, i + 1, j, score, score[i][j] - 1, SOUTH);
				update_map(map, i, j - 1, score, score[i][j] - 1, WEST);
			}
		}
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'O')
			{
				result += 1;
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