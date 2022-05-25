#ifndef BST_ITERATOR_HPP
#define BST_ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft {
    template <typename T, class Compare> class bst_iterator;
    template <typename T, typename V, class Compare> class bst_const_iterator;
    
	template <typename T, class Compare>
        class bst_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
			public:
				typedef typename T::value_type value_type;
                typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

				// Default constructor
				bst_iterator() : _data(NULL) {}

				// Copy constructor
				bst_iterator(const bst_iterator& it) : _data(it._data) {}

                //bst_iterator(const bst_const_iterator<T, Compare>& it) : _data(it.base()) {}

				// Constructor from pointer
				bst_iterator(T* data) : _data(data) {}
                
				// Assignation operator
				bst_iterator& operator=(const bst_iterator& rhs) {
					_data = rhs._data;
					return *this;
				}

				// Destructor
				virtual ~bst_iterator() {}

				// Access operators
				T* base() const { return _data; }
					// Dereference operator
				reference operator*() const { return _data->value; }
					// Arrow operator
				pointer operator->(void) const { return &(_data->value); }

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

                bool operator==(const bst_iterator& bst_it) const
                {
                    return (this->_data == bst_it._data);
                }

                bool operator!=(const bst_iterator& bst_it) const
                {
                    return (this->_data != bst_it._data);
                }
			private:
				T* _data;
        };

	template <typename T, typename V, class Compare>
        class bst_const_iterator : ft::iterator<ft::bidirectional_iterator_tag, T> {
			public:
				typedef V value_type;
                typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::iterator_category iterator_category;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::difference_type difference_type;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::pointer pointer;
				typedef typename ft::iterator<ft::bidirectional_iterator_tag, value_type>::reference reference;

				// Default constructor
				bst_const_iterator() : _data(NULL) {}

				// Copy constructor
				bst_const_iterator(const bst_const_iterator& it) : _data(it._data) {}

				// Constructor from pointer
				bst_const_iterator(T* data) : _data(data) {}

                // Constructor from iterator
                bst_const_iterator(const bst_iterator<T,Compare>& it) : _data(it.base()) {}

				// Assignation operator
				bst_const_iterator& operator=(const bst_const_iterator& rhs) {
                    if (*this == rhs)
                    {
                        return *this;
                    }
					_data = rhs._data;
					return *this;
				}

				// Destructor
				virtual ~bst_const_iterator() {}

				// Access operators
				T* base() const { return _data; }
					// Dereference operator
				reference operator*() const { return _data->value; }
					// Arrow operator
				pointer operator->(void) const { return &(_data->value); }

				// Arithmetic operators
					// Pre-increment operator
				bst_const_iterator& operator++(void)
                {
                    _data = _data->next();
                    return (*this);
                }
					// Post-increment operator
				bst_const_iterator operator++(int)
                {
                    bst_const_iterator ret(*this);
                    operator++();
                    return (ret);
                }
					// Pre-decrement operator
				bst_const_iterator& operator--(void)
                {
                    _data = _data->previous();
                    return (*this);
                }
					// Post-decrement operator
				bst_const_iterator operator--(int)
                {
                    bst_const_iterator ret(*this);
                    operator--();
                    return (ret);
                }

                bool operator==(const bst_const_iterator& bst_it) const
                {
                    return (this->_data == bst_it._data);
                }

                bool operator!=(const bst_const_iterator& bst_it) const
                {
                    return (this->_data != bst_it._data);
                }
			private:
				T* _data;

		};
}
#endif
