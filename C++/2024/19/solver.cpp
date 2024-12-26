#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>

#define MAP 71
#define FILE "input.txt"
#define BYTES 1024
// #define MAP 7
// #define FILE "test"
// #define BYTES 12
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

void	extract_towels(std::string &towel_line, std::set<std::string> &towels)
{
	std::stringstream	ss(towel_line);
	std::string			token;
	
	while (std::getline(ss, token, ','))
	{
		// Trim leading and trailing spaces from each token
		token.erase(0, token.find_first_not_of(' '));  // Remove leading spaces
		token.erase(token.find_last_not_of(' ') + 1); // Remove trailing spaces
		
		// Add the token to the vector
		towels.insert(token);
	}
}

int g_found = 0;
int	possible(std::string &line, std::set<std::string> &towels, std::string temp)
{
	size_t		i;
	// std::cout << line << std::endl;
	// std::cout << temp << std::endl;
	if (line == temp)
	{
		g_found = 1;
		return (1);
	}
	if (g_found)
		return (1);
	std::string	match7 = line.substr(temp.size(), 7);
	std::string	match6 = line.substr(temp.size(), 6);
	std::string	match5 = line.substr(temp.size(), 5);
	std::string	match4 = line.substr(temp.size(), 4);
	std::string	match3 = line.substr(temp.size(), 3);
	std::string	match2 = line.substr(temp.size(), 2);
	std::string	match1 = line.substr(temp.size(), 1);
	
	i = 0;
	if (match7.size() == 7 && towels.find(match7) != towels.end())
		i += possible(line, towels, temp + match7);
	if (match6.size() == 6 && towels.find(match6) != towels.end())
		i += possible(line, towels, temp + match6);
	if (match5.size() == 5 && towels.find(match5) != towels.end())
		i += possible(line, towels, temp + match5);
	if (match4.size() == 4 && towels.find(match4) != towels.end())
		i += possible(line, towels, temp + match4);
	if (match3.size() == 3 && towels.find(match3) != towels.end())
		i += possible(line, towels, temp + match3);
	if (match2.size() == 2 && towels.find(match2) != towels.end())
		i += possible(line, towels, temp + match2);
	if (match1.size() == 1 && towels.find(match1) != towels.end())
		i += possible(line, towels, temp + match1);
	return (i);
}


//  722806860814155 // too low
long long	possible2(std::string &line, std::set<std::string> &towels, std::string temp, std::vector<long long> &hash)
{
	long long	i;
	// std::cout << line << std::endl;
	// std::cout << temp << std::endl;
	if (hash[temp.size()] != - 1)
		return (hash[temp.size()]);
	if (line == temp)
	{
		return (1);
	}
	std::string	match8 = line.substr(temp.size(), 8);
	std::string	match7 = line.substr(temp.size(), 7);
	std::string	match6 = line.substr(temp.size(), 6);
	std::string	match5 = line.substr(temp.size(), 5);
	std::string	match4 = line.substr(temp.size(), 4);
	std::string	match3 = line.substr(temp.size(), 3);
	std::string	match2 = line.substr(temp.size(), 2);
	std::string	match1 = line.substr(temp.size(), 1);
	
	i = 0;
	if (match1.size() == 1 && towels.find(match1) != towels.end())
		i += possible2(line, towels, temp + match1, hash);
	if (match2.size() == 2 && towels.find(match2) != towels.end())
		i += possible2(line, towels, temp + match2, hash);
	if (match3.size() == 3 && towels.find(match3) != towels.end())
		i += possible2(line, towels, temp + match3, hash);
	if (match4.size() == 4 && towels.find(match4) != towels.end())
		i += possible2(line, towels, temp + match4, hash);
	if (match5.size() == 5 && towels.find(match5) != towels.end())
		i += possible2(line, towels, temp + match5, hash);
	if (match6.size() == 6 && towels.find(match6) != towels.end())
		i += possible2(line, towels, temp + match6, hash);
	if (match7.size() == 7 && towels.find(match7) != towels.end())
		i += possible2(line, towels, temp + match7, hash);
	if (match8.size() == 8 && towels.find(match8) != towels.end())
		i += possible2(line, towels, temp + match8, hash);
	hash[temp.size()] = i;
	return (i);
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

	std::vector<std::string>	lines;
	std::set<std::string>		towels;
	std::string					towel_line;
	std::string					line;
	
	std::getline(file, towel_line);
	extract_towels(towel_line, towels);
	std::getline(file, towel_line);

	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	
	size_t	i;
	for (const auto& str : towels)
	{
		std::cout << str << " | ";
	}
	std::cout << std::endl;
	for (i = 0; i < lines.size(); i++)
	{
		std::cout << lines[i] << std::endl;
	}
	for (i = 0; i < lines.size(); i++)
	{
		g_found = 0;
		if (possible(lines[i], towels, ""))
			result++;
		std::cout << i << ", " << result << std::endl;
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

	std::vector<std::string>	lines;
	std::set<std::string>		towels;
	std::string					towel_line;
	std::string					line;
	std::vector<long long>		hash;
	std::getline(file, towel_line);
	extract_towels(towel_line, towels);
	std::getline(file, towel_line);

	// Read the file line by line
	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl;  // Prlong long each line to the console
		lines.push_back(line);
	}
	
	size_t	i;
	// for (const auto& str : towels)
	// {
	// 	std::cout << str << " | ";
	// }
	// std::cout << std::endl;
	// for (i = 0; i < lines.size(); i++)
	// {
	// 	std::cout << lines[i] << std::endl;
	// }
	for (i = 0; i < lines.size(); i++)
	{
		hash.clear();
		for (size_t j = 0; j < 80; j++)
			hash.push_back(-1LL);
		result += possible2(lines[i], towels, "", hash);
		std::cout << i << " ||| " << result << std::endl;
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