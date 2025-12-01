#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <sstream>

void convertStringToIntegers(const std::string& str, int& a) {
	std::stringstream ss(str);
	ss >> a;
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

	std::string		line;
	int				a;
	int				dial = 50;

	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		if (line[0] == 'R')
			line[0] = '0';
		else
			line[0] = '-';
		convertStringToIntegers(line, a);
		dial += a;
		while (dial < 0) {
			dial += 100;
		}
		while (dial > 99) {
			dial -= 100;
		}
		if (dial == 0)
			result++;
		std::cout << "first: " << a << std::endl;
	}
	// std::multiset<int>::iterator it1 = first.begin();
	// std::multiset<int>::iterator it2 = second.begin();
	// int	dif;
	// while (it1 != first.end()) {
	// 	dif = *it1 - *it2;
	// 	if (dif < 0)
	// 		dif = -dif;
	// 	result += dif;
	// 	it1++;
	// 	it2++;
	// }
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

	std::string		line;
	int				a;
	int				dial = 50;

	// Read the file line by line
	while (std::getline(file, line)) {
		auto zero = false;
		// std::cout << line << std::endl;  // Print each line to the console
		if (line[0] == 'R')
			line[0] = '0';
		else
			line[0] = '-';
		convertStringToIntegers(line, a);
		std::cout << "a" << dial << std::endl;
		if (a > 0)
		{
			while (a) {
				a--;
				dial++;
				if (dial == 100)
				{
					dial = 0;
					result++;
				}
			}
		}
		else if (a < 0)
		{
			while (a) {
				a++;
				dial--;
				if (dial == 0)
				{
					result++;
				}
				if (dial == -1)
				{
					dial = 99;
				}
			}
		}
		std::cout << "r" << result << std::endl;
		// if (dial == 0)
		// 	result++;
		// std::cout << "first: " << a << std::endl;
	}
	// std::multiset<int>::iterator it1 = first.begin();
	// std::multiset<int>::iterator it2 = second.begin();
	// int	dif;
	// while (it1 != first.end()) {
	// 	dif = *it1 - *it2;
	// 	if (dif < 0)
	// 		dif = -dif;
	// 	result += dif;
	// 	it1++;
	// 	it2++;
	// }
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