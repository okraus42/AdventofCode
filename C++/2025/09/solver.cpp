#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

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
	long long		area;
	long long		max = 0;
	std::vector<long long>	nums;
	std::vector<std::vector<long long>>	numbers;
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		nums.clear();
		convertStringToIntegers(line, nums);
		nums.push_back(0);
		nums.push_back(0);
		numbers.push_back(nums);
		lines.push_back(line);
	}
	int n = lines.size();
	int m = lines[0].size();
	// for (int i = 0; i < m; i++)
	// if (lines[0][i] == 'S')
	// 	lines[1][i] = '|';
	for (int y = 0; y < n; y++) {
		for (int x = y + 1; x < n; x++) {
			a = numbers[x][0] - numbers[y][0];
			b = numbers[x][1] - numbers[y][1];
			if (a < 0)
				a *= -1;
			if (b < 0)
				b *= -1;
			area = ++a * ++b;
			
			if (area > max)
			{
				// std::cout << area << " " << numbers[x][0] << "," << numbers[x][1];
				// std::cout << " " << numbers[y][0] << "," << numbers[y][1] << std::endl;
				max = area;
			}
		}
	}
	result = max;
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

	int				skip;
	long long		a;
	long long		b;
	long long		c;
	long long		d;
	long long		xx[2];
	long long		yy[2];
	long long		area;
	long long		max = 0;
	std::vector<long long>	nums;
	std::vector<std::vector<long long>>	numbers;
	std::vector<std::string> lines;
	std::string			line;
	std::string			first;
	// Read the file line by line
	std::getline(file, line);
	first = line;
	nums.clear();
	convertStringToIntegers(line, nums);
	nums.push_back(0);
	nums.push_back(0);
	numbers.push_back(nums);
	lines.push_back(line);
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		nums.clear();
		convertStringToIntegers(line, nums);
		numbers.push_back(nums);
		lines.push_back(line);
	}
	nums.clear();
	convertStringToIntegers(first, nums);
	numbers.push_back(nums);
	lines.push_back(line);
	int n = lines.size();
	int m = lines[0].size();
	// for (int i = 0; i < m; i++)
	// if (lines[0][i] == 'S')
	// 	lines[1][i] = '|';
	for (int y = 1; y < n; y++) {
		for (int x = y + 1; x < n; x++) {
			
			xx[0] = numbers[x][0];
			xx[1] = numbers[y][0];
			yy[0] = numbers[x][1];
			yy[1] = numbers[y][1];
			if (xx[0] == xx[1] || yy[0] == yy[1])
				continue ;
			if (xx[0] > xx[1]) {
				std::swap(xx[0], xx[1]);
			}
			if (yy[0] > yy[1]) {
				std::swap(yy[0], yy[1]);
			}
			area = (xx[1] - xx[0] + 1) * (yy[1] - yy[0] + 1);
			if (area > max)
			{
				skip = 0;
				// std::cout << "xx" << " " << xx[0] << "," << xx[1] << std::endl;
				// std::cout << "yy" << " " << yy[0] << "," << yy[1] << std::endl;
				for (int i = 1; i < n; i++) {
					//xx0 - > xx1
					// a x
					//b y
					if (numbers[i][0] == numbers[i - 1][0]) {
						a = numbers[i][0];
						b = numbers[i - 1][1];
						c = numbers[i][1];
						if (b > c)
							std::swap(b, c);
						if (b <= yy[0] && c > yy[0])
							skip = 1;
						if (b < yy[1] && c >= yy[1])
							skip = 1;
						if (a <= xx[0] || a >= xx[1])
							skip = 0;
						// std::cout << "xxx: " << a << "   " << b << "," << c << std::endl;
					}
					else {
						a = numbers[i][1];
						b = numbers[i - 1][0];
						c = numbers[i][0];
						if (b > c)
							std::swap(b, c);
						if (b <= xx[0] && c > xx[0])
							skip = 1;
						if (b < xx[1] && c >= xx[1])
							skip = 1;
						if (a <= yy[0] || a >= yy[1])
							skip = 0;
						// std::cout << "yyy: " << a << "   " << b << "," << c << std::endl;
					}
					if (skip)
						break ;
				}
				// std::cout << area << " " << numbers[x][0] << "," << numbers[x][1];
				// std::cout << " " << numbers[y][0] << "," << numbers[y][1] << std::endl;
				if (!skip)
				{
					std::cout << area << " " << numbers[x][0] << "," << numbers[x][1];
					std::cout << " " << numbers[y][0] << "," << numbers[y][1] << std::endl;
					max = area;
				}
			}
		}
	}
	result = max;
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