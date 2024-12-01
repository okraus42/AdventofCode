#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <sstream>

void convertStringToIntegers(const std::string& str, int& a, int& b) {
	std::stringstream ss(str);
	ss >> a >> b;
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
	int				b;
	std::multiset<int>	first;
	std::multiset<int>	second;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		convertStringToIntegers(line, a, b);
		first.insert(a);
		second.insert(b);
		std::cout << "first: " << a << "   second: " << b << std::endl;
	}
	std::multiset<int>::iterator it1 = first.begin();
	std::multiset<int>::iterator it2 = second.begin();
	int	dif;
	while (it1 != first.end()) {
		dif = *it1 - *it2;
		if (dif < 0)
			dif = -dif;
		result += dif;
		it1++;
		it2++;
	}
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
	int				b;
	std::multiset<int>	first;
	std::multiset<int>	second;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		convertStringToIntegers(line, a, b);
		first.insert(a);
		second.insert(b);
		std::cout << "first: " << a << "   second: " << b << std::endl;
	}
	std::multiset<int>::iterator it1 = first.begin();
	std::multiset<int>::iterator it2 = second.begin();
	int	count;
	while (it1 != first.end()) {
		it2 = second.begin();
		count = 0;
		while (it2 != second.end()) {
			if (*it1 == *it2)
				++count;
			++it2;
		}
		result += *it1 * count;
		it1++;
	}
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