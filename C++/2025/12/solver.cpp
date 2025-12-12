#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>
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

typedef struct s_shape {
	int	id;
	int	s;
	int	a[3][3];
	bool operator<(const s_shape& other) const {
		if (s != other.s)
			return s < other.s;
		return id < other.id;
	}
}	t_shape;

void	part1()
{
	long long	result = 0;
	std::ifstream file("test.txt");
	// Check if the file is open
	if (!file.is_open()) {
		std::cerr << "Could not open the file!" << std::endl;
		return ;
	}

	std::vector<t_shape>	shapes;
	int						vars[6];
	int						start[6];
	int						end[6];
	int						size[6];
	// Read the file line by line
	std::vector<std::string> lines;
	std::string			line;
	// Read the file line by line
	while (std::getline(file, line)) {
		// std::cout << line << std::endl;  // Print each line to the console
		lines.push_back(line);
	}
	int n = lines.size();
	for (int i = 0; i < 6; i++) {
		std::set<t_shape>	uniq;
		t_shape shape;
		t_shape shape2;
		t_shape shapeF;
		t_shape shapeF2;
		shape.s = 0;
		shape.id = i + 1;
		size[i] = 0;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				shape.a[j][k] = (lines[(i * 5 + 1 + j)][k] == '#');
				size[i] += (lines[(i * 5 + 1 + j)][k] == '#');
				shape.s |= (lines[(i * 5 + 1 + j)][k] == '#') << (j * 3 + k);
			}
		}
		uniq.insert(shape);
		shapeF.s = 0;
		shapeF.id = i + 1;
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				shapeF.a[j][k] = shape.a[j][3 - k - 1];
				shapeF.s |= shapeF.a[j][k] << (j * 3 + k);
			}
		}
		uniq.insert(shapeF);
		for (int r = 0; r < 4; r++) {
			shape2.s = 0;
			shape2.id = i + 1;
			shapeF2.s = 0;
			shapeF2.id = i + 1;
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					shape2.a[j][k] = shape.a[3 - k - 1][j];
					shape2.s |= shape2.a[j][k] << (j * 3 + k);
					shapeF2.a[j][k] = shapeF.a[3 - k - 1][j];
					shapeF2.s |= shapeF2.a[j][k] << (j * 3 + k);
				}
			}
			uniq.insert(shape2);
			uniq.insert(shapeF2);
			shape = shape2;
			shapeF = shapeF2;
		}
		vars[i] = uniq.size();
		start[i] = shapes.size();
		end[i] = start[i] + vars[i];
		shapes.insert(shapes.end(), uniq.begin(), uniq.end());
		// std::cout << shape.id << ": " << shape.s << " " << vars[i] << std::endl;
		// for (auto s : uniq) {
		// 	std::cout << s.s << std::endl;
		// 	std::cout << s.a[0][0] << s.a[0][1] << s.a[0][2] << std::endl;
		// 	std::cout << s.a[1][0] << s.a[1][1] << s.a[1][2] << std::endl;
		// 	std::cout << s.a[2][0] << s.a[2][1] << s.a[2][2] << std::endl;
		// }
		shapes.push_back(shape);
	}
	for (int l = 30; l < n; l++) {
		// std::cout << lines[l] << std::endl;
		std::vector<long long> numbers;
		convertStringToIntegers(lines[l], numbers);
		int counts[6];
		int maX = numbers[0];
		int maY = numbers[1];
		for (int i = 0; i < 6; i++)
			counts[i] = numbers[i + 2];
		// std::cout << maX << "x" << maY << ": ";
		// for (int i = 0; i < 6; i++)
		// 	std::cout << counts[i] << " ";
		// std::cout << std::endl;
		int area = 0;
		for (int i = 0; i < 6; i++)
			area += counts[i] * size[i];
		if (area < maX * maY)
			++result;
	}
	file.close();
	std::cout << result << std::endl;
}

void	part2()
{
	long long	result = 0;
	
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