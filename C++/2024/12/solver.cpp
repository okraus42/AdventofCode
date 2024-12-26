#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

#define MAP 50
#define FILE "input.txt"

int	get_area(std::vector<std::string> &lines, int y, int x, char c)
{
	// std::cout << "Ay " << y << " x " << x << std::endl;
	int area;
	if (y < 0 || y >= (int)lines.size() || x < 0 || x >= (int)lines[y].size())
	{
		return (0);
	}
	if (lines[y][x] != c)
		return (0);
	if (lines[y][x] == '1')
		return (0);
	area = 1;
	lines[y][x] = '1';
	area += get_area(lines, y + 1, x, c);
	area += get_area(lines, y - 1, x, c);
	area += get_area(lines, y, x + 1, c);
	area += get_area(lines, y, x - 1, c);
	return (area);
}

int	get_perimeter(std::vector<std::string> &lines, int y, int x, char c)
{
	// std::cout << "Py " << y << " x " << x << std::endl;
	int perimeter = 0;
	if (y < 0 || y >= (int)lines.size() || x < 0 || x >= (int)lines[y].size())
	{
		return (0);
	}
	if (lines[y][x] != '1')
		return (0);
	if (y == 0 || (lines[y - 1][x] != '1' && lines[y - 1][x] != std::tolower(c)))
		perimeter += 1;
	if (y >= (int)lines.size() - 1 || (lines[y + 1][x] != '1' && lines[y + 1][x] != std::tolower(c)))
		perimeter += 1;
	if (x == 0 || (lines[y][x - 1] != '1' && lines[y][x - 1] != std::tolower(c)))
		perimeter += 1;
	if (x >= (int)lines[y].size() - 1 || (lines[y][x + 1] != '1' && lines[y][x + 1] != std::tolower(c)))
		perimeter += 1;
	// std::cout << perimeter << std::endl;
	lines[y][x] = std::tolower(c);
	perimeter += get_perimeter(lines, y + 1, x, c);
	perimeter += get_perimeter(lines, y - 1, x, c);
	perimeter += get_perimeter(lines, y, x + 1, c);
	perimeter += get_perimeter(lines, y, x - 1, c);
	return (perimeter);
}

void	fill_area(std::vector<std::string> &lines, int y, int x, char c)
{
	// std::cout << "Ay " << y << " x " << x << std::endl;
	if (y < 0 || y >= (int)lines.size() || x < 0 || x >= (int)lines[y].size())
	{
		return ;
	}
	if (lines[y][x] != c)
		return ;
	if (lines[y][x] == '2')
		return ;
	lines[y][x] = '2';
	fill_area(lines, y + 1, x, c);
	fill_area(lines, y - 1, x, c);
	fill_area(lines, y, x + 1, c);
	fill_area(lines, y, x - 1, c);
}

// int	check_e_side_n(std::vector<std::string> &lines, int y, int x, char c)
// {
// 	while (y >= 0 && lines[y][x] == c && (x == (int)lines[y].size() - 1 || (lines[y][x + 1] != c || lines[y][x + 1] != std::tolower(c))))
// 		y--;
// 	if (y < 0)
// 		return (0);
// 	if (lines[y][x] == std::tolower(c) && (x == (int)lines[y].size() - 1 || (lines[y][x + 1] != c || lines[y][x + 1] != std::tolower(c))))
// 		return (1);
// 	return (0);
// }

// int	check_e_side_s(std::vector<std::string> &lines, int y, int x, char c)
// {
// 	while (y < (int)lines.size() && lines[y][x] == c && (x == (int)lines[y].size() - 1 || (lines[y][x + 1] != c || lines[y][x + 1] != std::tolower(c))))
// 		y++;
// 	if (y == (int)lines.size())
// 		return (0);
// 	if (lines[y][x] == std::tolower(c) && (x == (int)lines[y].size() - 1 || (lines[y][x + 1] != c || lines[y][x + 1] != std::tolower(c))))
// 		return (1);
// 	return (0);
// }

// int	check_w_side_n(std::vector<std::string> &lines, int y, int x, char c)
// {
// 	while (y >= 0 && lines[y][x] == c && (x == 0 || (lines[y][x - 1] != c || lines[y][x - 1] != std::tolower(c))))
// 		y--;
// 	if (y < 0)
// 		return (0);
// 	if (lines[y][x] == std::tolower(c) && (x == 0 || (lines[y][x - 1] != c || lines[y][x - 1] != std::tolower(c))))
// 		return (1);
// 	return (0);
// }

// int	check_w_side_s(std::vector<std::string> &lines, int y, int x, char c)
// {
// 	while (y < (int)lines.size() && lines[y][x] == c && (x == 0 || (lines[y][x - 1] != c || lines[y][x - 1] != std::tolower(c))))
// 		y++;
// 	if (y == (int)lines.size())
// 		return (0);
// 	if (lines[y][x] == std::tolower(c) && (x == 0 || (lines[y][x - 1] != c || lines[y][x - 1] != std::tolower(c))))
// 		return (1);
// 	return (0);
// }


// /get corners
// int	get_sides(std::vector<std::string> &lines, int y, int x, char c)
// {
// 	int sides = 0;
// 	if (y < 0 || y >= (int)lines.size() || x < 0 || x >= (int)lines[y].size())
// 	{
// 		return (0);
// 	}
// 	if (lines[y][x] != '1')
// 		return (0);
// 	std::cout << "Sy " << y << " x " << x << std::endl;
// 	if (y == 0 || (lines[y - 1][x] != '1' && lines[y - 1][x] != std::tolower(c)))
// 	{
// 		if (((x > 0 && lines[y][x - 1] == std::tolower(c)) && (y == 0 || (lines[y - 1][x - 1] != '1' && lines[y - 1][x - 1] != std::tolower(c))))|| ((x < (int)lines[y].size() - 1  && lines[y][x + 1] == std::tolower(c)) && (y == 0 || (lines[y - 1][x + 1] != '1' && lines[y - 1][x + 1] != std::tolower(c)))))
// 			sides = sides;
// 		else
// 			sides += 1;
// 	}
// 	if (y >= (int)lines.size() - 1 || (lines[y + 1][x] != '1' && lines[y + 1][x] != std::tolower(c)))
// 	{
// 		if (((x > 0 && lines[y][x - 1] == std::tolower(c)) && (y >= (int)lines.size() - 1 || (lines[y + 1][x - 1] != '1' && lines[y + 1][x - 1] != std::tolower(c)))) || ((x < (int)lines[y].size() - 1  && lines[y][x + 1] == std::tolower(c)) && (y >= (int)lines.size() - 1 || (lines[y + 1][x + 1] != '1' && lines[y + 1][x + 1] != std::tolower(c)))))
// 			sides = sides;
// 		else
// 			sides += 1;
// 	}
// 	if (x == 0 || (lines[y][x - 1] != '1' && lines[y][x - 1] != std::tolower(c)))
// 	{
// 		if ((y > 0 && (lines[y - 1][x] == std::tolower(c)) && (x == 0 || (lines[y - 1][x - 1] != '1' && lines[y - 1][x - 1] != std::tolower(c)))) || ((y < (int)lines.size() - 1  && lines[y + 1][x] == std::tolower(c)) && (x == 0 || (lines[y + 1][x - 1] != '1' && lines[y + 1][x - 1] != std::tolower(c)))))
// 			sides = sides;
// 		else if (check_w_side_n(lines, y - 1, x, c) || check_w_side_s(lines, y + 1, x, c))
// 			sides = sides;
// 		else
// 			sides += 1;
// 	}
// 	if (x >= (int)lines[y].size() - 1 || (lines[y][x + 1] != '1' && lines[y][x + 1] != std::tolower(c)))
// 	{
// 		// std::cout << "end" << std::endl;
// 		if (((y > 0 && lines[y - 1][x] == std::tolower(c)) && (x >= (int)lines[y].size() - 1 || (lines[y - 1][x + 1] != '1' && lines[y - 1][x + 1] != std::tolower(c)))) || ((y < (int)lines.size() - 1 && lines[y + 1][x] == std::tolower(c)) && (x >= (int)lines[y].size() - 1 || (lines[y + 1][x + 1] != '1' && lines[y + 1][x + 1] != std::tolower(c)))))
// 			sides = sides;
// 		else if (check_e_side_n(lines, y - 1, x, c) || check_e_side_s(lines, y + 1, x, c))
// 			sides = sides;
// 		else
// 			sides += 1;
// 	}
// 	std::cout << sides << std::endl;
// 	lines[y][x] = std::tolower(c);
// 	sides += get_sides(lines, y + 1, x, c);
// 	sides += get_sides(lines, y - 1, x, c);
// 	sides += get_sides(lines, y, x + 1, c);
// 	sides += get_sides(lines, y, x - 1, c);
// 	return (sides);
// }

int	get_corners(std::vector<std::string> &lines, int y, int x, char c)
{
	int corners = 0;
	int up = 0;
	int	down = 0;
	int	left = 0;
	int	right = 0;
	if (y < 0 || y >= (int)lines.size() || x < 0 || x >= (int)lines[y].size())
	{
		return (0);
	}
	if (lines[y][x] != '1')
		return (0);
	if (x == 0 || (std::toupper(lines[y][x - 1]) != c && lines[y][x - 1] != '1'))
	{
		left = 1;
	}
	if (x == (int)lines[y].size() - 1 || (std::toupper(lines[y][x + 1]) != c && lines[y][x + 1] != '1'))
	{
		right = 1;
	}
	if (y == 0 || (std::toupper(lines[y - 1][x]) != c && lines[y - 1][x] != '1'))
	{
		up = 1;
	}
	if (y == (int)lines.size() - 1 || (std::toupper(lines[y + 1][x]) != c && lines[y + 1][x] != '1'))
	{
		down = 1;
	}
	// if (left + right + up + down == 1 && (x != 0 && x != (int)lines[y].size() - 1 && y != 0 && y != (int)lines.size() - 1))
	// 	corners = 1;
	if (left && up)
		corners += 1;
	if (right && up)
		corners += 1;
	if (left && down)
		corners += 1;
	if (right && down)
		corners += 1;
	if (!left && !up && x != 0 && y != 0 && (std::toupper(lines[y - 1][x - 1]) != c && lines[y - 1][x - 1] != '1'))
		corners += 1;
	if (!right && !up && x != (int)lines[y].size() - 1 && y != 0 && (std::toupper(lines[y - 1][x + 1]) != c && lines[y - 1][x + 1] != '1'))
		corners += 1;
	if (!left && !down && x != 0 && y != (int)lines.size() - 1 && (std::toupper(lines[y + 1][x - 1]) != c && lines[y + 1][x - 1] != '1'))
		corners += 1;
	if (!right && !down && x != (int)lines[y].size() - 1 && y != (int)lines.size() - 1 && (std::toupper(lines[y + 1][x + 1]) != c && lines[y + 1][x + 1] != '1'))
		corners += 1;
	// std::cout << "Cy " << y << " x " << x << std::endl;
	// std::cout << "c " << corners << std::endl;
	// std::cout << "l " << left << std::endl;
	// std::cout << "r " << right << std::endl;
	// std::cout << "u " << up << std::endl;
	// std::cout << "d " << down << std::endl;
	lines[y][x] = std::tolower(c);
	corners += get_corners(lines, y + 1, x, c);
	corners += get_corners(lines, y - 1, x, c);
	corners += get_corners(lines, y, x + 1, c);
	corners += get_corners(lines, y, x - 1, c);
	return (corners);
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
			if (std::isupper(lines[i][j]))
			{
				char c = lines[i][j];
				// std::cout << "y " << i << " x " << j << " c " << c << std::endl;
				long long area = get_area(lines, i, j, c);
				// std::cout << area << std::endl;
				long long perimeter = get_perimeter(lines, i, j, c);
				// std::cout << perimeter << std::endl;
				result += area * perimeter;
			}
		}
	}
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
			if (std::isupper(lines[i][j]))
			{
				char c = lines[i][j];
				// std::cout << "y " << i << " x " << j << " c " << c << std::endl;
				long long area = get_area(lines, i, j, c);
				// std::cout << area << std::endl;
				long long sides = get_corners(lines, i, j, c);
				fill_area(lines, i, j, lines[i][j]);
				// std::cout << sides << std::endl;
				result += area * sides;
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