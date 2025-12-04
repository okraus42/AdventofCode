#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>

void convertStringToIntegers(const std::string& str, std::vector<long long>& numbers) {
	std::string cleaned = str;
	for (char& c : cleaned)
		if (!isdigit(c)) c = ' ';

	std::stringstream ss(cleaned);
	long long num;
	while (ss >> num) {
		numbers.push_back(num);
	}
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

	std::string		line;
	long long		a;
	long long		b;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;

	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		a = 0;
		b = 0;
		int n = line.size();
		for (int i = 0; i < n; i++) {
			if (i == 0)
			{
				a = line[i];
			}
			else if (i == line.size() - 1 && line[i] > b) {
				b = line[i];
			}
			else if (line[i] > a) {
				b = 0;
				a = line[i];
			}
			else if (line[i] > b)
				b = line[i];
				
		}
		result += (a - '0') * 10 + (b - '0');
		std::cout <<  (a - '0') * 10 + (b - '0') << std::endl;
	}
	file.close();
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

	std::string		line;
	long long		a;
	long long		b[12];
	long long		c;
	int				d = 0;
	long long		invalids = 0;
	int				dial = 50;
	std::vector<long long> numbers;

	// Read the file line by line
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		for (int i = 0; i < 12; i++)
			b[i] = '0';
		int n = line.size();
		d = 0;
		for (int i = 0; i < n; i++) {
			if (i > n - 12) {
				d = 12 - (n - i);
				// std::cout << d << std::endl;
			}
			for (int j = d; j < 12; j++) {
				if (line[i] > b[j]) {
					b[j++] = line[i];
					while (j < 12) {
						b[j++] = '0'; 
					}
				}
			}
			for (int x = 0; x < 12; x++)
				std::cout << b[x] - '0';
			std::cout <<std::endl;
		}
		for (int i = 0; i < 12; i++) {
			b[i] -= '0';
			// std::cout << "b " << b[i] << std::endl;
		}
		a = 1;
		c = 0;
		for (int i = 11; i >= 0; i--) {
			b[i] *= a;
			a *= 10;
			c += b[i];
			// std::cout << "c " << c << std::endl;
		}
		result += c;
		std::cout << "c " << c << std::endl;
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