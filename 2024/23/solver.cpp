#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <set>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>


#define FILE "input.txt"
#define SAVE 100
#define PICO 20
#define DEPTH1 2
#define DEPTH2 25


#define EAST 1
#define WEST 2
#define NORTH 4
#define SOUTH 8

#define ROBOTA 0
#define ROBOTB 1
#define ROBOTC 2
#define ME 3

void	build_temp(std::set<std::string> &temp, std::map<std::string, std::set<std::string>> &m, std::string candidate)
{
	size_t matches = 0;
	if (temp.find(candidate) != temp.end())
		return ;
	//check candidate contains all values from the set
	for (std::set<std::string>::iterator it = m[candidate].begin(); it != m[candidate].end(); ++it)
	{
		// std::cout << *it << ",";
		if (temp.find(*it) != temp.end())
			matches++;
	}
	// std::cout << std::endl;
	if (matches != temp.size())
		return ;
	//add candidate
	temp.insert(candidate);
	//check for candidate neighbours
	for (std::set<std::string>::iterator it = m[candidate].begin(); it != m[candidate].end(); ++it)
	{
		build_temp(temp, m, *it);
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

	std::vector<std::string> lines;
	
	std::string			line;
	
	// Read the file line by line"

	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	size_t	i;
	std::multimap<std::string, std::string> connections;
	std::set<std::array<std::string, 3>> triples;
	for (i = 0; i < lines.size(); i++)
	{
		std::string pc1 = lines[i].substr(0, 2);
		std::string pc2 = lines[i].substr(3, 2);
		
		bool exists = false;
		for (std::multimap<std::string, std::string>::iterator it = connections.begin(); it != connections.end(); ++it)
		{
			if (it->first == pc1 && it->second == pc2)
			{
				exists = true;
				break;
			}
		}
		if (exists)
		{
			std::cout << "EXISTS: " << pc1 << ", " << pc2 << std::endl;
			continue ;
		}
		connections.insert(std::make_pair(pc1, pc2));
		connections.insert(std::make_pair(pc2, pc1));
	}

	for (std::multimap<std::string, std::string>::iterator it = connections.begin(); it != connections.end(); ++it)
	{
		std::string pc1 = it->first;
		std::string pc2 = it->second;
		std::pair<std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> range = connections.equal_range(pc2);
		// std::cout << "0" << pc1 << pc2 << std::endl;
		for (std::multimap<std::string, std::string>::iterator iter = range.first; iter != range.second; ++iter)
		{
			std::string pc3 = iter->second;
			std::pair<std::multimap<std::string, std::string>::iterator, std::multimap<std::string, std::string>::iterator> range = connections.equal_range(pc3);

			for (std::multimap<std::string, std::string>::iterator iterat = range.first; iterat != range.second; ++iterat)
			{
				std::string pc4 = iterat->second;
				if (pc1 == pc4 && pc1 != pc3)
				{
					if (pc1[0] == 't' || pc2[0] == 't' || pc3[0] == 't')
					{
						std::array<std::string, 3> arr = {pc1, pc2, pc3};
						std::sort(arr.begin(), arr.end());
						triples.insert(arr);
					}
				}
			}
		}
	}
	// for (std::set<std::array<std::string, 3>>::iterator it = triples.begin(); it != triples.end(); ++it)
	// {
	// 	std::cout << (*it)[0] << (*it)[1] << (*it)[2] << std::endl;
	// }
	result = triples.size();
	file.close();
	std::cout << result << std::endl;
}

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
	
	std::string			line;
	
	// Read the file line by line"

	while (std::getline(file, line) && line[0]) {
		// std::cout << line << std::endl; 
		lines.push_back(line);
	}
	size_t	i;
	std::multimap<std::string, std::string> connections;
	std::map<std::string, std::set<std::string>> m;
	for (i = 0; i < lines.size(); i++)
	{
		std::string pc1 = lines[i].substr(0, 2);
		std::string pc2 = lines[i].substr(3, 2);
		
		bool exists = false;
		for (std::multimap<std::string, std::string>::iterator it = connections.begin(); it != connections.end(); ++it)
		{
			if (it->first == pc1 && it->second == pc2) //probably unnecessary check
			{
				exists = true;
				std::cerr << "SUS" << std::endl;
				break;
			}
		}
		if (exists)
		{
			std::cout << "EXISTS: " << pc1 << ", " << pc2 << std::endl;
			continue ;
		}
		connections.insert(std::make_pair(pc1, pc2));
		connections.insert(std::make_pair(pc2, pc1));
	}
	std::set<std::string>	max;
	std::set<std::string>	temp;
	for (std::multimap<std::string, std::string>::iterator it1 = connections.begin(); it1 != connections.end(); ++it1)
	{
		m[it1->first].insert(it1->second);
	}
	for (std::map<std::string, std::set<std::string>>::iterator it1 = m.begin(); it1 != m.end(); ++it1)
	{
		// std::cout << it1->first << ": ";
		for (std::set<std::string>::iterator it2 = it1->second.begin(); it2 != it1->second.end(); ++it2)
		{
			// std::cout << *it2 << ",";
			temp.insert(it1->first);
			build_temp(temp, m, *it2);
			if (temp.size() > max.size())
				max = temp;
			temp.clear();
		}
		// std::cout << std::endl;
	}
	file.close();
	for (std::set<std::string>::iterator it = max.begin(); it != max.end(); ++it)
			result += *it + ",";
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