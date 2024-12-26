#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

void convertStringToIntegers(const std::string& str, std::vector<int> &numbers) {
	std::stringstream ss(str);
	int num;
	while (ss >> num) {
		numbers.push_back(num);
	}
}

void	part1()
{
	int	result = 0;
	std::ifstream file("test");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::string			line;
	std::vector<int>	numbers;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		numbers.clear();
		convertStringToIntegers(line, numbers);
		int	dif1;
		int dif2;
		std::vector<int>::iterator it1 = numbers.begin();
		dif1 = *it1 - (*(++(it1)));
		int skip = 0;
		if (std::abs(dif1) < 1 || std::abs(dif1) > 3)
			skip = 1;
		while (it1 != numbers.end()) {
			--it1;
			dif2 = *it1 - (*(++(it1)));
			if ((dif1 > 0 && dif2 < 0) || (dif1 < 0 && dif2 > 0))
				skip = 1;
			if (std::abs(dif2) < 1 || std::abs(dif2) > 3)
				skip = 1;
			it1++;
		}
		if (!skip)
			++result;
		std::cout << skip << " " << line <<std::endl;
	}
	// Close the file
	file.close();
	std::cout << result << std::endl;
}

void	part2()
{
	int	result = 0;
	std::ifstream file("input");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::string			line;
	std::vector<int>	numbers;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		numbers.clear();
		convertStringToIntegers(line, numbers);
		int	dif1;
		int dif2;
		std::vector<int>::iterator it1 = numbers.begin();
		dif1 = *it1 - (*(++(it1)));
		int skip = 0;
		if (std::abs(dif1) < 1 || std::abs(dif1) > 3)
			skip = 1;
		while (it1 != numbers.end()) {
			--it1;
			dif2 = *it1 - (*(++(it1)));
			if ((dif1 > 0 && dif2 < 0) || (dif1 < 0 && dif2 > 0))
				skip = 1;
			if (std::abs(dif2) < 1 || std::abs(dif2) > 3)
				skip = 1;
			it1++;
		}
		if (skip)
		{
			std::vector<int>	numbers2;
			for (int i = 0; i < numbers.size(); i++)
			{
				numbers2 = numbers;
				numbers2.erase(numbers2.begin() + i);
				std::cout << numbers2.size() << std::endl;
				it1 = numbers2.begin();
				dif1 = *it1 - (*(++(it1)));
				skip = 0;
				if (std::abs(dif1) < 1 || std::abs(dif1) > 3)
					skip = 1;
				while (it1 != numbers2.end()) {
					--it1;
					dif2 = *it1 - (*(++(it1)));
					if ((dif1 > 0 && dif2 < 0) || (dif1 < 0 && dif2 > 0))
						skip = 1;
					if (std::abs(dif2) < 1 || std::abs(dif2) > 3)
						skip = 1;
					it1++;
				}
				if (!skip)
					break ;
			}
			std::cout << "e" << std::endl;
		}
		if (!skip)
			++result;
		std::cout << skip << " " << line <<std::endl;
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