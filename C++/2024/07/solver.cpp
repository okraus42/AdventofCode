#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

void convertStringToIntegers(const std::string& str, std::vector<long long> &numbers) {
	
	size_t colon_pos = str.find(':');

	std::string first_number_str = str.substr(0, colon_pos);

	// Convert the first number to an integer
	long long first_number = std::stol(first_number_str);

	std::string numbers_str = str.substr(colon_pos + 1);

	// Remove leading spaces
	numbers_str.erase(0, numbers_str.find_first_not_of(" "));

	// First, add the number before the colon to the vector
	numbers.push_back(first_number);
		
	long long num;
	std::stringstream ss(numbers_str);
	// Extract each number and add to the vector
	while (ss >> num) {
		numbers.push_back(num);
	}
}
long long special(long long temp, long long num)
{
	long long res;
	if (num > 999)
		res = temp * 10000 + num;
	else if (num > 99)
		res = temp * 1000 + num;
	else if (num > 9)
		res = temp * 100 + num;
	else
		res = temp * 10 + num;
	return (res);
}


//this is stupid and takes too long, perms should be smaller. at least subtract 4 from it or something, I do not care
//but it works, eventually
void	check_solv2(std::vector<long long> &numbers, std::vector<int> &signs, int * solv)
{
	int	perms = numbers.size();
	perms = 1 << perms * 2;
	long long temp = 0;
	for (int i = 0; i < perms; i++)
	{
		temp = numbers[1];
		for (size_t j = 2; j < numbers.size(); j++)
		{
			if (i & (1 << (j - 2) * 2))
				temp += numbers[j];
			else if (i & (1 << ((j - 2) * 2) + 1))
				temp *= numbers[j];
			else
				temp = special(temp, numbers[j]);
			if (temp > numbers[0] || temp < 0)
				break ;
		}
		if (temp == numbers[0])
			*solv = 1;
	}
}

void	check_solv(std::vector<long long> &numbers, std::vector<int> &signs, int * solv)
{
	int	perms = numbers.size();
	perms = 1 << perms ;
	long long temp = 0;
	for (int i = 0; i < perms; i++)
	{
		temp = numbers[1];
		for (size_t j = 2; j < numbers.size(); j++)
		{
			if (i & (1 << (j - 2)))
				temp += numbers[j];
			else
				temp *= numbers[j];
			if (temp > numbers[0] || temp < 0)
				break ;
		}
		if (temp == numbers[0])
			*solv = 1;
	}
}


void	part1()
{
	long long	result = 0;
	long long	max = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::string			line;
	std::vector<long long>	numbers;
	std::vector<int>	signs;
	int					solv;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		numbers.clear();
		convertStringToIntegers(line, numbers);
		if (numbers[0] > max)
			max = numbers[0];
		// for (size_t i = 0; i < numbers.size(); i++)
		// 	std::cout << numbers[i] <<std::endl;
		solv = 0;
		signs.clear();
		check_solv(numbers, signs, &solv);
		if (solv)
			result += numbers[0];
		std::cout << result << std::endl;
	}
	// Close the file
	file.close();
	std::cout << result << std::endl;
}

void	part2()
{
	long long	result = 0;
	long long	max = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::string			line;
	std::vector<long long>	numbers;
	std::vector<int>	signs;
	int					solv;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		numbers.clear();
		convertStringToIntegers(line, numbers);
		if (numbers[0] > max)
			max = numbers[0];
		// for (size_t i = 0; i < numbers.size(); i++)
		// 	std::cout << numbers[i] <<std::endl;
		solv = 0;
		signs.clear();
		check_solv2(numbers, signs, &solv);
		if (solv)
			result += numbers[0];
		std::cout << result << std::endl;
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