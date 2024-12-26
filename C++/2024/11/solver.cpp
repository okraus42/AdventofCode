#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <map>
#include <vector>
#include <list>
#include <sstream>


// #define FILE "test"
#define FILE "input.txt"

void convertStringToIntegers(const std::string& str, std::list<long long> &numbers) {
	std::stringstream ss(str);
	int num;
	while (ss >> num) {
		numbers.push_back(num);
	}
}

void	printList(std::list<long long> &numbers)
{
	std::list<long long>::iterator it;
	for (it = numbers.begin(); it != numbers.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int	countDigits(long long num)
{
	int	i = 0;
	while (num)
	{
		i++;
		num /= 10;
	}
	return (i);
}

long long firstHalf(long long num, int digits)
{
	int temp = 1;
	for (int i = 0; i < digits / 2; i++)
	{
		temp *= 10;
	}
	num /= temp;
	return (num);
}

long long secondHalf(long long num, int digits)
{
	int temp = 1;
	for (int i = 0; i < digits / 2; i++)
	{
		temp *= 10;
	}
	num %= temp;
	return (num);
}

void	iterate(std::list<long long> &numbers)
{
	std::list<long long>::iterator it = numbers.begin();
	std::list<long long>::iterator next;
	// std::list<long long>::iterator prev;
	while (it != numbers.end())
	{
		next = it;
		next++;
		int digits = countDigits(*it);
		// prev = it;
		// prev--;
		if (*it == 0)
		{
			*it = 1;
			// numbers.erase(it);
			it = next;
		}
		else if ((digits % 2) == 0)
		{
			numbers.insert(next, secondHalf(*it, digits));
			*it = firstHalf(*it, digits);
			it = next;
		}
		else
		{
			*it *= 2024;
			it = next;
		}
	}
	// printList(numbers);
}

long long count(long long num, int blinks, std::map<std::pair<long long, int>, long long> &hashmap)
{
	long long res;
	if (!blinks)
		return (1);
	std::pair<long long, int> combo = std::make_pair(num, blinks);
	// std::cout << num  << "  " << blinks << std::endl;
	// std::cout << "n " << num  << " b " << blinks << std::endl;
	if (hashmap.find(combo) != hashmap.end())
	{
		// std::cout << "REPEAT" << std::endl;
		// std::cout << "res " << hashmap[combo] << std::endl;
		return(hashmap[combo]);
	}
	if (num == 0)
	{
		// std::cout << "zero" << std::endl;
		res = count(1, blinks - 1, hashmap);
		hashmap[combo] = res;
		// std::cout << "zero2" << std::endl;
		// std::cout << "n " << num  << " b " << blinks << std::endl;
		// std::cout << "res " << hashmap[combo] << std::endl;
		return (res);
	}
	else if ((countDigits(num) % 2) == 0)
	{
		// std::cout << "countcount" << std::endl;
		res = count(firstHalf(num, countDigits(num)), blinks - 1, hashmap);
		res += count(secondHalf(num, countDigits(num)), blinks - 1, hashmap);
		hashmap[combo] = res;
		// std::cout << "countcount2" << std::endl;
		// std::cout << "n " << num  << " b " << blinks << std::endl;
		// std::cout << "res " << hashmap[combo] << std::endl;
		return (res);
	}
	else
	{
		// std::cout << "2024..." << std::endl;
		res = count(num * 2024, blinks - 1, hashmap);
		hashmap[combo] = res;
		// std::cout << "2024...2" << std::endl;
		// std::cout << "n " << num  << " b " << blinks << std::endl;
		// std::cout << "res " << hashmap[combo] << std::endl;
		return (res);
	}
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

	std::string			line;
	// Read the file line by line
	std::getline(file, line);
	std::list<long long> numbers;
	convertStringToIntegers(line, numbers);
	printList(numbers);
	for (int i = 0; i < 25; i++)
	{
		iterate(numbers);
		std::cout << i << ": " << numbers.size() << std::endl;
	}
	file.close();
	result = numbers.size();
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
	std::string			line;
	// Read the file line by line
	std::getline(file, line);
	std::list<long long> numbers;
	std::map<std::pair<long long, int>, long long>	hashmap;
	convertStringToIntegers(line, numbers);
	printList(numbers);
	std::list<long long>::iterator it = numbers.begin();
	while (it != numbers.end())
	{
		result += count(*it, 75, hashmap);
		// std::cout << "RESULT " << result << std::endl;
		*it++;
	}
	file.close();
	// result = numbers.size(); FU line I forgot to comment
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