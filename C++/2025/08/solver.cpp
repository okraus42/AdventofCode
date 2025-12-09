#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

void convertStringToIntegers(const std::string& str, std::vector<long long>& nums) {
	std::string cleaned = str;
	for (char& c : cleaned)
		if (!isdigit(c)) c = ' ';

	std::stringstream ss(cleaned);
	long long num;
	while (ss >> num) {
		nums.push_back(num);
	}
}

void convertIntegerToString(const long long num, std::string& str) {
	std::stringstream ss;
	ss << num;
	ss >> str;
}

double get_distance(long long a, long long b, std::vector<std::vector<long long>>&	numbers) {
	double d = 0;
	double x = (double)numbers[a][0] - (double)numbers[b][0];
	double y = (double)numbers[a][1] - (double)numbers[b][1];;
	double z = (double)numbers[a][2] - (double)numbers[b][2];;
	d = std::sqrt(x * x + y * y + z *z);
	return d;
}

#define CONNECTIONS 1000

void	part1()
{
	long long	result = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}


	long long		a = 0;
	long long		b = 0;
	long long		c;
	long long		cirq = 0;
	double 			d;
	double 			min_d = 0;
	double 			dd = 0;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long>	nums;
	std::vector<std::vector<long long>>	numbers;

	// Read the file line by line
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
	// int m = lines[0].size();
	c = 0;
	while (c < CONNECTIONS)
	{
		dd = 999999999999LL;
		for (int y = 0; y < n; y++) {
			for (int x = y + 1; x < n; x++) {
				d = get_distance(y, x, numbers);
				if (d < dd && d > min_d) {
					dd = d;
					a = y;
					b = x;
				}
			}
		}
		min_d = dd;
		if (!numbers[a][3] && !numbers[b][3]) {
			++cirq;
			numbers[a][3] = cirq;
			numbers[b][3] = cirq;
		}
		else if (numbers[a][3] && numbers[b][3]) {
			int tmp1 = numbers[a][3];
			int tmp2 = numbers[b][3];
			for (int i = 0; i < n; i++) {
				if (numbers[i][3] == tmp2)
					numbers[i][3] = tmp1;
			}
		}
		else {
			int tmp = numbers[a][3];
			if (!tmp)
				tmp = numbers[b][3];
			numbers[a][3] = tmp;
			numbers[b][3] = tmp;
		}
		// std::cout << "a " << numbers[a][0] << " " << numbers[a][1] << " " << numbers[a][2] << " " << numbers[a][3] << std::endl;
		// std::cout << "b " << numbers[b][0] << " " << numbers[b][1] << " " << numbers[b][2] << " " << numbers[b][3] << std::endl;
		++c;
	}
	for (int i = 0; i < n; i++) {
		// std::cout << numbers[i][0] << " " << numbers[i][1] << " " << numbers[i][2] << " " << numbers[i][3] << std::endl;
	}
	std::vector<long long>	cirquits;
	for (int i = 1; i < CONNECTIONS; i++) {
		a = 0;
		for (int j = 0; j < n; j++) {
			if (numbers[j][3] == i)
				a++;
		}
		cirquits.push_back(a);
	}
	std::sort(cirquits.begin(), cirquits.end(), std::greater<long long>());
	result = cirquits[0] * cirquits[1] * cirquits[2];
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


	long long		a = 0;
	long long		b = 0;
	long long		p = 0;
	long long		q = 0;
	long long		c;
	long long		cirq = 0;
	double 			d;
	double 			min_d = 0;
	double 			dd = 0;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long>	nums;
	std::vector<std::vector<long long>>	numbers;

	// Read the file line by line
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
	// int m = lines[0].size();
	c = 0;
	while (1)
	{
		dd = 999999999999LL;
		for (int y = 0; y < n; y++) {
			for (int x = y + 1; x < n; x++) {
				d = get_distance(y, x, numbers);
				if (d < dd && d > min_d) {
					dd = d;
					a = y;
					b = x;
				}
			}
		}
		min_d = dd;
		if (!numbers[a][3] && !numbers[b][3]) {
			++cirq;
			numbers[a][3] = cirq;
			numbers[b][3] = cirq;
		}
		else if (numbers[a][3] && numbers[b][3]) {
			int tmp1 = numbers[a][3];
			int tmp2 = numbers[b][3];
			for (int i = 0; i < n; i++) {
				if (numbers[i][3] == tmp2)
					numbers[i][3] = tmp1;
			}
		}
		else {
			int tmp = numbers[a][3];
			if (!tmp)
				tmp = numbers[b][3];
			numbers[a][3] = tmp;
			numbers[b][3] = tmp;
		}
		// std::cout << "a " << numbers[a][0] << " " << numbers[a][1] << " " << numbers[a][2] << " " << numbers[a][3] << std::endl;
		// std::cout << "b " << numbers[b][0] << " " << numbers[b][1] << " " << numbers[b][2] << " " << numbers[b][3] << std::endl;
		++c;
		p = numbers[0][3];
		q = numbers[1][3];
		for (int i = 0; i < n; i++) {
			if (numbers[i][3] != p) {
				p = 0;
				q = 1;
				break ;
			}

		}
		if (p == q)
			break ;
	}
	result = numbers[a][0] * numbers[b][0];
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