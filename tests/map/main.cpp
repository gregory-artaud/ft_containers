#include <iostream>
#include "map.hpp"
#include <map>

/* bool equal(const ft::map<int>& lhs, const std::map<int>& rhs) {
	// TODO
	return false;
} */

int main(void) {
	// Nombre de tests echoués
	// Il faut le maintenir a 0
	int result = 0;

#define TEST(x) (if (!x) result++)

	// Test constructors
	// TODO

	std::cout << "Result: " << result << std::endl;
	return 0;
}
