#include <iostream>
#include "vector.hpp"
#include <vector>

bool equal(const ft::vector<int>& lhs, const std::vector<int>& rhs) {
	if (lhs.size() != rhs.size()) return false;
	if (lhs.max_size() != rhs.max_size()) return false;
	if (lhs.capacity() != rhs.capacity()) return false;
	for (size_t i = 0; i < lhs.size(); ++i) if (lhs[i] != rhs[i]) return false;

	return true;
}

void printVectorData(const ft::vector<int>& v) {
	std::cout << "size: " << v.size() << std::endl;
	std::cout << "max_size: " << v.max_size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
}

void printVectorData(const std::vector<int>& v) {
	std::cout << "size: " << v.size() << std::endl;
	std::cout << "max_size: " << v.max_size() << std::endl;
	std::cout << "capacity: " << v.capacity() << std::endl;
}

int main(void) {
	// Nombre de tests echoués
	// Il faut le maintenir a 0
	int result = 0;

#define TEST(x) if (!x) result++;

	// Test constructors
	ft::vector<int> mv1;
	std::vector<int> sv1;

	std::cout << "Test constructors" << std::endl;
	TEST(equal(mv1, sv1))
	
	std::cout << "Result: " << result << std::endl;
	return 0;
}
