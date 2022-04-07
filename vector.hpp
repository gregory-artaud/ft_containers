#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include "iterators.hpp"

#define TWO_POWER_N(n) (1 << (n))
#define TWO_POWER_64 TWO_POWER_N(64)

/*
** 
** Documentation: https://www.cplusplus.com/reference/vector/vector/
**
** TODO:
**
** - Recheck iterators (maybe implement random access iterator)
** - Recheck if operators are neeeded (maybe add them)
** - Implement everything
**
*/

namespace ft {
	template < class T, class Alloc = std::allocator<T> > class vector
	{
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::const_reference const_reference;
		typedef size_t size_type;

		// iterators and const_iterators
		typedef pointer iterator;
		typedef const_pointer const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			T* _data;
			size_type _size;
			size_type _capacity;
			allocator_type _alloc;

		public:
			/*
			** Constructors and Destructor
			*/
			// Default constructor
			vector (const allocator_type& alloc = allocator_type())
			{
				_data = nullptr;
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
			}

			// Fill constructor
			vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
			{
				_data = nullptr;
				_size = 0;
				_capacity = 0;
				_alloc = alloc;
				(void)n;
				(void)val;
				//for (size_type i = 0; i < n; i++) _alloc.construct(_data + i, val);
			}

			// Range constructor
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) // TODO
			{
				(void)first;
				(void)last;
				(void)alloc;
			} 

			// Copy constructor
			vector (const vector& x) // TODO
			{
				(void)x;
			}

			// Default destructor
			~vector ()
			{
				if (_data)
				{
					for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
				}
			}

			vector& operator= (const vector& x)
			{
				for (size_type i = 0; i < _size; i++)
						_alloc.destroy(_data + i);
					_alloc.deallocate(_data, _capacity);
				reserve(x._capacity);
				for (size_type i = 0; i < x._size; i++)
					_alloc.construct(_data + i, x._data[i]);
				_size = x._size;
				return *this;
			}

			/*
			** Iterators 
			*/
			iterator begin(); // TODO
			const_iterator begin() const; // TODO
			iterator end(); // TODO
			const_iterator end() const; // TODO
			reverse_iterator rbegin(); // TODO
			const_reverse_iterator rbegin() const; // TODO
			reverse_iterator rend(); // TODO
			const_reverse_iterator rend() const; // TODO

			/*
			** Capacity
			*/
			size_type size () const { return _size; }
			size_type capacity () const { return _capacity; }
			bool empty () const { return _size == 0; }
			size_type max_size () const { return (4611686018427387903); } // replace by formula : TWO_POWER_64 / sizeof(value_type) - 1
			void resize (size_type n, value_type val = value_type()); // TODO
			void reserve (size_type n)
			{
				if (n < _capacity) return;
				pointer tmp = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(tmp + i, _data[i]);
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(_data + i);
				_alloc.deallocate(_data, _capacity);
				_capacity = n;
				_data = tmp;
			}

			/*
			** Element access
			*/
			reference operator[] (size_type n)
			{
				return _data[n];
			}

			const_reference operator[] (size_type n) const
			{
				return _data[n];
			}
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
				if (_size == _capacity)
					reserve(_capacity * 2);
				_alloc.construct(_data + _size, val);
				_size++;
			}
			void pop_back (); // TODO
			void swap (vector& x); // TODO
			void clear(); // TODO

			/*
			** Allocator
			*/
			// NB: return a copy of the allocator
			allocator_type get_allocator() const { return allocator_type(_alloc); }
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
