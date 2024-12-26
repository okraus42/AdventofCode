#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


#define FILE "input.txt"
#define MAXBIT 45
// #define TESTBIT 2

#define VALUE1 0
#define VALUE2 2
#define OPERATOR 1
#define RESULT 4


void ok_deep(std::vector<std::vector<std::string>> &operations, std::string sus, int level)
{
	if (!level)
		return;
	for (auto& inner : operations)
	{
		if (inner.size() > RESULT)
		{
			if (inner[RESULT] == sus)
			{
				if (level == 5)
					std::cout << "DEEPDIVE" << std::endl;
				std::cout << level << ": " << inner[VALUE1] << " " << inner[OPERATOR] << " " << inner[VALUE2] << " " << inner[RESULT] << std::endl;
				ok_deep(operations, inner[VALUE1], level - 1);
				ok_deep(operations, inner[VALUE2], level - 1);
			}
		}
	}
}

//6, 15, 22,23, 38,39, 
void ok_swap(std::vector<std::vector<std::string>> &operations, const std::string &swap1, const std::string &swap2)
{
	// Iterate over all the inner vectors in the operations vector
	for (auto& inner_vec : operations)
	{
		if (inner_vec.size() > RESULT)
		{
			if (inner_vec[RESULT] == swap1)
				inner_vec[RESULT] = swap2;
			else if (inner_vec[RESULT] == swap2)
				inner_vec[RESULT] = swap1;
		}
	}
}

std::string formatToTwoDigits(int num)
{
	std::ostringstream oss;
	oss << std::setw(2) << std::setfill('0') << num;  // Ensure width of 2, and fill with '0' if necessary
	return oss.str();
}

void ok_test00(std::map<std::string, int> memory, std::vector<std::vector<std::string>> operations, size_t bit)
{
	size_t	i = 0;
	size_t	j;
	std::string	meme;

	(void) bit;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "x" + formatToTwoDigits(i);
		memory[meme] = 0;
		std::cout << "0";
	}
	std::cout << std::endl;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "y" + formatToTwoDigits(i);
		memory[meme] = 0;
		std::cout << "0";
	}
	std::cout << std::endl;
	while (operations.size())
	{
		for (i = 0; i < operations.size(); i++)
		{
			if (memory.find(operations[i][VALUE1]) != memory.end() && memory.find(operations[i][VALUE2]) != memory.end())
			{
				if (operations[i][OPERATOR] == "AND")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] & memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "OR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] | memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "XOR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] ^ memory[operations[i][VALUE2]];
				}
				operations.erase(operations.begin() + i);
			}
		}
	}
	j = 1;
	for (auto it = memory.begin(); it != memory.end(); ++it)
	{
		if (it->first[0] == 'z')
		{
			// std::cout << it->first << " " << j << " " << it->second << std::endl;
			if (it->second)
				std::cout << "1";
			else
				std::cout << "0";
			j <<= 1;
		}
	}
	std::cout << std::endl;
}

void ok_test01(std::map<std::string, int> memory, std::vector<std::vector<std::string>> operations, size_t bit)
{
	size_t	i = 0;
	size_t	j;
	std::string	meme;

	(void) bit;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "x" + formatToTwoDigits(i);
		memory[meme] = 0;
		std::cout << "0";
	}
	std::cout << std::endl;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "y" + formatToTwoDigits(i);
		if (i == bit)
		{
			memory[meme] = 1;
			std::cout << "1";
		}
		else
		{
			memory[meme] = 0;
			std::cout << "0";
		}
	}
	std::cout << std::endl;
	while (operations.size())
	{
		for (i = 0; i < operations.size(); i++)
		{
			if (memory.find(operations[i][VALUE1]) != memory.end() && memory.find(operations[i][VALUE2]) != memory.end())
			{
				if (operations[i][OPERATOR] == "AND")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] & memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "OR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] | memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "XOR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] ^ memory[operations[i][VALUE2]];
				}
				operations.erase(operations.begin() + i);
			}
		}
	}
	j = 1;
	for (auto it = memory.begin(); it != memory.end(); ++it)
	{
		if (it->first[0] == 'z')
		{
			// std::cout << it->first << " " << j << " " << it->second << std::endl;
			if (it->second)
				std::cout << "1";
			else
				std::cout << "0";
			j <<= 1;
		}
	}
	std::cout << std::endl;
}

void ok_test10(std::map<std::string, int> memory, std::vector<std::vector<std::string>> operations, size_t bit)
{
	size_t	i = 0;
	size_t	j;
	std::string	meme;

	(void) bit;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "x" + formatToTwoDigits(i);
		if (i == bit)
		{
			memory[meme] = 1;
			std::cout << "1";
		}
		else
		{
			memory[meme] = 0;
			std::cout << "0";
		}
	}
	std::cout << std::endl;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "y" + formatToTwoDigits(i);
		memory[meme] = 0;
		std::cout << "0";
	}
	std::cout << std::endl;
	while (operations.size())
	{
		for (i = 0; i < operations.size(); i++)
		{
			if (memory.find(operations[i][VALUE1]) != memory.end() && memory.find(operations[i][VALUE2]) != memory.end())
			{
				if (operations[i][OPERATOR] == "AND")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] & memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "OR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] | memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "XOR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] ^ memory[operations[i][VALUE2]];
				}
				operations.erase(operations.begin() + i);
			}
		}
	}
	j = 1;
	for (auto it = memory.begin(); it != memory.end(); ++it)
	{
		if (it->first[0] == 'z')
		{
			// std::cout << it->first << " " << j << " " << it->second << std::endl;
			if (it->second)
				std::cout << "1";
			else
				std::cout << "0";
			j <<= 1;
		}
	}
	std::cout << std::endl;
}

void ok_test11(std::map<std::string, int> memory, std::vector<std::vector<std::string>> operations, size_t bit)
{
	size_t	i = 0;
	size_t	j;
	std::string	meme;

	(void) bit;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "x" + formatToTwoDigits(i);
		if (i == bit)
		{
			memory[meme] = 1;
			std::cout << "1";
		}
		else
		{
			memory[meme] = 0;
			std::cout << "0";
		}
	}
	std::cout << std::endl;
	for (i = 0; i < MAXBIT; i++)
	{
		meme = "y" + formatToTwoDigits(i);
		if (i == bit)
		{
			memory[meme] = 1;
			std::cout << "1";
		}
		else
		{
			memory[meme] = 0;
			std::cout << "0";
		}
	}
	std::cout << std::endl;
	while (operations.size())
	{
		for (i = 0; i < operations.size(); i++)
		{
			if (memory.find(operations[i][VALUE1]) != memory.end() && memory.find(operations[i][VALUE2]) != memory.end())
			{
				if (operations[i][OPERATOR] == "AND")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] & memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "OR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] | memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "XOR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] ^ memory[operations[i][VALUE2]];
				}
				operations.erase(operations.begin() + i);
			}
		}
	}
	j = 1;
	for (auto it = memory.begin(); it != memory.end(); ++it)
	{
		if (it->first[0] == 'z')
		{
			// std::cout << it->first << " " << j << " " << it->second << std::endl;
			if (it->second)
				std::cout << "1";
			else
				std::cout << "0";
			j <<= 1;
		}
	}
	std::cout << std::endl;
}

void	part1()
{
	long long	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	std::vector<std::vector<std::string>> operations;
	std::string			line;
	std::map<std::string, int> memory;
	
	// Read the file line by line"

	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	while (std::getline(file, line)) {
		// std::cout << line << std::endl; 
		std::istringstream stream(line);
		std::string word;
		std::vector<std::string> operation;
		
		// Extract words separated by spaces
			while (stream >> word)
			{
				operation.push_back(word);
			}
			operations.push_back(operation);
	}
	size_t	i;
	size_t	j;
	(void) j;
	for (i = 0; i < lines.size(); i++)
	{
		std::string cell = lines[i].substr(0,3);
		int	value = std::stoi(lines[i].substr(5,2));
		// std::cout << cell << "   " << value << std::endl;
		memory[cell] = value;
	}
	while (operations.size())
	{
		for (i = 0; i < operations.size(); i++)
		{
			if (memory.find(operations[i][VALUE1]) != memory.end() && memory.find(operations[i][VALUE2]) != memory.end())
			{
				if (operations[i][OPERATOR] == "AND")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] & memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "OR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] | memory[operations[i][VALUE2]];
				}
				else if (operations[i][OPERATOR] == "XOR")
				{
					memory[operations[i][RESULT]] = memory[operations[i][VALUE1]] ^ memory[operations[i][VALUE2]];
				}
				operations.erase(operations.begin() + i);
			}
		}
	}
	j = 1;
	for (auto it = memory.begin(); it != memory.end(); ++it)
	{
		if (it->first[0] == 'z')
		{
			// std::cout << it->first << " " << j << " " << it->second << std::endl;
			if (it->second)
				result |= j;
			j <<= 1;
		}
	}
	file.close();
	std::cout << result << std::endl;
}

// test 4 numbers 0-0 0-1 1-0 1-1
// see the lowest bit when it deviates

// maybe check for carry later

void	part2()
{
	std::string	result;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	std::vector<std::vector<std::string>> operations;
	std::string			line;
	std::map<std::string, int> memory;
	
	// Read the file line by line"

	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	while (std::getline(file, line)) {
		// std::cout << line << std::endl; 
		std::istringstream stream(line);
		std::string word;
		std::vector<std::string> operation;
		
		// Extract words separated by spaces
			while (stream >> word)
			{
				operation.push_back(word);
			}
			operations.push_back(operation);
	}
	size_t	i;
	size_t	j;
	(void) j;
	for (i = 0; i < lines.size(); i++)
	{
		std::string cell = lines[i].substr(0,3);
		int	value = std::stoi(lines[i].substr(5,2));
		// std::cout << cell << "   " << value << std::endl;
		memory[cell] = value;
	}
	//fdv, vjf
	ok_deep(operations, "z04", 5);
	ok_deep(operations, "z05", 5);
	ok_deep(operations, "z38", 5);
	ok_deep(operations, "z39", 5);
	ok_deep(operations, "z40", 5);
	std::string	swap1 = "dbp";
	std::string swap2 = "fdv";
	std::string	swap3 = "z15";
	std::string swap4 = "ckj";
	std::string	swap5 = "kdf";
	std::string swap6 = "z23";
	std::string	swap7 = "z39";
	std::string swap8 = "rpp";
	ok_swap(operations, swap1, swap2);
	ok_swap(operations, swap3, swap4);
	ok_swap(operations, swap5, swap6);
	ok_swap(operations, swap7, swap8);
	for (i = 0; i < MAXBIT; i++)
	{
		std::cout << i << std::endl;
		ok_test00(memory, operations, i);
		std::cout << std::endl;
		ok_test01(memory, operations, i);
		std::cout << std::endl;
		ok_test10(memory, operations, i);
		std::cout << std::endl;
		ok_test11(memory, operations, i);
		std::cout << std::endl;
	}
	file.close();
	std::set<std::string> swaps;
	swaps.insert(swap1);
	swaps.insert(swap2);
	swaps.insert(swap3);
	swaps.insert(swap4);
	swaps.insert(swap5);
	swaps.insert(swap6);
	swaps.insert(swap7);
	swaps.insert(swap8);
	for (auto swap : swaps)
		result += swap + ",";
	result.pop_back();
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
