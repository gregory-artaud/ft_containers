#include <iostream>

#ifdef stl
 #include <vector>
 #include <stack>
 #include <map>
 #define LIB std
 #define LIB_STR "std"
#else
 #include "vector.hpp"
 #include "stack.hpp"
 #include "map.hpp"
 #define LIB ft
 #define LIB_STR "ft"
#endif

void printVectorData(const LIB::vector<int>& v) {
	std::cout << std::endl;
	std::cout << "\t\t\tsize: " << v.size() << std::endl;
	std::cout << "\t\t\tmax_size: " << v.max_size() << std::endl;
	std::cout << "\t\t\tcapacity: " << v.capacity() << std::endl;
	std::cout << "\t\t\tcontent: ";
	for (size_t i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

int main(void) {
	//std::cout << "Testing library: " << LIB_STR << std::endl;

	// Test vector
	std::cout << "Testing vector" << std::endl;
	// Test constructors
	{
		std::cout << "\tTest constructors" << std::endl;

		// Test default constructor
		{
			std::cout << "\t\tTest default constructor" << std::endl;
			LIB::vector<int> v;

			printVectorData(v);
		}

		// Test fill constructor
		// #1
		{
			std::cout << "\t\tTest fill constructor #1" << std::endl;
			LIB::vector<int> v(0);

			printVectorData(v);
		}
		// #2 Error here : the range constructor is called and idk why
		{
			std::cout << "\t\tTest fill constructor #2" << std::endl;
			LIB::vector<int> v((size_t)10, 0);

			printVectorData(v);
		}
	}
	return 0;
}
