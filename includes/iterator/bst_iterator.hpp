#ifndef BST_ITERATOR_HPP
#define BST_ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft {
	template <typename T>
        class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
			public:
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;

				// Default constructor
				bst_iterator() : _data(NULL) {}

				// Copy constructor
				bst_iterator(const bst_iterator& it) : _data(it._data) {}

				// Constructor from pointer
				bst_iterator(pointer data) : _data(data) {}

				// Assignation operator
				bst_iterator& operator=(const bst_iterator& rhs) {
					_data = rhs._data;
					return *this;
				}

				// Destructor
				virtual ~bst_iterator() {}

				// Access operators
				pointer base() const { return _data; }
					// Dereference operator
				reference operator*() const { return *_data; }
					// Arrow operator
				pointer operator->(void) { return &(this->operator*()); }

				// User-defined conversion operator
				operator bst_iterator<const T> () const { return (bst_iterator<const T>(this->_data)); }
				
				// Arithmetic operators
					// Pre-increment operator
				bst_iterator& operator++(void)
                {
                    _data = _data->next();
                    return (*this);
                }
					// Post-increment operator
				bst_iterator operator++(int)
                {
                    bst_iterator ret(*this);
                    operator++();
                    return (ret);
                }
					// Pre-decrement operator
				bst_iterator& operator--(void)
                {
                    _data = _data->previous();
                    return (*this);
                }
					// Post-decrement operator
				bst_iterator operator--(int)
                {
                    bst_iterator ret(*this);
                    operator--();
                    return (ret);
                }

			private:
				pointer _data;

		};

	// Relational operators
	template <typename T>
	bool
		operator==(const ft::bst_iterator<T> lhs, const ft::bst_iterator<T> rhs)
	{
		return (lhs.base() == rhs.base());
	}
	template <typename T1, typename T2>
    bool
		operator==(const ft::bst_iterator<T1> lhs, const ft::bst_iterator<T2> rhs)
    {
        return (lhs.base() == rhs.base());
    }

	template <typename T>
	bool
		operator!=(const ft::bst_iterator<T> lhs, const ft::bst_iterator<T> rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename T1, typename T2>
	bool
		operator!=(const ft::bst_iterator<T1> lhs, const ft::bst_iterator<T2> rhs)
	{
		return (lhs.base() != rhs.base());
	}
}

#endif
