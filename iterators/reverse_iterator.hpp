#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

#include "iterators_traits.hpp"

namespace ft {
	template <class Iterator> class reverse_iterator {
		public:
			typedef Iterator iterator_type;
			typedef typename ft::iterator_traits<iterator_type>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<iterator_type>::value_type value_type;
			typedef typename ft::iterator_traits<iterator_type>::difference_type difference_type;
			typedef typename ft::iterator_traits<iterator_type>::pointer pointer;
			typedef typename ft::iterator_traits<iterator_type>::reference reference;

			// Default constructor
			reverse_iterator () : _it(NULL) {}

			// Initializing constructor
			reverse_iterator (iterator_type it) : _it(it) {}

			// Copy constructor
			template <class Iter> reverse_iterator (const reverse_iterator<Iter>& rev_it) : _it(rev_it._it) {};

			/*
			** Base function
			** Returns the internal iterator
			*/ 
			iterator_type base() const { return _it; }

			// Operators
				// Access operators
					// Dereference operator
			reference operator*() const { return *(--_it); }
					// Arrow operator
			pointer operator->(void) const { return &(this->operator*()); }
					// Index operator
			reference operator[](difference_type n) const { return (this->base()[-n - 1]); }
				
				// Arithmetic operators
					// Pre-increment operator
			reverse_iterator& operator++(void) {
				--_it;
				return (*this);
			}
					// Post-increment operator
			reverse_iterator operator++(int) {
				reverse_iterator ret(*this);
				operator++();
				return (ret);
			}
					// Pre-decrement operator
			reverse_iterator& operator--(void) {
				++_it;
				return (*this);
			}
					// Post-decrement operator
			reverse_iterator operator--(int) {
				reverse_iterator ret(*this);
				operator--();
				return (ret);
			}
					// Addition operator
			reverse_iterator operator+(difference_type n) const { return (reverse_iterator(_it - n)); }
					// Subtraction operator
			reverse_iterator operator-(difference_type n) const { return (reverse_iterator(_it + n)); }
					// Addition assignment operator
	        reverse_iterator& operator+= (difference_type n)
            {
                _it -= n;
                return (*this);
            }
					// Subtraction assignment operator
	        reverse_iterator& operator-= (difference_type n)
			{
				_it += n;
				return (*this);
			}		
			

		private:
			iterator_type _it;
	};

	// Relational operators
	template <class Iterator> bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }
	template <class Iterator> bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return lhs.base() != rhs.base(); }
	template <class Iterator> bool operator< (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }
	template <class Iterator> bool operator> (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }
	template <class Iterator> bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }
	template <class Iterator> bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

	// Operator overloads
	template <class Iterator> reverse_iterator<Iterator> operator+ (const reverse_iterator<Iterator>& lhs, typename reverse_iterator<Iterator>::difference_type n) { return (lhs + n); }
	template <class Iterator> typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }
}

#endif
