#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

void convertStringToIntegers(const std::string& str, std::vector<long long>& numbers) {
	std::string cleaned = str;
	for (char& c : cleaned)
		if (!isdigit(c)) c = ' ';

	std::stringstream ss(cleaned);
	long long num;
	while (ss >> num) {
		numbers.push_back(num);
	}
}

void convertIntegerToString(const long long num, std::string& str) {
	std::stringstream ss;
	ss << num;
	ss >> str;
}


void	part1()
{
	long long	result = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}


	long long		a;
	long long		b;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;

	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	int n = lines.size();
	int m = lines[0].size();
	int o = n - 1;
	int p = m - 1;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			a = 0;
			if (y && x && lines[y - 1][x - 1] == '@')
				++a;
			if (y && lines[y - 1][x] == '@')
				++a;
			if (y && x != p && lines[y - 1][x + 1] == '@')
				++a;
			if (x && lines[y][x - 1] == '@')
				++a;
			if (x != p && lines[y][x + 1] == '@')
				++a;
			if (y != o && x && lines[y + 1][x - 1] == '@')
				++a;
			if (y != o && lines[y + 1][x] == '@')
				++a;
			if (y != o && x != p && lines[y + 1][x + 1] == '@')
				++a;
			if (a < 4 && lines[y][x] == '@')
			{
				// lines[y][x] = 'x';
				result++;
			}
		}
	}
	for (int y = 0; y < n; y++)
	std::cout << lines[y] << std::endl;
	std::cout << o << " xxxxx " << p << std::endl;
	file.close();
	std::cout << result << std::endl;
}

void	part2()
{
	long long	result = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}


	long long		a;
	long long		b;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;

	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	int n = lines.size();
	int m = lines[0].size();
	int o = n - 1;
	int p = m - 1;
	int r = 1;
	while (r)
	{
		r = 0;
		for (int y = 0; y < n; y++)
		{
			for (int x = 0; x < m; x++)
			{
				a = 0;
				if (y && x && lines[y - 1][x - 1] == '@')
					++a;
				if (y && lines[y - 1][x] == '@')
					++a;
				if (y && x != p && lines[y - 1][x + 1] == '@')
					++a;
				if (x && lines[y][x - 1] == '@')
					++a;
				if (x != p && lines[y][x + 1] == '@')
					++a;
				if (y != o && x && lines[y + 1][x - 1] == '@')
					++a;
				if (y != o && lines[y + 1][x] == '@')
					++a;
				if (y != o && x != p && lines[y + 1][x + 1] == '@')
					++a;
				if (a < 4 && lines[y][x] == '@')
				{
					lines[y][x] = '.';
					r = 1;
					result++;
				}
			}
		}
	}
	
	for (int y = 0; y < n; y++)
	std::cout << lines[y] << std::endl;
	std::cout << o << " xxxxx " << p << std::endl;
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