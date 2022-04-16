#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

/*
** 
** Documentation: https://www.cplusplus.com/reference/stack/stack/
**
** TODO:
**
** - Do and recheck constructors (maybe implement copy constructor)
**
*/

namespace ft {
	template <class T, class Container = ft::vector<T> > class stack
	{
		public:
			typedef T value_type;
			typedef Container container_type;
			typedef size_t size_type;

			stack (const container_type& ctnr = container_type()) // TODO
			{
				_container = ctnr;
			}

			bool empty() const { return _container.empty(); }
			size_type size() const { return _container.size(); }
			value_type& top() { return _container.back(); }
			const value_type& top() const { return _container.back(); }
			void push (const value_type& val) { _container.push_back(val); }
			void pop() { _container.pop_back(); }

			template <class Tp, class Ctnr>
  			friend bool operator== (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);
			template <class Tp, class Ctnr>
  			friend bool operator!= (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);
			template <class Tp, class Ctnr>
  			friend bool operator< (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);
			template <class Tp, class Ctnr>
  			friend bool operator<= (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);
			template <class Tp, class Ctnr>
  			friend bool operator> (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);
			template <class Tp, class Ctnr>
  			friend bool operator>= (const stack<Tp,Ctnr>& lhs, const stack<Tp,Ctnr>& rhs);

		protected:
			container_type _container;
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
