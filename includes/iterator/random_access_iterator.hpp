#ifndef RANDOM_ACCESS_ITERATOR_HPP
#define RANDOM_ACCESS_ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft {
	template <typename T>
        class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T> {
			public:
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
				typedef typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;

				// Default constructor
				random_access_iterator() : _data(NULL) {}

				// Copy constructor
				random_access_iterator(const random_access_iterator& it) : _data(it._data) {}

				// Constructor from pointer
				random_access_iterator(pointer data) : _data(data) {}

				// Assignation operator
				random_access_iterator& operator=(const random_access_iterator& rhs) {
					_data = rhs._data;
					return *this;
				}

				// Destructor
				virtual ~random_access_iterator() {}

				// Access operators
				pointer base() const { return _data; }
					// Dereference operator
				reference operator*() const { return *_data; }
					// Arrow operator
				pointer operator->(void) { return &(this->operator*()); }
					// Index operator
				reference operator[](difference_type n) { return (*(operator+(n))); }

				// User-defined conversion operator
				operator random_access_iterator<const T> () const { return (random_access_iterator<const T>(this->_data)); }
				
				// Arithmetic operators
					// Pre-increment operator
				random_access_iterator& operator++(void)
                {
                    _data++;
                    return (*this);
                }
					// Post-increment operator
				random_access_iterator operator++(int)
                {
                    random_access_iterator ret(*this);
                    operator++();
                    return (ret);
                }
					// Pre-decrement operator
				random_access_iterator& operator--(void)
                {
                    _data--;
                    return (*this);
                }
					// Post-decrement operator
				random_access_iterator operator--(int)
                {
                    random_access_iterator ret(*this);
                    operator--();
                    return (ret);
                }
					// Addition operator
				random_access_iterator operator+(difference_type n) const { return (_data + n); }
					// Subtraction operator
				random_access_iterator operator-(difference_type n) const { return (_data - n); }
					// Addition assignment operator
				random_access_iterator& operator+=(difference_type n)
                {
                    _data += n;
                    return (*this);
                }
					// Subtraction assignment operator
				random_access_iterator& operator-=(difference_type n)
                {
                    _data -= n;
                    return (*this);
                }

			private:
				pointer _data;

		};

	// Relational operators
	template <typename T>
	bool
		operator==(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T1, typename T2>
    bool
		operator==(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
    {
        return (lhs.base() == rhs.base());
    }

	template <typename T>
	bool
		operator!=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T1, typename T2>
	bool
		operator!=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T>
	typename ft::random_access_iterator<T>::difference_type 
		operator-(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <typename T1, typename T2>
	typename ft::random_access_iterator<T1>::difference_type 
		operator-(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <typename T>
	ft::random_access_iterator<T>
		operator+(typename ft::random_access_iterator<T>::difference_type n, const ft::random_access_iterator<T>& it)
	{
		return (it + n);
	}

	template <typename T>
	bool
		operator<(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T>
	bool
		operator<=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T>
	bool
		operator>(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T>
	bool
		operator>=(const ft::random_access_iterator<T> lhs, const ft::random_access_iterator<T> rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename T1, typename T2>
	bool
		operator<(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename T1, typename T2>
	bool
		operator<=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename T1, typename T2>
	bool
		operator>(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename T1, typename T2>
	bool
		operator>=(const ft::random_access_iterator<T1> lhs, const ft::random_access_iterator<T2> rhs)
	{
		return (lhs.base() >= rhs.base());
	}
}

#endif
