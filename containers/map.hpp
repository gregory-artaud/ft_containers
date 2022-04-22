#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "../includes/data_structure/data_structure.hpp"
#include "../includes/functional/functional.hpp"
#include "../includes/utility/utility.hpp"

/*
** 
** Documentation: https://www.cplusplus.com/reference/map/map/
**
** TODO:
**
** - Finish roadmap
** - Implement everything
**
*/

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>,
         class Alloc = std::allocator<ft::pair<const Key,T> > > class map
	{
		typedef Key key_type;
		typedef T mapped_type;
		typedef std::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		// typedef [...] value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef size_t size_type;
		
		// iterators and const_iterators
		// TODO

		private:
			allocator_type _alloc;
		
		public:
			// Constructors and Destructor
			map (); // TODO
			~map (); // TODO

			/*
			** Iterators
			*/

			/*
			** Capacity
			*/

			/*
			** Element access
			*/

			/*
			** Modifiers
			*/

			/*
			** Observers
			*/

			/*
			** Operations
			*/

			/*
			** Allocator
			*/
			// NB: return a copy of the allocator
			allocator_type get_allocator() const { return allocator_type(_alloc); }
	};
}

#endif
