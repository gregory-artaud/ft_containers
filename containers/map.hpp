#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include "../includes/data_structure/data_structure.hpp"
#include "../includes/functional/functional.hpp"
#include "../includes/utility/utility.hpp"
#include "../includes/iterator/bst_iterator.hpp"

/*
** 
** Documentation: https://www.cplusplus.com/reference/map/map/
**
** TODO:
**
** - Recheck roadmap
** - Do BinarySearchTree
** - Implement everything
**
*/

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>,
         class Alloc = std::allocator<ft::pair<const Key,T> > > class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<const key_type, mapped_type> value_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			
			// iterators and const_iterators
			typedef ft::bst_iterator<typename ft::BinarySearchTree<value_type, Compare, Alloc>::node_type> iterator;
			typedef ft::bst_iterator<const typename ft::BinarySearchTree<value_type, Compare, Alloc>::node_type> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;

			class value_compare
			{
				friend class map;
				protected:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

		private:
			ft::BinarySearchTree<value_type, Compare, Alloc> _tree;
			allocator_type _alloc;
			key_compare _compare;
		
		public:
			// Constructors and Destructor
			map(const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type()); // TODO

            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type()); // TODO
            
            map(const map& x); // TODO

			~map(); // TODO

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
            bool empty() const; // TODO
            size_type max_size() const
            {
                return allocator_type().max_size(); 
            }
            size_type size() const; // TODO

			/*
			** Element access
			*/
            iterator lower_bound(const key_type& k); // TODO
            const_iterator lower_bound(const key_type& k) const; // TODO
            iterator upper_bound(const key_type& k); // TODO
            const_iterator upper_bound(const key_type& k) const; // TODO
            mapped_type& operator[](const key_type& k); // TODO

			/*
			** Modifiers
			*/
            void erase(iterator position); // TODO
            size_type erase(const key_type& k); // TODO
            void erase(iterator first, iterator last); // TODO
            void clear(); // TODO
            ft::pair<iterator,bool> insert(const value_type& val); // TODO
            iterator insert(iterator position, const value_type& val); // TODO
            template <class InputIterator>
            void insert(InputIterator first, InputIterator last); // TODO

			/*
			** Observers
			*/
            size_type count(const key_type& k) const; // TODO
            ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const; // TODO
            ft::pair<iterator,iterator> equal_range(const key_type& k); // TODO
            iterator find(const key_type& k); // TODO
            const_iterator find(const key_type& k) const; // TODO

			/*
			** Operations
			*/
            map& operator=(const map& x); // TODO
            void swap(map& x); // TODO

			/*
			** Allocator and Compare
			*/
			// NB: return a copy of the allocator
			allocator_type get_allocator() const
            {
                return allocator_type(_alloc);
            }
            key_compare key_comp() const; // TODO
			value_compare value_comp() const
			{
				return value_compare(_compare);
			}
	};

    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
    {
        x.swap(y);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key,T,Compare,Alloc>& lhs,
        const map<Key,T,Compare,Alloc>& rhs)
    {
        if (lhs.size() != rhs.size()) return false;
        return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(),
            rhs.begin(), rhs.end());
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs)
    {
        return rhs < lhs;
    }

    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key,T,Compare,Alloc>& lhs,
                const map<Key,T,Compare,Alloc>& rhs)
    {
        return !(lhs < rhs);
    }
}

#endif
