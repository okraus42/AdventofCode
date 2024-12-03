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

int getInt(const std::string& str) {
	std::stringstream ss(str);
	int num;
	ss >> num;
	return (num);
}

int parseString(std::string str)
{
	int num1;
	int num2;
	long long res = 0;
	int i;
	while (str.find("mul(") != std::string::npos)
	{
		i = 0;
		str = str.substr(str.find("mul(") + 4);
		std::cout << "str: " <<str << std::endl;
		if (std::isdigit(str[0]))
		{
			i = 1;
			num1 = getInt(str);
			std::cout <<"n1:" << num1 <<std::endl;
			while (i < str.size() && std::isdigit(str[i]))
				i++;
			if (i < 4 && i < str.size() && str[i] == ',')
			{
				str = str.substr(i + 1);
				if (std::isdigit(str[0]))
				{
					i = 1;
					num2 = getInt(str);
					std::cout <<"n2:" << num2 <<std::endl;
					while (i < str.size() && std::isdigit(str[i]))
						i++;
					if (i < 4 && i < str.size() && str[i] == ')')
					{
						str = str.substr(i + 1);
						res += num1 * num2;
					}
				}
			}
			
		}
	}
	std::cout << "res:" << res <<std::endl;
	return (res);
}


int parseString2(std::string str)
{
	int num1;
	int num2;
	long long res = 0;
	int i;
	const char *m = "mul(";
	const char *d = "do()";
	const char *dn = "don't()";
	static const char *f;
	if (!f && str.find(m) < str.find(dn))
		f = m;
	else if (!f)
		f = d;
	std::cout << "f1: " <<f << std::endl;
	while (str.find(f) != std::string::npos)
	{
		i = 0;
		str = str.substr(str.find(f) + 4);
		std::cout << "str: " <<str << std::endl;
		if (f == d)
		{
			if (str.find(m) <= str.find(dn))
				f = m;
			else
				f = d;
			std::cout << "f2: " <<f << std::endl;
			continue ;
		}
		if (str.find(m) <= str.find(dn))
			f = m;
		else
			f = d;
		std::cout << "f3: " <<f << std::endl;
		if (std::isdigit(str[0]))
		{
			i = 1;
			num1 = getInt(str);
			std::cout <<"n1:" << num1 <<std::endl;
			while (i < str.size() && std::isdigit(str[i]))
				i++;
			if (i < 4 && i < str.size() && str[i] == ',')
			{
				str = str.substr(i + 1);
				if (std::isdigit(str[0]))
				{
					i = 1;
					num2 = getInt(str);
					std::cout <<"n2:" << num2 <<std::endl;
					while (i < str.size() && std::isdigit(str[i]))
						i++;
					if (i < 4 && i < str.size() && str[i] == ')')
					{
						str = str.substr(i + 1);
						res += num1 * num2;
					}
				}
			}
			
		}
	}
	std::cout << "res:" << res <<std::endl;
	return (res);
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

	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		result += parseString(line);
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

	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;  // Print each line to the console
		result += parseString2(line);
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