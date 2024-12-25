#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


#define FILE "input.txt"
#define MAXBIT 45
// #define TESTBIT 2

#define VALUE1 0
#define VALUE2 2
#define OPERATOR 1
#define RESULT 4

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
	std::set<std::vector<int>>	keys;
	std::set<std::vector<int>>	locks;
	std::string			line;

	
	// Read the file line by line"

	while (std::getline(file, line)) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	
	size_t	i;
	size_t	j;
	size_t	k;
	for (i = 0; i < lines.size();)
	{
		std::cout << lines[i] << std::endl;
		std::vector<int>	lock;
		std::vector<int>	key;
		if (lines[i][0] == '#')
		{
			for (j = 0; j < lines[i].size(); j++)
			{
				int dots = -1;
				for (k = 0; lines[i + k].size() == lines[i].size(); k++)
				{
					if (lines[i + k][j] == '.')
						dots++;
				}
				lock.push_back(5 - dots);
			}
			locks.insert(lock);
		}
		else
		{
			for (j = 0; j < lines[i].size(); j++)
			{
				int dots = -1;
				for (k = 0; lines[i + k].size() == lines[i].size(); k++)
				{
					if (lines[i + k][j] == '.')
						dots++;
				}
				key.push_back(5 - dots);
			}
			keys.insert(key);
		}
		i += 8;
	}
	for (auto it = keys.begin(); it != keys.end(); it++)
	{
		std::cout << "key: ";
		for (i = 0; i < (*it).size(); i++)
		{
			std::cout << (*it)[i] << " ";
		}
		std::cout << std::endl;
	}
	for (auto it = locks.begin(); it != locks.end(); it++)
	{
		std::cout << "lock: ";
		for (i = 0; i < (*it).size(); i++)
		{
			std::cout << (*it)[i] << " ";
		}
		std::cout << std::endl;
	}
	for (auto kkk = keys.begin(); kkk != keys.end(); kkk++)
	{
		for (auto lll = locks.begin(); lll != locks.end(); lll++)
		{
			int	mismatch = 0;
			for (i = 0; i < (*kkk).size(); i++)
			{
				if ((*kkk)[i] + (*lll)[i] > 5)
					mismatch = 1;
			}
			if (!mismatch)
				result++;
		}
	}
	file.close();
	std::cout << result << std::endl;
}

// test 4 numbers 0-0 0-1 1-0 1-1
// see the lowest bit when it deviates

// maybe check for carry later

void	part2()
{
	std::string	result;
	
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
