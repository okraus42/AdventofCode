#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <set>
#include <algorithm>
#include <climits>
#include <numeric>
#include <unordered_map>


void convertStringToIntegers(const std::string& str, std::vector<unsigned int>& numbers) {
	std::string cleaned = str;
	for (char& c : cleaned)
		if (!isdigit(c)) c = ' ';

	std::stringstream ss(cleaned);
	unsigned int num;
	while (ss >> num) {
		numbers.push_back(num);
	}
}

void convertIntegerToString(const long long num, std::string& str) {
	std::stringstream ss;
	ss << num;
	ss >> str;
}

typedef struct s_machine {
	unsigned int on;
	std::vector<unsigned int>	buttons;
	std::vector<std::vector<unsigned int>>	b;
	std::vector<unsigned int>	joltage;
}	t_machine;

t_machine	get_machine(std::string& str) {
	t_machine machine;
	unsigned int on;
	unsigned int				button;
	std::vector<unsigned int>	buttons;
	std::vector<unsigned int>	joltage;
	std::vector<unsigned int>	numbers;
	std::stringstream ss;
	ss << str;
	std::string word;
	ss >> word;
	word = word.substr(1, word.size() - 2);
	on = 0;
	// std::cout << word << std::endl;
	for (int i = word.size() - 1; i >= 0; --i) {
		char c = word[i];
		on <<= 1;
		if (c != '.')
			on |= 1;
		// std::cout << word << " " << on << std::endl;
	}
	word.clear();
	ss >> word;
	while (word[0] == '(') {
		word = word.substr(1, word.size() - 2);
		numbers.clear();
		convertStringToIntegers(word, numbers);
		machine.b.push_back(numbers);
		button = 0;
		for (unsigned int num : numbers) {
			button |= 1 << num;
		}
		buttons.push_back(button);
		word.clear();
		ss >> word;
	}
	word = word.substr(1, word.size() - 2);
	numbers.clear();
	convertStringToIntegers(word, numbers);
	joltage = numbers;
	machine.on = on;
	machine.buttons = buttons;
	machine.joltage = joltage;
	return machine;
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
	std::vector<long long>	nums;
	std::vector<std::vector<long long>>	numbers;
	std::vector<t_machine>	machines;

	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		t_machine machine = get_machine(line);
		machines.push_back(machine);
	}
	int n = machines.size();
	int m = 0;
	// std::cout << "hello" << std::endl;
	for (int y = 0; y < n; y++) {
		// std::cout << y << ": " << machines[y].on << " | ";
		// m = machines[y].buttons.size();
		// for (int x = 0; x < m; x++)
		// 	std::cout << machines[y].buttons[x] << ", ";
		// std::cout << " | ";
		// m = machines[y].joltage.size();
		// for (int x = 0; x < m; x++)
		// 	std::cout << machines[y].joltage[x] << ", ";
		// std::cout << std::endl;
		unsigned int	goal = machines[y].on;
		std::set<unsigned int>	states;
		std::vector<unsigned int>	round;
		states.insert(0);
		m = machines[y].buttons.size();
		int i = 0;
		for (i = 0; states.find(goal) == states.end(); i++) {
			round.clear();
			for (unsigned int u : states) {
				for (int x = 0; x < m; x++) {
					round.push_back(u ^ machines[y].buttons[x]);
				}
			}
			states.insert(round.begin(), round.end());
			// std::cout << "i" << std::endl;
		}
		result += i;
	}
	file.close();
	std::cout << result << std::endl;
}

#include <z3++.h>
#include <vector>
#include <iostream>

int solve(const std::vector<std::vector<unsigned int>>& b, const std::vector<unsigned int>& target) {
	z3::context ctx;
	z3::optimize opt(ctx);
	int n = (int)b.size();
	int m = (int)target.size();
	std::vector<z3::expr> x;
	for (int i = 0; i < n; i++) {
		x.push_back(ctx.int_const(("x" + std::to_string(i)).c_str()));
		opt.add(x[i] >= 0);
	}
	for (int j = 0; j < m; j++) {
		z3::expr sum = ctx.int_val(0);
		for (int i = 0; i < n; i++) {
			// if b[i] vector has index j
			bool covers = false;
			for (unsigned int idx : b[i]) {
				if (idx == j) {
					covers = true;
					break;
				}
			}
			if (covers)
			{
				sum = sum + x[i];
			}
		}
		opt.add(sum == (int)target[j]);
	}
	z3::expr total = ctx.int_val(0);
	for (int i = 0; i < n; i++) total = total + x[i];
	opt.minimize(total);

	int best = 0;
	if (opt.check() == z3::sat) {
		z3::model mdl = opt.get_model();
		for (int i = 0; i < n; i++) {
			int val = mdl.eval(x[i]).get_numeral_int();
			best += val;
			std::cout << "Vector " << i << ": " << val << "\n";
		}
		std::cout << "Moves: " << best << "\n";
	}
	return best;
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
	std::vector<long long>	nums;
	std::vector<std::vector<long long>>	numbers;
	std::vector<t_machine>	machines;
	int	skip;
	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		t_machine machine = get_machine(line);
		machines.push_back(machine);
	}
	int n = machines.size();
	int m = 0;
	// std::cout << "hello" << std::endl;
	for (int y = 0; y < n; y++) {
		// std::vector<unsigned int>	goal = machines[y].joltage;
		// std::set<std::vector<unsigned int>>	states;
		// std::vector<unsigned int>	jolts;
		// std::vector<std::vector<unsigned int>>	round;
		// for (unsigned int xxx : machines[y].joltage)
		// 	jolts.push_back(0);
		// states.insert(jolts);
		// m = machines[y].buttons.size();
		// int i = 0;
		// for (i = 0; states.find(goal) == states.end(); i++) {
		// 	round.clear();
		// 	for (std::vector<unsigned int> u : states) {
		// 		for (int x = 0; x < m; x++) {
		// 			jolts.clear();
		// 			jolts = u;
		// 			// std::cout << "i" << std::endl;
		// 			for (int w = 0; w < machines[y].b[x].size(); w++)
		// 				jolts[machines[y].b[x][w]] += 1;
		// 			// std::cout << "j" << std::endl;
		// 			skip = 0;
		// 			for (int w = 0; w < goal.size(); w++)
		// 			{
		// 				if (jolts[w] > goal[w])
		// 					skip = 1;
		// 			}
		// 			if (!skip)
		// 				round.push_back(jolts);
		// 		}
		// 	}
		// 	states.insert(round.begin(), round.end());
		// 	std::cout << "i: " << i << std::endl;
		// }
		
		result += solve(machines[y].b, machines[y].joltage);

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