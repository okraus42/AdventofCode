#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <sstream>


// #define FILE "test"
#define FILE "input.txt"

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
	std::vector<int> disk;
	int	front = 0;
	int	back;
	int	id = 0;
	for (size_t i = 0; i < line.size(); i++)
	{
		int n = line[i] - '0';
		if (i % 2)
		{
			for (int j = 0; j < n; j++)
				disk.push_back(-1);
		}
		else
		{
			for (int j = 0; j < n; j++)
				disk.push_back(id);
			id++;
		}
	}
	//defragment disk
	back = disk.size() - 1;
	while (back > front)
	{
		while (back && disk[back] == -1)
			back--;
		while (front < back && disk[front] != -1)
			front++;
		if (front < back)
		{
			disk[front] = disk[back];
			disk[back] = -1;
		}
		front++;
		back--;
	}
	//check disk
	// for (size_t i = 0; i < disk.size(); i++)
	// {
	// 	std::cout << disk[i];
	// }
	// std::cout <<std::endl;
	front = 0;
	while (disk[front] != -1)
	{
		result += front * disk[front];
		front++;
	}
	file.close();
	std::cout << result << std::endl;
}
void	part2()
{
	long	result = 0;
	std::ifstream file(FILE);
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::string			line;
	// Read the file line by line
	std::getline(file, line);
	std::vector<int> disk;
	long	front = 0;
	long	back;
	int	id = 0;
	for (size_t i = 0; i < line.size(); i++)
	{
		int n = line[i] - '0';
		if (i % 2)
		{
			for (int j = 0; j < n; j++)
				disk.push_back(-n);
		}
		else
		{
			for (int j = 0; j < n; j++)
				disk.push_back(id);
			id++;
		}
	}
	// // check disk
	// for (size_t i = 0; i < disk.size(); i++)
	// {
	// 	std::cout << disk[i] << "|";
	// }
	// std::cout <<std::endl;
	// defragment disk
	back = disk.size() - 1;
	int	file_size = 0;
	while (back > 0 && disk[back])
	{
		front = 0;
		file_size = 0;
		while (back && disk[back] < 0)
			back--;
		if (disk[back])
		{
			while (disk[back] == disk[back - file_size])
				file_size++;
		}
		while (front < back && disk[front] > -file_size)
			front++;
		// std::cout << "back" << back  <<"file" <<file_size << "back" << disk[back]<< std::endl;
		// std::cout <<"front" <<front <<std::endl;
		// // // check disk
		// for (size_t i = 0; i < disk.size(); i++)
		// {
		// 	std::cout << disk[i] << "|";
		// }
		// std::cout <<std::endl <<std::endl;
		if (front < back)
		{
			// std::cout<<"inside" <<std::endl;
			int i = 0;
			for (i = 0; i < file_size; i++)
			{
				disk[front + i] = disk[back];
			}
			for (i = 0; i < file_size; i++)
			{
				disk[back - i] = -file_size;
			}
			int	num = disk[front + i];
			if (num < 0)
			{
				while (disk[front + i] == num)
				{
					disk[front + i] += file_size;
					i++;
				}
			}
		}
		back -= file_size;
	}
	// // check disk
	// for (size_t i = 0; i < disk.size(); i++)
	// {
	// 	std::cout << disk[i] << "|";
	// }
	// std::cout <<std::endl;
	front = 0;
	while (front < (int)disk.size())
	{
		if (disk[front] >= 0)
		{
			result += front * disk[front];
			// std::cout << front << "   " << disk[front] << "|";
		}
		front++;
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