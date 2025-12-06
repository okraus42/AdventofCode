#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

void convertStringToIntegers(const std::string& str, long long& a, long long& b) {
	std::string cleaned = str;
	for (char& c : cleaned)
		if (!isdigit(c)) c = ' ';

	std::stringstream ss(cleaned);
	ss >> a;
	ss >> b;
}


void convertStringToInteger(const std::string& str, long long& a) {
	std::stringstream ss(str);
	ss >> a;
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
	std::vector<long long> min;
	std::vector<long long> max;

	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	// while (std::getline(file, line)) {
	// 	// std::cout << line << std::endl;  // Print each line to the console
	// 	lines.push_back(line);
	// }
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		if (line == "")
			break;
		convertStringToIntegers(line, a, b);
		min.push_back(a);
		max.push_back(b);
	}
	while (std::getline(file, line)) {
		std::cout << "aaa " << line << std::endl;
		if (line == "")
			break;
		convertStringToInteger(line, a);
		numbers.push_back(a);
	}
	file.close();
	int n = numbers.size();
	int m = min.size();
	for (long long l : numbers) {
		for (int i = 0; i < m; i++) {
			if (l >= min[i] && l <= max[i]) {
				result++;
				break;
			}
		}
	}
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
	std::vector<long long[2]> numbers;
	std::vector<long long> min;
	std::vector<long long> max;

	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;

	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		if (line == "")
			break;
		convertStringToIntegers(line, a, b);
		min.push_back(a);
		max.push_back(b);
	}
	int n = min.size();
	int m;
	int found = 1;
	while (found) {
		found = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				if (min[j] < min[i] && max[j] > max[i]) {
					min[i] = min[j];
					max[i] = max[j];
					min[j] = 0;
					max[j] = -1;
					found = 1;
				}
				else if (min[j] && min[j] < min[i] && max[j] >= min[i] && max[j] <= max[i]) {
					min[i] = min[j];
					min[j] = 0;
					max[j] = -1;
					found = 1;
				}
				else if (max[j] > max[i] && min[j] >= min[i] && min[j] <= max[i]) {
					max[i] = max[j];
					min[j] = 0;
					max[j] = -1;
					found = 1;
				}
				else if (min[j] && min[j] >= min[i] && max[j] <= max[i]) {
					min[j] = 0;
					max[j] = -1;
					found = 1;
				}
			}
		}
	}
	for (int i = 0; i < n; i++) {
		std::cout << ": " << min[i] << "-" << max[i] << std::endl;
		result += max[i] - min[i] + 1;
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