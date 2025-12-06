#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

void convertStringToIntegers(const std::string& str, long long& a, long long& b) {
	std::string cleaned = str;
	for (char& c : cleaned)
		if (!isdigit(c)) c = ' ';

	std::stringstream ss(cleaned);
	ss >> a;
	ss >> b;
}


void convertStringToInteger(const std::string& str, long long& a) {
	std::stringstream ss(str);
	ss >> a;
}


void convertIntegerToString(const long long num, std::string& str) {
	std::stringstream ss;
	ss << num;
	ss >> str;
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


	long long		a;
	long long		b;
	long long		c;
	long long		d;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;
	std::vector<long long> min;
	std::vector<long long> max;

	// Read the file line by line
	std::vector<std::string> lines;
	std::vector<std::vector<std::string>> array;
	std::string			line;
	std::string			word;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		std::stringstream ss(line);
		while (ss >> word)
			lines.push_back(word);
		array.push_back(lines);
		lines.clear();
	}
	a = array.size() - 1;
	b = array[0].size();
	for (int i = 0; i < b; i++)
	{
		convertStringToInteger(array[0][i], d);
		std::cout << d << std::endl;
		c = d;
		for (int j = 1; j < a; j++) {
			convertStringToInteger(array[j][i], d);
			std::cout << d << std::endl;
			if (array[a][i] == "*")
				c *= d;
			if (array[a][i] == "+")
				c += d;
		}
		result += c;
	}
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


	long long		a;
	long long		b;
	long long		c;
	long long		d;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;
	std::vector<long long> min;
	std::vector<long long> max;

	// Read the file line by line
	std::vector<std::string> lines;
	std::vector<std::vector<std::string>> array;
	std::string			line;
	std::string			word;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	a = lines.size() - 1;
	b = lines[0].size() - 1;
	std::vector<std::string> words;
	for (int i = b; i >= 0; i--) {
		word.clear();
		for (int j = 0; j < a; j++) {
			if (lines[j][i] != ' ')
				word.push_back(lines[j][i]);
		}
		std::cout << word << std::endl;
		words.push_back(word);
		if (lines[a][i] == '+')
		{
			convertStringToInteger(words[0], d);
			c = d;
			for (int x = 1; x < words.size(); x++)
			{
				convertStringToInteger(words[x], d);
				c += d;
			}
			words.clear();
			result += c;
			i--;
		}
		if (lines[a][i] == '*')
		{
			convertStringToInteger(words[0], d);
			c = d;
			for (int x = 1; x < words.size(); x++)
			{
				convertStringToInteger(words[x], d);
				c *= d;
			}
			words.clear();
			result += c;
			i--;
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