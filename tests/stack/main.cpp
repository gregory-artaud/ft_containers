#include <iostream>
#include "stack.hpp"
#include <stack>

bool equal(const ft::stack<int>& lhs, const std::stack<int>& rhs) {
	(void)lhs;
	(void)rhs;
	return false;
}

int main(void) {
	// Nombre de tests echoués
	// Il faut le maintenir a 0
	int result = 0;

#define TEST(x) (if (!x) result++)

	// Test constructors
	std::cout << "Result: " << result << std::endl;
	return 0;
}
