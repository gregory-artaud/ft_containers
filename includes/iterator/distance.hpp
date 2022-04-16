#ifndef DISTANCE_HPP
#define DISTANCE_HPP

#include "iterators_traits.hpp"

namespace ft {
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
		distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type n = 0;

		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}
}

#endif