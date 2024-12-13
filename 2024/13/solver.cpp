#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

#define MAP 50
#define FILE "input.txt"


void	extract_numbers(std::vector<std::string> &lines, size_t i, long long &xa, long long &ya, long long &xb, long long &yb, long long &xp, long long &yp)
{
	size_t	posX = lines[i].find("X");
	size_t	posY = lines[i].find("Y");
	std::string xStr = lines[i].substr(posX + 1);
	std::string yStr = lines[i].substr(posY + 1);
	xa = std::stoi(xStr);
	ya = std::stoi(yStr);

	posX = lines[i + 1].find("X");
	posY = lines[i + 1].find("Y");
	xStr = lines[i + 1].substr(posX + 1);
	yStr = lines[i + 1].substr(posY + 1);
	xb = std::stoi(xStr);
	yb = std::stoi(yStr);

	// Extract Strs for "Prize: X=8400, Y=5400"
	posX = lines[i + 2].find("X");
	posY = lines[i + 2].find("Y");
	xStr = lines[i + 2].substr(posX + 2);
	yStr = lines[i + 2].substr(posY + 2);
	xp = std::stoi(xStr);
	yp = std::stoi(yStr);
}

long long	need_tokens1(std::vector<std::string> &lines, size_t i)
{
	long long xa;
	long long ya;
	long long xb;
	long long yb;
	long long xp;
	long long yp;
	long long tokens = 0;
	long long current = 0;

	extract_numbers(lines, i, xa, ya, xb, yb, xp, yp);
	for (long long a = 0; a < 125; a++)
	{
		for (long long b = 0; b < 125; b++)
		{
			if (a * xa + b * xb == xp && a * ya + b * yb == yp)
			{
				current = a * 3 + b;
			}
			if (current && current < tokens)
				tokens = current;
			if (!tokens && current)
				tokens = current;
		}
	}
	std::cout << tokens << std::endl;
	return (tokens);
}

//Cramer's rule
long long	need_tokens2(std::vector<std::string> &lines, size_t i)
{
	long long xa;
	long long ya;
	long long xb;
	long long yb;
	long long xp;
	long long yp;
	long long tokens = 0;
	long long a;
	long long b;

	extract_numbers(lines, i, xa, ya, xb, yb, xp, yp);
	xp += 10000000000000;
	yp += 10000000000000;
	long long determinant = xa * yb - ya * xb;
	if (determinant != 0)
	{
		a = (xp * yb - xb * yp) / determinant;
		b = (xa * yp - xp * ya) / determinant;
		std::cout << "result,a = " << a << ", b = " << b << std::endl;
		//need check if our result is integer
		if (a * xa + b * xb == xp && a * ya + b * yb == yp)
			tokens = 3 * a + b;
	}
	else
	{
		std::cout << "zero determinant" << std::endl;
	}
	std::cout << tokens << std::endl;
	return (tokens);
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
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	size_t i;

	std::set<long long> locations;
	for (i = 0; i < lines.size(); i += 4)
	{
		result += need_tokens1(lines, i);
	}
	file.close();
	std::cout << result << std::endl;
}
void	part2()
{
	long long	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	size_t i;

	std::set<long long> locations;
	for (i = 0; i < lines.size(); i += 4)
	{
		result += need_tokens2(lines, i);
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