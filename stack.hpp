#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

/*
**
** TODO:
**
** - Do and recheck constructors (maybe implement copy constructor)
**
*/

namespace ft {
	template <class T, class Container = ft::vector<T> > class stack
	{
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		private:
			container_type _container;

		public:
			stack (); // TODO

			bool empty() const { return _container.empty(); }
			size_type size() const { return _container.size(); }
			value_type& top() { return _container.back(); }
			const value_type& top() const { return _container.back(); }
			void push (const value_type& val) { _container.push_back(val); }
			void pop() { _container.pop_back(); }
	};
	/*
	** Relational operators
	*/
	template <class T, class Container>
  	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container == rhs._container; }
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return !(lhs == rhs); }
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container < rhs._container; }
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container <= rhs._container; }
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container > rhs._container; }
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) { return lhs._container >= rhs._container; }
}

#endif
