#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

void	move_up(std::vector<std::string> &lines, size_t y, size_t x, int *exit);
void	move_right(std::vector<std::string> &lines, size_t y, size_t x, int *exit);
void	move_down(std::vector<std::string> &lines, size_t y, size_t x, int *exit);
void	move_left(std::vector<std::string> &lines, size_t y, size_t x, int *exit);


void	move_up(std::vector<std::string> &lines, size_t y, size_t x, int *exit)
{
	if (*exit)
		return ;
	while (y > 0 && lines[y - 1][x] != '#')
	{
		lines[y][x] = 'X';
		y--;
	}
	if (y == 0)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_right(lines, y, x, exit);
	}
}

void	move_right(std::vector<std::string> &lines, size_t y, size_t x, int *exit)
{
	if (*exit)
		return ;
	while (x < lines[y].size() - 1 && lines[y][x + 1] != '#')
	{
		lines[y][x] = 'X';
		x++;
	}
	if (x == lines[y].size() - 1)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_down(lines, y, x, exit);
	}
}

void	move_down(std::vector<std::string> &lines, size_t y, size_t x, int *exit)
{
	if (*exit)
		return ;
	while (y < lines.size() - 1 && lines[y + 1][x] != '#')
	{
		lines[y][x] = 'X';
		y++;
	}
	if (y == lines.size() - 1)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_left(lines, y, x, exit);
	}
}

void	move_left(std::vector<std::string> &lines, size_t y, size_t x, int *exit)
{
	if (*exit)
		return ;
	while (x > 0 && lines[y][x - 1] != '#')
	{
		lines[y][x] = 'X';
		x--;
	}
	if (x == 0)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_up(lines, y, x, exit);
	}
}

void	move_up2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop);
void	move_right2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop);
void	move_down2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop);
void	move_left2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop);


void	move_up2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop)
{
	if (*exit || *loop)
		return ;
	while (y > 0 && lines[y - 1][x] != '#')
	{
		if (lines[y][x] == 'X')
			lines[y][x] = 'x';
		else if (lines[y][x] == 'x')
			lines[y][x] = 'l';
		else if (lines[y][x] == 'l')
			lines[y][x] = 'L';
		else if (lines[y][x] == 'L')
			*loop += 1;
		else
			lines[y][x] = 'X';
		y--;
	}
	if (y == 0)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_right2(lines, y, x, exit, loop);
	}
}

void	move_right2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop)
{
	if (*exit || *loop)
		return ;
	while (x < lines[y].size() - 1 && lines[y][x + 1] != '#')
	{
		if (lines[y][x] == 'X')
			lines[y][x] = 'x';
		else if (lines[y][x] == 'x')
			lines[y][x] = 'l';
		else if (lines[y][x] == 'l')
			lines[y][x] = 'L';
		else if (lines[y][x] == 'L')
			*loop += 1;
		else
			lines[y][x] = 'X';
		x++;
	}
	if (x == lines[y].size() - 1)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_down2(lines, y, x, exit, loop);
	}
}

void	move_down2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop)
{
	if (*exit || *loop)
		return ;
	while (y < lines.size() - 1 && lines[y + 1][x] != '#')
	{
		if (lines[y][x] == 'X')
			lines[y][x] = 'x';
		else if (lines[y][x] == 'x')
			lines[y][x] = 'l';
		else if (lines[y][x] == 'l')
			lines[y][x] = 'L';
		else if (lines[y][x] == 'L')
			*loop += 1;
		else
			lines[y][x] = 'X';
		y++;
	}
	if (y == lines.size() - 1)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_left2(lines, y, x, exit, loop);
	}
}

void	move_left2(std::vector<std::string> &lines, size_t y, size_t x, int *exit, int *loop)
{
	if (*exit || *loop)
		return ;
	while (x > 0 && lines[y][x - 1] != '#')
	{
		if (lines[y][x] == 'X')
			lines[y][x] = 'x';
		else if (lines[y][x] == 'x')
			lines[y][x] = 'l';
		else if (lines[y][x] == 'l')
			lines[y][x] = 'L';
		else if (lines[y][x] == 'L')
			*loop += 1;
		else
			lines[y][x] = 'X';
		x--;
	}
	if (x == 0)
	{
		lines[y][x] = 'X';
		*exit = 1;
	}
	else
	{
		move_up2(lines, y, x, exit, loop);
	}
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
	int		exit = 0;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	size_t i;
	size_t j;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '^')
			{
				break;
			}
		}
		if (j != lines[i].size())
			break ;
	}
	std::cout << "i " << i << "j " << j << std::endl;

	move_up(lines, i, j, &exit);
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == 'X')
			{
				result += 1;
			}
		}
		if (j != lines[i].size())
			break ;
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
	std::vector<std::string> lines2;
	std::string			line;
	int		exit;
	int		loop;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	size_t i;
	size_t j;
	for (i = 0; i < lines.size(); i++)
	{
		for (j = 0; j < lines[i].size(); j++)
		{
			if (lines[i][j] == '^')
			{
				break;
			}
		}
		if (j != lines[i].size())
			break ;
	}
	std::cout << "i " << i << "j " << j << std::endl;
	size_t y;
	size_t x;
	for (y = 0; y < lines.size(); y++)
	{
		for (x = 0; x < lines[i].size(); x++)
		{
			if (lines[y][x] == '.')
			{
				lines2.clear();
				for (size_t l = 0; l < lines.size(); l++)
					lines2.push_back(lines[l]);
				lines2[y][x] = '#';
				loop = 0;
				exit = 0;
				move_up2(lines2, i, j, &exit, &loop);
				if (loop)
				{
					lines2[y][x] = 'O';
					for (size_t l = 0; l < lines2.size(); l++)
						std::cout << lines2[l] << std::endl;
					std::cout << std::endl;
					result += 1;
				}
				lines2[y][x] = '.';
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