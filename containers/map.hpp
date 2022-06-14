#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <limits>
#include "../includes/data_structure/data_structure.hpp"
#include "../includes/functional/functional.hpp"
#include "../includes/utility/utility.hpp"
#include "../includes/iterator/bst_iterator.hpp"
#include "../includes/algorithm/algorithm.hpp"

/*
** 
** Documentation: https://www.cplusplus.com/reference/map/map/
**
*/

namespace ft {
	template < class Key, class T, class Compare = ft::less<Key>,
         class Alloc = std::allocator<ft::pair<const Key,T> > > class map
	{
		public:
			typedef Key key_type;
			typedef T mapped_type;
			typedef ft::pair<key_type, mapped_type> value_type;
            typedef typename ft::BinarySearchTree<value_type, Compare>::node_type node_type;
			typedef Compare key_compare;
			typedef Alloc allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			
			// iterators and const_iterators
			typedef typename ft::BinarySearchTree<value_type, Compare>::iterator iterator;
			typedef typename ft::BinarySearchTree<value_type, Compare>::const_iterator const_iterator;
			typedef typename ft::BinarySearchTree<value_type, Compare>::reverse_iterator reverse_iterator;
			typedef typename ft::BinarySearchTree<value_type, Compare>::const_reverse_iterator const_reverse_iterator;

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
			ft::BinarySearchTree<value_type, Compare> _tree;
			allocator_type _alloc;
			key_compare _comp;
		
		public:
			// Constructors and Destructor
			map(const key_compare& comp = key_compare(),
                const allocator_type& alloc = allocator_type())
            {
                _alloc = alloc;
                _comp = comp;
            }

            template <class InputIterator>
            map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
                    const allocator_type& alloc = allocator_type())
            {
                _alloc = alloc;
                _comp = comp;
                insert(first, last);
            }
            
            map(const map& x)
            {
                _alloc = x.get_allocator();
                _comp = x.key_comp();
                insert(x.begin(), x.end());
            }

			~map()
            {
                clear();
            }

			/*
			** Iterators
			*/
            iterator begin()
			{
				return _tree.begin();
			}
            const_iterator begin() const
			{
				return _tree.begin();
			}
            iterator end()
			{
				return _tree.end();
			}
            const_iterator end() const
			{
				return _tree.end();
			}
			reverse_iterator rbegin()
			{
				return _tree.rbegin();
			}
			const_reverse_iterator rbegin() const
			{
				return _tree.rbegin();
			}
			reverse_iterator rend()
			{
				return _tree.rend();
			}
			const_reverse_iterator rend() const
			{
				return _tree.rend();
			}

			/*
			** Capacity
			*/
            bool empty() const
			{
				return (size() == 0);
			}
			/*
			** Result may vary from STL map due to Node implementation, which has an impact on sizeof(node_type)
			** In those variations, STL has a 	sizeof(node_type) = 40
			** mine has a 						sizeof(node_type) = 48
			*/
            size_type max_size() const
            {
			   	size_type res = std::numeric_limits<size_type>::max() / sizeof(node_type);
				
				// hacky patch
				//if (res == 384307168202282325)
				//	return 461168601842738790;
				return (res);
            }
            size_type size() const
            {
                return _tree.size();
            }

			/*
			** Element access
			*/
            iterator lower_bound(const key_type& k)
            {
                for (iterator it = begin(); it != end(); ++it)
                {
                    if (!_comp(it->first, k))
                    {
                        return it;
                    }
                }
                return end();
            }

            const_iterator lower_bound(const key_type& k) const
            {
                for (const_iterator it = begin(); it != end(); ++it)
                {
                    if (!_comp(it->first, k))
                    {
                        return it;
                    }
                }
                return end();
            }

            iterator upper_bound(const key_type& k)
            {
                for (iterator it = begin(); it != end(); ++it)
                {
                    if (_comp(k, it->first))
                    {
                        return it;
                    }
                }
                return end();
            }

            const_iterator upper_bound(const key_type& k) const
            {
                for (const_iterator it = begin(); it != end(); ++it)
                {
                    if (_comp(k, it->first))
                    {
                        return it;
                    }
                }
                return end();
            }

            mapped_type& operator[](const key_type& k)
            {
                return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
            }

			/*
			** Modifiers
			*/
            void erase(iterator position)
            {
                _tree.erase(position);
            }

            size_type erase(const key_type& k)
            {
                iterator it = find(k);

                if (it == end())
                {
                    return 0;
                }
                erase(it);
                return 1;;
            }

            void erase(iterator first, iterator last)
            {
                iterator tmp;
                
                if (first == last)
                {
                    return ;
                }
                tmp = first;
                erase(++first, last);
                erase(tmp);
            }

            void clear()
            {
                _tree.clear();
            }

            ft::pair<iterator,bool> insert(const value_type& val)
            {
                    return _tree.insert(val);
            }

            iterator insert(iterator position, const value_type& val)
            {
                (void)position;
                return (insert(val).first);
            }

            template <class InputIterator>
            void insert(InputIterator first, InputIterator last)
            {
                while (first != last)
                {
                    insert(*first);
                    first++;
                }
            }

			/*
			** Observers
			*/
            size_type count(const key_type& k) const
            {
                const_iterator it = find(k);

                if (it != end())
                {
                    return 1;
                }
                return 0;
            }

            ft::pair<const_iterator,const_iterator> equal_range(const key_type& k) const
            {
                const_iterator first = lower_bound(k);
                const_iterator second = upper_bound(k);
                return ft::make_pair(first, second);
            }

            ft::pair<iterator,iterator> equal_range(const key_type& k)
            {
                iterator first = lower_bound(k);
                iterator second = upper_bound(k);
                return ft::make_pair(first, second);
            }

            iterator find(const key_type& k)
            {
                return _tree.searchByKey(ft::make_pair(k, mapped_type()));
            }

            const_iterator find(const key_type& k) const
            {
                return _tree.searchByKey(ft::make_pair(k, mapped_type()));
            }

			/*
			** Operations
			*/
            map& operator=(const map& x)
            {
                clear();
                _comp = x.key_comp();
                insert(x.begin(), x.end());
                return *this;
            }
            void swap(map& x)
            {
                if (x == *this)
                {
                    return ;
                }
                _tree.swap(x._tree);
            }

			/*
			** Allocator and Compare
			*/
			// NB: return a copy of the allocator
			allocator_type get_allocator() const
            {
                return allocator_type(_alloc);
            }

            key_compare key_comp() const
            {
                return key_compare(_comp);
            }

			value_compare value_comp() const
			{
				return value_compare(_comp);
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
        if (lhs.size() != rhs.size())
        {
            return false;
        }
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
