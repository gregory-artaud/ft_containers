#include <iostream>
#include <string>
#include <exception>

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

typedef LIB::vector<int>* (*testFunction)(void);

void printVectorData(const LIB::vector<int>& v) {
	std::cout << "\t\t\tsize: " << v.size() << std::endl;
	std::cout << "\t\t\tmax_size: " << v.max_size() << std::endl;
	std::cout << "\t\t\tcapacity: " << v.capacity() << std::endl;
	std::cout << "\t\t\tcontent: ";
	for (size_t i = 0; i < v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

void test(const std::string testName, testFunction getTestedVector) {
	LIB::vector<int>* v;

	std::cout << testName << std::endl;
	v = NULL;
	try {
		v = getTestedVector();
	} catch (std::exception& e) {
		std::cout << "\t\t\t" << e.what() << std::endl;
	}
	printVectorData(*v);
	delete v;
}

LIB::vector<int>* test_default_constructor() { return new LIB::vector<int>(); }

LIB::vector<int>* test_fill_constructor_1() { return new LIB::vector<int>(0); }
LIB::vector<int>* test_fill_constructor_2() { return new LIB::vector<int>(1); }
LIB::vector<int>* test_fill_constructor_3() { return new LIB::vector<int>(10); }
LIB::vector<int>* test_fill_constructor_4() { return new LIB::vector<int>((size_t)10, 0); }
LIB::vector<int>* test_fill_constructor_5() { return new LIB::vector<int>((size_t)10, 1); }
LIB::vector<int>* test_fill_constructor_6() { return new LIB::vector<int>((size_t)10, 10); }
LIB::vector<int>* test_fill_constructor_7() { return new LIB::vector<int>((size_t)10, -10); }
LIB::vector<int>* test_fill_constructor_8() { return new LIB::vector<int>((size_t)0, -10); }

LIB::vector<int>* test_copy_constructor_1() { LIB::vector<int> v; return new LIB::vector<int>(v); }
LIB::vector<int>* test_copy_constructor_2() { LIB::vector<int> v(1); return new LIB::vector<int>(v); }
LIB::vector<int>* test_copy_constructor_3() { LIB::vector<int> v(10); return new LIB::vector<int>(v); }
LIB::vector<int>* test_copy_constructor_4() { LIB::vector<int> v((size_t)10, -10); return new LIB::vector<int>(v); }

int main(void) {
	//std::cout << "Testing library: " << LIB_STR << std::endl;

	std::cout << "Testing vector" << std::endl;
	std::cout << "\tTest constructors" << std::endl;

	test("\t\tTest default constructor #1", test_default_constructor);

	test("\t\tTest fill constructor #1", test_fill_constructor_1);
	test("\t\tTest fill constructor #2", test_fill_constructor_2);
	test("\t\tTest fill constructor #3", test_fill_constructor_3);
	test("\t\tTest fill constructor #4", test_fill_constructor_4);
	test("\t\tTest fill constructor #5", test_fill_constructor_5);
	test("\t\tTest fill constructor #6", test_fill_constructor_6);
	test("\t\tTest fill constructor #7", test_fill_constructor_7);
	test("\t\tTest fill constructor #8", test_fill_constructor_8);
	
	test("\t\tTest copy constructor #1", test_copy_constructor_1);
	test("\t\tTest copy constructor #2", test_copy_constructor_2);
	test("\t\tTest copy constructor #3", test_copy_constructor_3);
	test("\t\tTest copy constructor #4", test_copy_constructor_4);
	return 0;
}
