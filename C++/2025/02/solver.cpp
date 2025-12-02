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

long long	find_invalids(long long a, long long b) {
	long long invalids = 0;
	int invalid;
	std::string str;
	// convertIntegerToString(a, str);
	// std::cout << str << std::endl;
	for (long long l = a; l <= b; ++l) {
		str.clear();
		convertIntegerToString(l, str);
		int n = str.size();
		if (n % 2 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 2; i++) {
				// std::cout << str[i] << " " << str[n / 2 + i] << std::endl;
				if (str[i] != str[n / 2 + i])
					invalid = 0;
			}
			if (invalid)
				invalids += l;

		}
	}
	return invalids;
}

long long	find_invalids2(long long a, long long b) {
	long long invalids = 0;
	int invalid;
	std::string str;
	// convertIntegerToString(a, str);
	// std::cout << str << std::endl;
	for (long long l = a; l <= b; ++l) {
		str.clear();
		convertIntegerToString(l, str);
		int n = str.size();
		if (n % 2 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 2; i++) {
				// std::cout << str[i] << " " << str[n / 2 + i] << std::endl;
				if (str[i] != str[n / 2 + i])
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 3 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 3; i++) {
				if (!(str[i] == str[n / 3 + i]
					&& str[i] == str[2 * n / 3 + i]
					))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 4 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 4; i++) {
				if (!((str[i] == str[n / 4 + i]
					&& str[i] == str[2 * n / 4 + i]
					&& str[i] == str[3 * n / 4 + i]))
				)
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 5 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 5; i++) {
				if (!(str[i] == str[n / 5 + i]
					&& str[i] == str[2 * n / 5 + i]
					&& str[i] == str[3 * n / 5 + i]
					&& str[i] == str[4 * n / 5 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 6 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 6; i++) {
				if (!(str[i] == str[n / 6 + i]
					&& str[i] == str[2 * n / 6 + i]
					&& str[i] == str[3 * n / 6 + i]
					&& str[i] == str[4 * n / 6 + i]
					&& str[i] == str[5 * n / 6 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 7 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 7; i++) {
				if (!(str[i] == str[n / 7 + i]
					&& str[i] == str[2 * n / 7 + i]
					&& str[i] == str[3 * n / 7 + i]
					&& str[i] == str[4 * n / 7 + i]
					&& str[i] == str[5 * n / 7 + i]
					&& str[i] == str[6 * n / 7 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 8 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 8; i++) {
				if (!(str[i] == str[n / 8 + i]
					&& str[i] == str[2 * n / 8 + i]
					&& str[i] == str[3 * n / 8 + i]
					&& str[i] == str[4 * n / 8 + i]
					&& str[i] == str[5 * n / 8 + i]
					&& str[i] == str[6 * n / 8 + i]
					&& str[i] == str[7 * n / 8 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 9 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 9; i++) {
				if (!(str[i] == str[n / 9 + i]
					&& str[i] == str[2 * n / 9 + i]
					&& str[i] == str[3 * n / 9 + i]
					&& str[i] == str[4 * n / 9 + i]
					&& str[i] == str[5 * n / 9 + i]
					&& str[i] == str[6 * n / 9 + i]
					&& str[i] == str[7 * n / 9 + i]
					&& str[i] == str[8 * n / 9 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 10 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 10; i++) {
				if (!(str[i] == str[n / 10 + i]
					&& str[i] == str[2 * n / 10 + i]
					&& str[i] == str[3 * n / 10 + i]
					&& str[i] == str[4 * n / 10 + i]
					&& str[i] == str[5 * n / 10 + i]
					&& str[i] == str[6 * n / 10 + i]
					&& str[i] == str[7 * n / 10 + i]
					&& str[i] == str[8 * n / 10 + i]
					&& str[i] == str[9 * n / 10 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 11 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 11; i++) {
				if (!(str[i] == str[n / 11 + i]
					&& str[i] == str[2 * n / 11 + i]
					&& str[i] == str[3 * n / 11 + i]
					&& str[i] == str[4 * n / 11 + i]
					&& str[i] == str[5 * n / 11 + i]
					&& str[i] == str[6 * n / 11 + i]
					&& str[i] == str[7 * n / 11 + i]
					&& str[i] == str[8 * n / 11 + i]
					&& str[i] == str[9 * n / 11 + i]
					&& str[i] == str[10 * n / 11 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 13 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 13; i++) {
				if (!(str[i] == str[n / 13 + i]
					&& str[i] == str[2 * n / 13 + i]
					&& str[i] == str[3 * n / 13 + i]
					&& str[i] == str[4 * n / 13 + i]
					&& str[i] == str[5 * n / 13 + i]
					&& str[i] == str[6 * n / 13 + i]
					&& str[i] == str[7 * n / 13 + i]
					&& str[i] == str[8 * n / 13 + i]
					&& str[i] == str[9 * n / 13 + i]
					&& str[i] == str[10 * n / 13 + i]
					&& str[i] == str[11 * n / 13 + i]
					&& str[i] == str[12 * n / 13 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
		if (n % 15 == 0)
		{
			invalid = 1;
			for (int i = 0; i < n / 15; i++) {
				if (!(str[i] == str[n / 15 + i]
					&& str[i] == str[2 * n / 15 + i]
					&& str[i] == str[3 * n / 15 + i]
					&& str[i] == str[4 * n / 15 + i]
					&& str[i] == str[5 * n / 15 + i]
					&& str[i] == str[6 * n / 15 + i]
					&& str[i] == str[7 * n / 15 + i]
					&& str[i] == str[8 * n / 15 + i]
					&& str[i] == str[9 * n / 15 + i]
					&& str[i] == str[10 * n / 15 + i]
					&& str[i] == str[11 * n / 15 + i]
					&& str[i] == str[12 * n / 15 + i]
					&& str[i] == str[13 * n / 15 + i]
					&& str[i] == str[14 * n / 15 + i]
				))
					invalid = 0;
			}
			if (invalid) {
				invalids += l;
				std::cout << l << std::endl;
				continue; 
			}
		}
	}
	return invalids;
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

	std::string		line;
	long long		a;
	long long		b;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;

	// Read the file line by line
	std::getline(file, line);
	convertStringToIntegers(line, numbers);
	int n = numbers.size();
	for (int i = 0; i < n; i += 2)
	{
		a = numbers[i];
		b = numbers[i + 1];
		invalids += find_invalids(a, b);
		std::cout << a << " " << b << "   " << invalids << std::endl;

	}
	result = invalids;
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

	std::string		line;
	long long		a;
	long long		b;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;

	// Read the file line by line
	std::getline(file, line);
	convertStringToIntegers(line, numbers);
	int n = numbers.size();
	for (int i = 0; i < n; i += 2)
	{
		a = numbers[i];
		b = numbers[i + 1];
		invalids += find_invalids2(a, b);
		std::cout << a << " " << b << "   " << invalids << std::endl;

	}
	result = invalids;
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