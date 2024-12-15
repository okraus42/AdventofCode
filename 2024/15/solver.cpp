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


void	move_left(std::vector<std::string> &map, size_t &y, size_t &x)
{
	int	temp;
	if (map[y][x - 1] == '.')
	{
		x--;
	}
	else if (map[y][x - 1] == 'O')
	{
		temp = (x - 1);
		while (map[y][temp] == 'O')
			temp--;
		if (map[y][temp] == '.')
		{
			map[y][temp] = 'O';
			map[y][x - 1] = '.';
			x--;
		}
	}
}

void	move_right(std::vector<std::string> &map, size_t &y, size_t &x)
{
	int	temp;
	if (map[y][x + 1] == '.')
	{
		x++;
	}
	else if (map[y][x + 1] == 'O')
	{
		temp = (x + 1);
		while (map[y][temp] == 'O')
			temp++;
		if (map[y][temp] == '.')
		{
			map[y][temp] = 'O';
			map[y][x + 1] = '.';
			x++;
		}
	}
}

void	move_up(std::vector<std::string> &map, size_t &y, size_t &x)
{
	int	temp;
	if (map[y - 1][x] == '.')
	{
		y--;
	}
	else if (map[y - 1][x] == 'O')
	{
		temp = (y - 1);
		while (map[temp][x] == 'O')
			temp--;
		if (map[temp][x] == '.')
		{
			map[temp][x] = 'O';
			map[y - 1][x] = '.';
			y--;
		}
	}
}

void	move_down(std::vector<std::string> &map, size_t &y, size_t &x)
{
	int	temp;
	if (map[y + 1][x] == '.')
	{
		y++;
	}
	else if (map[y + 1][x] == 'O')
	{
		temp = (y + 1);
		while (map[temp][x] == 'O')
			temp++;
		if (map[temp][x] == '.')
		{
			map[temp][x] = 'O';
			map[y + 1][x] = '.';
			y++;
		}
	}
}

void	print(std::vector<std::string> &map, size_t y, size_t x)
{
	size_t	i;
	map[y][x] = '@';
	for (i = 0; i < map.size(); i++)
	{
		std::cout << map[i] << std::endl;
	}
	std::cout << std::endl;
	map[y][x] = '.';

}

void	move_robot(std::vector<std::string> &map, std::vector<std::string> &lines, size_t y, size_t x)
{
	size_t	i;
	size_t	j;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '<')
			{
				move_left(map, y, x);
			}
			else if (lines[i][j] == '>')
			{
				move_right(map, y, x);
			}
			else if (lines[i][j] == '^')
			{
				move_up(map, y, x);
			}
			else if (lines[i][j] == 'v')
			{
				move_down(map, y, x);
			}
			std::cout << lines[i][j] << std::endl;
			print(map, y, x);
		}
	}
}

void	move_box_left(std::vector<std::string> &map, size_t y, size_t x)
{
	if (map[y][x] == '[' || map[y][x] == ']')
	{
		if (map[y][x - 1] == '[' || map[y][x - 1] == ']')
			move_box_left(map, y, x - 1);
		if (map[y][x - 1] == '.')
		{
			map[y][x - 1] = map[y][x];
			map[y][x] = '.';
		}
	}
}

void	move_left2(std::vector<std::string> &map, size_t &y, size_t &x)
{
	move_box_left(map, y, x - 1);
	if (map[y][x - 1] == '.')
		x--;
}

void	move_box_right(std::vector<std::string> &map, size_t y, size_t x)
{
	if (map[y][x] == '[' || map[y][x] == ']')
	{
		if (map[y][x + 1] == '[' || map[y][x + 1] == ']')
			move_box_right(map, y, x + 1);
		if (map[y][x + 1] == '.')
		{
			map[y][x + 1] = map[y][x];
			map[y][x] = '.';
		}
	}
}

void	move_right2(std::vector<std::string> &map, size_t &y, size_t &x)
{
	move_box_right(map, y, x + 1);
	if (map[y][x + 1] == '.')
		x++;
}

void	check_wall_up(std::vector<std::string> &map, size_t y, size_t x, int &wall)
{
	if (map[y][x] == '[')
	{
		check_wall_up(map, y - 1, x, wall);
		check_wall_up(map, y - 1, x + 1, wall);
	}
	if (map[y][x] == ']')
	{
		check_wall_up(map, y - 1, x, wall);
		check_wall_up(map, y - 1, x - 1, wall);
	}
	if (map[y][x] == '#')
		wall = 1;
}

void	move_box_up(std::vector<std::string> &map, size_t y, size_t x)
{
	if (map[y][x] == '[')
	{
		move_box_up(map, y - 1, x);
		move_box_up(map, y - 1, x + 1);
		map[y - 1][x] = '[';
		map[y - 1][x + 1] = ']';
		map[y][x] = '.';
		map[y][x + 1] = '.';
	}
	if (map[y][x] == ']')
	{
		move_box_up(map, y - 1, x);
		move_box_up(map, y - 1, x - 1);
		map[y - 1][x] = ']';
		map[y - 1][x - 1] = '[';
		map[y][x] = '.';
		map[y][x - 1] = '.';
	}
}

void	move_up2(std::vector<std::string> &map, size_t &y, size_t &x)
{
	int	wall = 0;
	check_wall_up(map, y - 1, x, wall);
	if (!wall)
	{
		move_box_up(map, y - 1, x);
		y--;
	}
}

void	check_wall_down(std::vector<std::string> &map, size_t y, size_t x, int &wall)
{
	if (map[y][x] == '[')
	{
		check_wall_down(map, y + 1, x, wall);
		check_wall_down(map, y + 1, x + 1, wall);
	}
	if (map[y][x] == ']')
	{
		check_wall_down(map, y + 1, x, wall);
		check_wall_down(map, y + 1, x - 1, wall);
	}
	if (map[y][x] == '#')
		wall = 1;
}

void	move_box_down(std::vector<std::string> &map, size_t y, size_t x)
{
	if (map[y][x] == '[')
	{
		move_box_down(map, y + 1, x);
		move_box_down(map, y + 1, x + 1);
		map[y + 1][x] = '[';
		map[y + 1][x + 1] = ']';
		map[y][x] = '.';
		map[y][x + 1] = '.';
	}
	if (map[y][x] == ']')
	{
		move_box_down(map, y + 1, x);
		move_box_down(map, y + 1, x - 1);
		map[y + 1][x] = ']';
		map[y + 1][x - 1] = '[';
		map[y][x] = '.';
		map[y][x - 1] = '.';
	}
}

void	move_down2(std::vector<std::string> &map, size_t &y, size_t &x)
{
	int	wall = 0;
	check_wall_down(map, y + 1, x, wall);
	if (!wall)
	{
		move_box_down(map, y + 1, x);
		y++;
	}
}

void	move_robot2(std::vector<std::string> &map, std::vector<std::string> &lines, size_t y, size_t x)
{
	size_t	i;
	size_t	j;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '<')
			{
				move_left2(map, y, x);
			}
			else if (lines[i][j] == '>')
			{
				move_right2(map, y, x);
			}
			else if (lines[i][j] == '^')
			{
				move_up2(map, y, x);
			}
			else if (lines[i][j] == 'v')
			{
				move_down2(map, y, x);
			}
			std::cout << lines[i][j] << std::endl;
			print(map, y, x);
		}
	}
}

void	update_map(std::vector<std::string> &map, std::vector<std::string> &map2)
{
	size_t	i;
	size_t	j;
	std::string	str;
	for (i = 0; i < map2.size(); i++)
	{
		str = "";
		for (j = 0; j < map2[i].size(); j++)
		{
			if (map2[i][j] == '#')
			{
				str += "##";
			}
			else if (map2[i][j] == 'O')
			{
				str += "[]";
			}
			else if (map2[i][j] == '.')
			{
				str += "..";
			}
			else if (map2[i][j] == '@')
			{
				str += "@.";
			}
		}
		map.push_back(str);
	}
	print(map, 0, 0);
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
	std::vector<std::string> map;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		map.push_back(line);
	}
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	size_t	i;
	size_t	j;
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == '@')
			{
				map[i][j] = '.';
				move_robot(map, lines, i, j);
			}
		}
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'O')
				result += 100 * i + j;
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
	std::vector<std::string> map;
	std::vector<std::string> map2;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		map2.push_back(line);
	}
	update_map(map, map2);
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	size_t	i;
	size_t	j;
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == '@')
			{
				map[i][j] = '.';
				move_robot2(map, lines, i, j);
			}
		}
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == '[')
				result += 100 * i + j;
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