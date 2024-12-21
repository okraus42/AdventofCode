#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>


#define FILE "input.txt"
#define SAVE 100
#define PICO 20



#define EAST 1
#define WEST 2
#define NORTH 4
#define SOUTH 8






void	ok_score(std::vector<std::string> &map, size_t y, size_t x, std::vector<std::vector<long long>> &score, long long s)
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
	{
		// std::cout << "exit" <<std::endl;
		return ;
	}
	ok_score(map, y, x + 1, score, s + 1);
	ok_score(map, y - 1, x, score, s + 1);
	ok_score(map, y + 1, x, score, s + 1);
	ok_score(map, y, x - 1, score, s + 1);
}

long long	absl(long long a, long long b)
{
	if (a == 999999999999999LL || b == 999999999999999LL)
		return (0);
	if (a < b)
		return (b - a);
	return (a - b);

}

long long	count_cheats(std::vector<std::vector<long long>> &score)
{
	long long	cheats = 0;
	ssize_t		i;
	ssize_t		j;
	ssize_t		y;
	ssize_t		x;
	
	for (i = 0; (size_t)i < score.size() - 1; i++)
	{
		for (j = 0; (size_t)j < score[i].size() - 1; j++)
		{
			for (y = i - PICO; y <= i + PICO; y++)
			{
				for (x = j - PICO; x <= j + PICO; x++)
				{
					if (absl(i, y) + absl(j, x) <= PICO && y > 0 && x > 0 && (size_t)y < score.size() - 1 && (size_t)x < score[y].size() - 1)
					{
						if (absl(score[i][j], score[y][x]) >= SAVE + absl(i, y) + absl(j, x))
						{
							// std::cout << "i " << i
							// << "\tj " << j
							// << "\ty " << y
							// << "\tx " << x
							// << "\tscore[i][j] " << score[i][j]
							// << "\tscore[y][x] " << score[y][x]
							// << std::endl;
							cheats++;
						}
					}
				}
			}
		}
	}
	return (cheats / 2);
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
	long long	orig = 0;
	long long	now = 0;
	long long	cheats = 0;
	std::vector<std::string> map2;
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
	size_t	y;
	size_t	x;
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
				ok_score(map, i, j, score, 0LL);
			}
		}
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'E')
			{
				orig = score[i][j];
				std::cout << orig << std::endl;
			}
		}
	}
	for (y = 1; y < map.size() - 1; y++)
	{
		for (x = 1; x < map[y].size() - 1; x++)
		{
			if (map[y][x] == '#')
			{
				map2.clear();
				for (i = 0; i < map.size(); i++)
				{
					map2.push_back(map[i]);
				}
				map2[y][x] = '.';
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
				for (i = 0; i < map.size(); i++)
				{
					for (j = 0; j < map[i].size(); j++)
					{
						if (map[i][j] == 'S')
						{
							ok_score(map2, i, j, score, 0LL);
						}
					}
				}
				for (i = 0; i < map.size(); i++)
				{
					for (j = 0; j < map[i].size(); j++)
					{
						if (map[i][j] == 'E')
						{
							now = score[i][j];
							if (orig - now >= SAVE)
							{
								// std::cout << "y: " << y << "\tx: " << x <<std::endl;
								cheats++;
								// std::cout << orig - now << std::endl;
							}
						}
					}
				}
			}
		}
	}
	result = cheats;
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
	long long	orig = 0;
	std::vector<std::string> map2;
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
				ok_score(map, i, j, score, 0LL);
			}
		}
	}
	for (i = 0; i < map.size(); i++)
	{
		for (j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'E')
			{
				orig = score[i][j];
				std::cout << std::endl;
				std::cout << orig << std::endl;
			}
		}
	}
	result = count_cheats(score);
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