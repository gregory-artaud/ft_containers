#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "../includes/iterator/iterator.hpp" // replace with #include "iterator.hpp"
#include "../includes/type_traits/type_traits.hpp" // replace with #include "iterator.hpp"

#define TWO_POWER_N(n) (1 << (n))
#define TWO_POWER_64 TWO_POWER_N(64)

/*
** 
** Documentation: https://www.cplusplus.com/reference/vector/vector/
**
** TODO:
**
** - Recheck deallocation in reserve
** - Finnish resize
** - Implement everything
**
*/

namespace ft {
	template < class T, class Alloc = std::allocator<T> > class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::const_reference const_reference;
			typedef size_t size_type;

			typedef ft::random_access_iterator<value_type> iterator;
			typedef ft::random_access_iterator<const value_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			/*
			** Constructors and Destructor
			*/
			// Default constructor
			vector (const allocator_type& alloc = allocator_type())
			{
				_start = NULL;
				_end = NULL;
				_alloc_edge = NULL;
				_alloc = alloc;
			}

			// Fill constructor
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				_start = NULL;
				_end = NULL;
				_alloc_edge = NULL;
				_alloc = alloc;
				reserve(n);
				for (size_type i = 0; i < n; i++) push_back(val);
			}

			// Range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				_start = NULL;
				_end = NULL;
				_alloc_edge = NULL;
				_alloc = alloc;
				while (first != last)
				{
					push_back(*first);
					++first;
				}
			}

			// Copy constructor
			vector (const vector& x)
			{
				_start = NULL;
				_end = NULL;
				_alloc_edge = NULL;
				_alloc = x._alloc;
				reserve(x.size());
				for (size_type i = 0; i < x.size(); i++) push_back(x[i]);
			}

			// Default destructor
			~vector ()
			{
				clear();
				_alloc.deallocate(_start, capacity());
			}

			vector& operator= (const vector& x)
			{
				if (this != &x)
				{
					clear();
					for (size_type i = 0; i < x.size(); i++) push_back(x[i]);
				}
				return *this;
			}

			/*
			** Iterators 
			*/
			iterator begin() { return _start; }
			const_iterator begin() const { return _start; }
			iterator end() { return ((empty()) ? _start : _end ); }
			const_iterator end() const { return ((empty()) ? _start : _end ); }
			reverse_iterator rbegin() { return reverse_iterator(end()); }
			const_reverse_iterator rbegin() const { return reverse_iterator(end()); }
			reverse_iterator rend() { return reverse_iterator(begin()); }
			const_reverse_iterator rend() const { return reverse_iterator(begin()); }

			/*
			** Capacity
			*/
			size_type size () const { return (_end - _start); }
			size_type capacity () const { return (_alloc_edge - _start); }
			bool empty () const { return (_start == _end); }
			size_type max_size () const { return (allocator_type().max_size()); }
			void reserve (size_type n)
			{
				if (n == capacity()) return;
				if (n > max_size()) throw std::length_error("vector::reserve");
				pointer old_start = _start;
				pointer old_end = _end;

				_start = _alloc.allocate(n);
				_end = _start;
				while (old_start != old_end)
					_alloc.construct(_end++, *(old_start++));
				//if (old_start != NULL) _alloc.deallocate(old_start, capacity());
				_alloc_edge = _start + n;
			}
			void resize (size_type n, value_type val = value_type()) // TODO
			{
				if (n < size())
					for (size_type i = n; i < size(); i++)
						pop_back();
				else if (n > size())
					for (size_type i = size(); i < n; i++)
						;//push_back(val);
				(void)val;
			}

			/*
			** Element access
			*/
			reference operator[] (size_type n) { return *(_start + n); }
			const_reference operator[] (size_type n) const { return *(_start + n); }
			reference at (size_type n); // TODO
			const_reference at (size_type n) const; // TODO
			reference front (); // TODO
			const_reference front () const; // TODO
			reference back (); // TODO
			const_reference back () const; // TODO

			/*
			** Modifiers
			*/
			
			/**
			 * 
			 * @param n Index of the element to be inserted
			 * @param val Value to be inserted
			 * 
			 */
			void assign (size_type n, const value_type& val); // TODO

			/**
			 * 
			 * @param first First element of the range to be inserted
			 * @param last Last element of the range to be inserted
			 * 
			 */
			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last); // TODO

			/**
			 * 
			 * @param n Index of the element to be inserted
			 * @param val Value to be inserted
			 * 
			 * @return Reference to the inserted element
			 */
			iterator insert (iterator position, const value_type& val); // TODO

			/**
			 * 
			 * @param position Position of the element to be inserted
			 * @param n Number of elements to be inserted
			 * @param val Value to be inserted
			 * 
			 */
			void insert (iterator position, size_type n, const value_type& val); // TODO

			/**
			 * 
			 * @param position Position of the element to be inserted
			 * @param first First element of the range to be inserted
			 * @param last Last element of the range to be inserted
			 * 
			 */
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last); // TODO

			iterator erase (iterator position); // TODO
			iterator erase (iterator first, iterator last); // TODO

			void push_back (const value_type& val)
			{
				if (size() == capacity())
					reserve((capacity()) ? capacity() * 2 : 1);
				_alloc.construct(_end++, val);
			}
			void pop_back () { if (size() > 0) _alloc.destroy(_end--); }
			void swap (vector& x); // TODO
			void clear ()
			{
				size_type old_size = size();

				for (size_type i = 0; i < old_size; i++)
					_alloc.destroy(_end-- - i);
			}

			/*
			** Allocator
			*/
			// NB: return a copy of the allocator
			allocator_type get_allocator() const { return allocator_type(_alloc); }

		private:
			pointer _start;
			pointer _end;
			size_type _size;
			pointer _alloc_edge;
			allocator_type _alloc;
	};
	/*
	** Relational operators
	*/
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // TODO
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // TODO
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // TODO
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // TODO
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // TODO
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs); // TODO

	/*
	** Swap
	*/
	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y); // TODO
}

#endif
