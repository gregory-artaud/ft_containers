#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

#define TWO_POWER_N(n) (1 << (n))
#define TWO_POWER_64 TWO_POWER_N(64)

/*
**
** TODO:
**
** - Recheck iterators (maybe implement random access iterator)
** - Recheck constructors (maybe implement copy constructor)
** - Recheck if operators are neeeded (maybe add them)
**
*/

namespace ft {
	template < class T, class Alloc = std::allocator<T> > class vector
	{
		typedef T value_type;
		typedef allocator<T> allocator_type;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_pointer const_pointer;
		typedef allocator_type::const_reference const_reference;
		typedef size_t size_type;

		// iterators and const_iterators
		typedef pointer iterator;
		typedef const_pointer const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;

		private:
			T* _data;
			size_type _size;
			size_type _capacity;
			Alloc _alloc;

		public:
			// constructors and destructor (recheck on https://www.cplusplus.com/reference/vector/vector/ needed)
			vector (); // TODO
			~vector (); // TODO

			vector& operator= (const vector& x); // TODO

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
			size_type max_size () const { return (TWO_POWER_64) / sizeof(value_type) - 1; }
			void resize (size_type n, value_type val = value_type()); // TODO
			void reserve (size_type n); // TODO

			/*
			** Element access
			*/
			reference operator[] (size_type n); // TODO
			const_reference operator[] (size_type n) const; // TODO
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

			void push_back (const value_type& val); // TODO
			void pop_back (); // TODO
			void swap (vector& x); // TODO
			void clear(); // TODO

			/*
			** Allocator
			*/
			allocator_type get_allocator() const { return _alloc; }
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
