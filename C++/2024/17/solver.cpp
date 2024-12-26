#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

#define MAP 50
#define FILE "input.txt"
#define WIDTH 101
#define HEIGHT 103
// #define FILE "test"
// #define WIDTH 11
// #define HEIGHT 7
#define MOVES 100

#define EAST 1
#define WEST 2
#define NORTH 4
#define SOUTH 8


void	run_program(std::string &output, std::vector<int> &program, unsigned long long regA, unsigned long long regB, unsigned long long regC)
{
	size_t	i = 0;
	int		operand;
	unsigned long long		combo;
	int		instruction;

	while (i < program.size() - 1)
	{
		instruction = program[i];
		operand = program[i + 1];
		combo = operand;
		i += 2;
		if (operand == 4)
			combo = regA;
		else if (operand == 5)
			combo = regB;
		else if (operand == 6)
			combo = regC;
		// else if (operand == 7)
		// 	std::cerr << "Error 777" << std::endl;
		if (instruction == 0)
		{
			regA = regA / (1 << combo);
		}
		else if (instruction == 1)
		{
			regB ^= operand;
		}
		else if (instruction == 2)
		{
			regB = combo % 8;
		}
		else if (instruction == 3)
		{
			if (regA)
			{
				if ((i - 2) != (size_t)operand)	//maybe?
					i = operand;
			}
		}
		else if (instruction == 4)
		{
			regB ^= regC;
		}
		else if (instruction == 5)
		{
			if (output.size())
				output += ',';
			output += '0' + (combo % 8);
		}
		else if (instruction == 6)
		{
			regB = regA / (1 << combo);
		}
		else if (instruction == 7)
		{
			regC = regA / (1 << combo);
		}
	}
}

void	init_program(std::vector<std::string> &lines, std::vector<int> &program, unsigned long long &regA, unsigned long long &regB, unsigned long long &regC)
{
	size_t		pos = lines[0].find(":");
	std::string	str = lines[0].substr(pos + 1);
	regA = std::stoi(str);

	pos = lines[1].find(":");
	str = lines[1].substr(pos + 1);
	regB = std::stoi(str);

	pos = lines[2].find(":");
	str = lines[2].substr(pos + 1);
	regC = std::stoi(str);

	pos = lines[4].find(":");
	str = lines[4].substr(pos + 1);

	std::istringstream program_stream(str);
	int program_value;
	char comma;

	// Parse the comma-separated integers in the program line
	while (program_stream >> program_value)
	{
		program.push_back(program_value);
		program_stream >> comma;  // Skip the comma after each number
	}
}

void	part1()
{
	std::string	result = "";
	unsigned long long regA = 0;
	unsigned long long regB = 0;
	unsigned long long regC = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string>	lines;
	std::string					line;
	std::vector<int>			program;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Prunsigned long long each line to the console
		lines.push_back(line);
	}
	init_program(lines, program, regA, regB, regC);
	std::cout << "Register A: " << regA << std::endl;
	std::cout << "Register B: " << regB << std::endl;
	std::cout << "Register C: " << regC << std::endl;
	std::cout << "Program: ";
	for (const auto& val : program) {
		std::cout << val << " ";
	}
	std::cout << std::endl << std::endl;
	run_program(result, program, regA, regB, regC);
	file.close();
	std::cout << result << std::endl;
}
void	part2()
{
	std::string	output = "";
	unsigned long long result = 0;
	unsigned long long regA = 0;
	unsigned long long regB = 0;
	unsigned long long regC = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string>	lines;
	std::string					line;
	std::string					orig = "";
	std::vector<int>			program;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	init_program(lines, program, regA, regB, regC);
	std::cout << "Register A: " << regA << std::endl;
	std::cout << "Register B: " << regB << std::endl;
	std::cout << "Register C: " << regC << std::endl;
	std::cout << "Program: ";
	for (const auto& val : program) {
		std::cout << val << " ";
	}
	for (size_t i = 0; i < program.size(); i++)
	{
		if (i)
			orig += ',';
		orig += '0' + program[i];
	}
	// regA = 174504540372800ULL;
	// regA = 174577517266434; // too high
	regA = 156985331106427 - 1; //input the last best match
	run_program(output, program, regA, regB, regC);
	//reversing strings because apparently the last value is least affected by the register value change
	std::reverse(output.begin(), output.end());
	std::reverse(orig.begin(), orig.end());
	std::cout << std::endl << orig << std::endl;
	size_t	match = 0;
	size_t	oldmatch = 0;
	size_t	iter = 0;
	while (output != orig)
	{
		iter++;
		//commented out but it was useful to get rough estimates and get the lenth right
		// if (output.size() < orig.size())
		// {
		// 	// regA *= 2;
		// }
		// else if (output.size() > orig.size())
		// {
		// 	// regA /= 2;
		// }
		// else
		{
			match = 0;
			while (match < output.size() && output[match] == orig[match])
				match++;
			regA += 1; // fine tune this value
			if (match > oldmatch && output.size() == orig.size())
			{
				oldmatch = match;
				(void)oldmatch;
				std::cout << match << std::endl;
				std::cout << regA << std::endl;
				std::cout << output << std::endl;
			}
			// if (iter % 65536 == 0)
			// {
			// 	oldmatch = match;
			// 	(void)oldmatch;
			// 	std::cout << match << std::endl;
			// 	std::cout << output.size() << " " << orig.size() << std::endl;
			// 	std::cout << regA << std::endl;
			// 	std::cout << output << std::endl;
			// }
			// std::cout << match << std::endl;
			// std::cout << regA << std::endl;
			// std::cout << output << std::endl;
		}
		output.clear();
		run_program(output, program, regA, regB, regC);
		std::reverse(output.begin(), output.end());
	}
	result = regA;
	file.close();
	std::cout << output << std::endl;
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