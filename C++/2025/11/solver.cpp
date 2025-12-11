#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>

void convertStringToIntegers(const std::string& str, std::vector<boost::multiprecision::cpp_int>& numbers) {
	std::string cleaned = str;
	for (char& c : cleaned)
		if (!isdigit(c)) c = ' ';

	std::stringstream ss(cleaned);
	boost::multiprecision::cpp_int num;
	while (ss >> num) {
		numbers.push_back(num);
	}
}

void convertIntegerToString(const boost::multiprecision::cpp_int num, std::string& str) {
	std::stringstream ss;
	ss << num;
	ss >> str;
}

typedef struct s_device {
	std::string name;
	std::vector<std::string>	next;
	boost::multiprecision::cpp_int					in;
	boost::multiprecision::cpp_int					in_d;
	boost::multiprecision::cpp_int					in_f;
	boost::multiprecision::cpp_int					in_df;
}	t_device;

t_device	get_device(std::string& str) {
	t_device device;
	std::stringstream ss;
	ss << str;
	std::string word;
	ss >> word;
	device.name = word.substr(0, word.size() - 1);
	while (ss >> word) {
		// std::cout << word;
		device.next.push_back(word);
		word.clear();
	}
	// std::cout << std::endl;
	return device;
}

void	part1()
{
	boost::multiprecision::cpp_int	result = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}


	std::vector<boost::multiprecision::cpp_int>	nums;
	std::vector<std::vector<boost::multiprecision::cpp_int>>	numbers;
	std::map<std::string, t_device>		devices;
	std::vector<std::string>				f;

	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		t_device d;
		d = get_device(line);
		devices[d.name] = d;
		lines.push_back(line);
	}
	devices["you"].in = 1;
	for (auto d : devices)
	{
		std::cout << d.second.name << ": ";
		for (int i = 0; i < d.second.next.size(); i++)
			std::cout << d.second.next[i] << " ";
		std::cout << "| " << d.second.in << std::endl;
	}
	for (int i = 0; i < devices["you"].next.size(); i++) {
		std::string key = devices["you"].next[i];
		f.push_back(key);
		devices[key].in += 1;
	}
	while (f.size()) {
		std::string key = f[0];
		if (key == "out") {
			f.erase(f.begin());
			continue ;
		}
		boost::multiprecision::cpp_int ins = devices[key].in;
		for (int i = 0; i < devices[key].next.size(); i++) {
			std::string next = devices[key].next[i];
			f.push_back(next);
			devices[next].in += ins;
		}
		devices[key].in = 0;
		f.erase(f.begin());
	}
	result = devices["out"].in;
	file.close();
	std::cout << result << std::endl;
}

void	part2()
{
	boost::multiprecision::cpp_int	result = 0;
	std::ifstream file("input.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}


	boost::multiprecision::cpp_int		a;
	boost::multiprecision::cpp_int		b;
	std::vector<boost::multiprecision::cpp_int>	nums;
	std::vector<std::vector<boost::multiprecision::cpp_int>>	numbers;
	std::map<std::string, t_device>		devices;
	std::vector<std::string>				f;

	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		t_device d;
		d = get_device(line);
		devices[d.name] = d;
		lines.push_back(line);
	}
	devices["svr"].in = 1;
	for (auto d : devices)
	{
		std::cout << d.second.name << ": ";
		for (int i = 0; i < d.second.next.size(); i++)
			std::cout << d.second.next[i] << " ";
		std::cout << "| " << d.second.in << std::endl;
	}
	for (int i = 0; i < devices["svr"].next.size(); i++) {
		std::string key = devices["svr"].next[i];
		f.push_back(key);
		devices[key].in += 1;
	}
	while (f.size()) {
		std::string key = f[0];
		// std::cout << key << std::endl;
		if (key == "out" || devices[key].in == 0) {
			f.erase(f.begin());
			continue ;
		}
		boost::multiprecision::cpp_int ins = devices[key].in;
		boost::multiprecision::cpp_int ins_d = devices[key].in_d;
		boost::multiprecision::cpp_int ins_f = devices[key].in_f;
		boost::multiprecision::cpp_int ins_df = devices[key].in_df;
		for (int i = 0; i < devices[key].next.size(); i++) {
			std::string next = devices[key].next[i];
			f.push_back(next);
			devices[next].in += ins;
			devices[next].in_f += ins_f;
			devices[next].in_d += ins_d;
			devices[next].in_df += ins_df;
			if (key == "fft") {
				std::cout << "fft: " << ins << " " << ins_f << " " << ins_d << " " << ins_df <<"\n";
				devices[next].in_f = ins - ins_f;
				devices[next].in_df = ins_d - ins_df;
			}
			if (key == "dac") {
				std::cout << "dac: " << ins << " " << ins_f << " " << ins_d << " " << ins_df <<"\n";
				devices[next].in_d = ins - ins_d;
				devices[next].in_df = ins_f - ins_df;
			}
		}
		devices[key].in = 0;
		devices[key].in_d = 0;
		devices[key].in_f = 0;
		devices[key].in_df = 0;
		f.erase(f.begin());
	}
	result = devices["out"].in_df;
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