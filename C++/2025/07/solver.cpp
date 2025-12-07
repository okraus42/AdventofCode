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
	for (int i = 0; i < m; i++)
	if (lines[0][i] == 'S')
		lines[1][i] = '|';
	for (int y = 2; y < n; y++) {
		for (int x = 0; x < m; x ++) {
			if (lines[y][x] == '^' && lines[y - 1][x] == '|') {
				result++;
				lines[y][x-1] = '|';
				lines[y][x+1] = '|';
			}
			else if (lines[y - 1][x] == '|') {
				lines[y][x] = '|';
			}
		}
	}
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
	std::vector<long long> nums;
	std::vector<std::vector<long long>> numbers;

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
	for (int i = 0; i < m; i++)
		if (lines[0][i] == 'S')
			lines[1][i] = '|';
	for (int y = 0; y < n; y++) {
		nums.clear();
		for (int x = 0; x < m; x++) {
			nums.push_back(0);
		}
		numbers.push_back(nums);
	}
	for (int i = 0; i < m; i++)
		if (lines[0][i] == 'S')
			numbers[1][i] = 1;
	for (int y = 2; y < n; y++) {
		for (int x = 0; x < m; x ++) {
			if (lines[y][x] == '^' && lines[y - 1][x] == '|') {
				lines[y][x-1] = '|';
				lines[y][x+1] = '|';
				numbers[y][x- 1] += numbers[y - 1][x];
				numbers[y][x + 1] += numbers[y - 1][x];
			}
			else if (lines[y - 1][x] == '|') {
				lines[y][x] = '|';
				numbers[y][x] += numbers[y - 1][x];
			}
		}
	}
	for (int x = 0; x < m; x++) {
		result += numbers[n - 1][x];
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