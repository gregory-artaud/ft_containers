#include "../../containers/map.hpp"
#include "../../containers/vector.hpp"

#include <map>
#include <iostream>
#include <list>
#include <sys/time.h>
#include <stdlib.h>

#define T1 int
#define T2 std::string
typedef std::pair<T1, T2> T3;

long int	ft_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000000) + (t.tv_usec));
}

void print_time(long int start, long int end, std::string name)
{
	//// std::cout << "start = " << start << "  end = " << end << std::endl;
	std::cout << "Tester " << name << " takes [" << ((float)(end - start)) << "] usec to complete." << std::endl;
}

template <typename T>
std::string	printPair(const T &iterator, bool nl = true, std::ostream &o = std::cout)
{
	o << "key: " << iterator->first << " | value: " << iterator->second;
	if (nl)
		o << std::endl;
	return ("");
}

template <typename T_MAP>
void	printSize(T_MAP const &mp, bool print_content = 1)
{
	std::cout << "size: " << mp.size() << std::endl;
	std::cout << "max_size: " << mp.max_size() << std::endl;
	if (print_content)
	{
		typename T_MAP::const_iterator it = mp.begin(), ite = mp.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << printPair(it, false) << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

int main(void)
{
	long int start = ft_get_time();

	// Test here
	
	print_time(start, ft_get_time(), "sandbox");
	return 0;
}
