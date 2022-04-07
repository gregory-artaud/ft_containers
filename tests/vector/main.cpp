#include <iostream>
#include "vector.hpp"
#include <vector>

#define COMPARE(x, y)										 \
	printVectorData(x);										\
	printVectorData(y);

#define TEST(name, x)										 \
	std::cout << "\tTest " << name << ": ";					\
	if (!x)													\
	{														\
		result++; 											\
		std::cout << "KO " << result << std::endl;			\
		COMPARE(my_v, std_v)								\
	}														\
	else													\
		std::cout << "OK" << std::endl;


bool equal(const ft::vector<int>& lhs, const std::vector<int>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	if (lhs.max_size() != rhs.max_size()) return false;
	if (lhs.capacity() != rhs.capacity()) return false;
	for (size_t i = 0; i < lhs.size(); ++i) if (lhs[i] != rhs[i]) return false;

	return true;
}

void printVectorData(const ft::vector<int>& v) {
	std::cout << std::endl;
	std::cout << "\t\tsize: " << v.size() << std::endl;
	std::cout << "\t\tmax_size: " << v.max_size() << std::endl;
	std::cout << "\t\tcapacity: " << v.capacity() << std::endl;
}

void printVectorData(const std::vector<int>& v) {
	std::cout << std::endl;
	std::cout << "\t\tsize: " << v.size() << std::endl;
	std::cout << "\t\tmax_size: " << v.max_size() << std::endl;
	std::cout << "\t\tcapacity: " << v.capacity() << std::endl;
}



int main(void) {
	// Nombre de tests echoués
	// Il faut le maintenir a 0
	int result = 0;


	// Test constructors
	{
		std::cout << "Test constructors" << std::endl;

		// Test default constructor
		{
			ft::vector<int> my_v;
			std::vector<int> std_v;

			TEST("default constructor #1", equal(my_v, std_v))
		}

		// Test fill constructor
		// #1
		{
			ft::vector<int> my_v(0);
			std::vector<int> std_v(0);

			TEST("fill constructor #1", equal(my_v, std_v))
		}
		// #2
		{
			ft::vector<int> my_v(10, 0);
			std::vector<int> std_v(10, 0);

			TEST("fill constructor #2", equal(my_v, std_v))
		}
		// Test size and value constructor
	}

	std::cout << "Result: " << result << std::endl;
	return 0;
}
