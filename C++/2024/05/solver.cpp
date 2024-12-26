#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

void convertStringToIntegers(const std::string& str, std::vector<int> &numbers, char delimiter) {
	std::stringstream ss(str);
	std::string token;

	int num;
	while (std::getline(ss, token, delimiter)) {
		// Convert the token to an integer and add it to the vector
		num = std::stoi(token);
		numbers.push_back(num);
	}
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

	std::vector<std::vector<int>>	rules;
	std::vector<std::vector<int>>	lists;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line) && line.size() > 2) {
		std::cout << line << std::endl;  // Print each line to the console
		std::vector<int>	numbers;
		convertStringToIntegers(line, numbers, '|');
		rules.push_back(numbers);
	}

	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		std::vector<int>	numbers;
		convertStringToIntegers(line, numbers, ',');
		lists.push_back(numbers);
	}
	// Close the file
	file.close();
	int correct;
	for (size_t i = 0; i < lists.size(); i++)
	{
		correct = 1;
		for (size_t j = 1; j < lists[i].size(); j++)
		{
			//check all previous numbers if they appear before
			for (size_t k = 0; k < rules.size(); k++)
			{
				if (lists[i][j] == rules[k][0])
				{
					for (size_t l = 0; l < j; l++)
					{
						if (lists[i][l] == rules[k][1])
						{
							// std::cout << i
							// << " " << j
							// << " " << k
							// << " " << l
							// << " " << lists[i][j]
							// << " " << rules[k][1]
							// << " " << lists[i][l]
							// << " " << rules[k][0]
							// << std::endl;
							correct = 0;
						}
					}
				}
			}
		}
		std::cout << correct << std::endl;
		if (correct)
			result += lists[i][lists[i].size() / 2];
	}

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

	std::vector<std::vector<int>>	rules;
	std::vector<std::vector<int>>	lists;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line) && line.size() > 2) {
		std::cout << line << std::endl;  // Print each line to the console
		std::vector<int>	numbers;
		convertStringToIntegers(line, numbers, '|');
		rules.push_back(numbers);
	}

	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		std::vector<int>	numbers;
		convertStringToIntegers(line, numbers, ',');
		lists.push_back(numbers);
	}
	// Close the file
	file.close();
	int correct;
	for (size_t i = 0; i < lists.size(); i++)
	{
		correct = 1;
		for (size_t j = 1; j < lists[i].size(); j++)
		{
			//check all previous numbers if they appear before
			for (size_t k = 0; k < rules.size(); k++)
			{
				if (lists[i][j] == rules[k][0])
				{
					for (size_t l = 0; l < j; l++)
					{
						if (lists[i][l] == rules[k][1])
						{
							// std::cout << i
							// << " " << j
							// << " " << k
							// << " " << l
							// << " " << lists[i][j]
							// << " " << rules[k][1]
							// << " " << lists[i][l]
							// << " " << rules[k][0]
							// << std::endl;
							correct = 0;
						}
					}
				}
			}
		}
		std::cout << correct << std::endl;
		if (!correct)
		{
			while (!correct)
			{
				correct = 1;
				for (size_t j = 1; j < lists[i].size(); j++)
				{
					//check all previous numbers if they appear before
					for (size_t k = 0; k < rules.size(); k++)
					{
						if (lists[i][j] == rules[k][0])
						{
							for (size_t l = 0; l < j; l++)
							{
								if (lists[i][l] == rules[k][1])
								{
									int tmp = lists[i][l];
									lists[i][l] = lists[i][j];
									lists[i][j] = tmp;
									correct = 0;
								}
							}
						}
					}
				}
			}
			result += lists[i][lists[i].size() / 2];
		}
	}

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