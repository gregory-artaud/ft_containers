#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "../includes/iterator/iterator.hpp" // replace with #include "iterator.hpp"
#include "../includes/type_traits/type_traits.hpp" // replace with #include "iterator.hpp"
#include "../includes/algorithm/algorithm.hpp" // replace with #include "algorithm.hpp"

/*
** 
** Documentation: https://www.cplusplus.com/reference/vector/vector/
**
** TODO:
**
** - Recheck execution time and complexity of insert
** - Recheck execution time and complexity of assign
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
			vector (size_type n, const value_type& val = value_type(),
                    const allocator_type& alloc = allocator_type())
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
			vector (InputIterator first, InputIterator last,
                    const allocator_type& alloc = allocator_type(),
				typename ft::enable_if
                    <!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				_start = NULL;
				_end = NULL;
				_alloc_edge = NULL;
				_alloc = alloc;
				while (first != last) push_back(*(first++));
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
				if (n <= capacity()) return;
				if (n > max_size()) throw std::length_error("vector::reserve");

				pointer old_start = _start;
				pointer old_end = _end;
				size_type old_size = size();
				size_type old_capacity = capacity();

				_start = _alloc.allocate(n);
				_alloc_edge = _start + n;
				_end = _start;
				while (old_start != old_end)
				{
					_alloc.construct(_end++, *(old_start++));
				}
				if (old_start != NULL)
				{
					_alloc.deallocate(old_start - old_size, old_capacity);
				}
			}
			void resize (size_type n, value_type val = value_type())
			{
				if (n > max_size()) throw std::length_error("vector::resize");
				else if (n < size())
				{
					while (n < size())
					{
						pop_back();
					}
				}
				else if (n > size())
				{
					insert(end(), n - size(), val);
				}
			}

			/*
			** Element access
			*/
			reference operator[] (size_type n) { return *(_start + n); }
			const_reference operator[] (size_type n) const { return *(_start + n); }
			reference at (size_type n)
			{
				checkBounds(n);
				return *(_start + n);
			}
			const_reference at (size_type n) const
			{
				checkBounds(n);
				return *(_start + n);
			}
			reference front () { return *_start; }
			const_reference front () const { return *_start; }
			reference back () { return *(_end - 1); }
			const_reference back () const { return *(_end - 1); }

			/*
			** Modifiers
			*/
			
			void assign (size_type n, const value_type& val)
			{
				clear();
				if (n == 0) return;
				reserve(n);
				for (size_type i = 0; i < n; i++) 
				{
					push_back(val);
				}
			}

			template <class InputIterator>
  			void assign (InputIterator first, InputIterator last,
				typename ft::enable_if
                    <!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				size_type n = ft::distance(first, last);

				clear();
				if (n == 0) return;
				reserve(n);
				for (size_type i = 0; i < n; i++) 
				{
					push_back(*(first++));
				}
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type index = &(*position) - _start;

				if (position == end())
				{
					push_back(val);
				}
				else
				{
					checkSize();
					for (size_type i = size(); i > index; i--)
					{
						_alloc.construct(_start + i, *(_start + i - 1));
						_alloc.destroy(_start + i - 1);
					}
					_alloc.construct(_start + index, val);
					_end++;
				}
				return iterator(_start + index);
			}

			void insert (iterator position, size_type n, const value_type& val) 
			{
				for (size_type i = 0; i < n; i++)
				{
					position = insert(position, val);
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if
                    <!ft::is_integral<InputIterator>::value, InputIterator>::type* = NULL)
			{
				while (first != last)
				{
					position = insert(position, *(--last));
				}
			}

			iterator erase (iterator position)
			{
				size_type index = &(*position) - _start;

				if (position == end())
				{
					pop_back();
				}
				else
				{
					for (size_type i = index; i < size() - 1; i++)
					{
						_alloc.destroy(_start + i);
						_alloc.construct(_start + i, _start[i + 1]);
					}
					_end--;
				}
				return iterator(_start + index);
			}
			iterator erase (iterator first, iterator last)
			{
				size_type last_index = &(*last) - _start;
				size_type first_index = &(*first) - _start;
				while (first_index != last_index)
				{
					first = erase(first);
					first_index++;
				}
				return first;
			}

			void push_back (const value_type& val)
			{
				checkSize();
				_alloc.construct(_end++, val);
			}
			void pop_back () { if (size() > 0) _alloc.destroy(--_end); }
			void swap (vector& x)
			{
				pointer tmp;

				tmp = _start;
				_start = x._start;
				x._start = tmp;

				tmp = _end;
				_end = x._end;
				x._end = tmp;

				tmp = _alloc_edge;
				_alloc_edge = x._alloc_edge;
				x._alloc_edge = tmp;
			}
			void clear ()
			{
				size_type old_size = size();

				for (size_type i = 0; i < old_size; i++)
					pop_back();
			}

			/*
			** Allocator
			*/
			// NB: return a copy of the allocator
			allocator_type get_allocator() const { return allocator_type(_alloc); }

		private:
			pointer _start;
			pointer _end;
			pointer _alloc_edge;
			allocator_type _alloc;

			void checkSize(void)
			{
				size_type size = this->size();

				if (size == capacity())
				{
					reserve((size) ? size * 2 : 1);
				}
			}

			void checkBounds(size_type n) const
			{
				if ((n >= size()) || (n < 0))
				{
					throw std::out_of_range("vector::at");
				}
			}
	};
	/*
	** Relational operators
	*/
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size()) return false;
		for (size_t i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i]) return false;
		return true;
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }
	template <class T, class Alloc>
	bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }
	template <class T, class Alloc>
	bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return rhs < lhs;
    }
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }

	/*
	** Swap
	*/
	template <class T, class Alloc>
  	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) { x.swap(y); }
}

#endif
