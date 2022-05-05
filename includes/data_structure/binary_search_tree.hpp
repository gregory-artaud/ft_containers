#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "../functional/functional.hpp"
#include "../utility/utility.hpp"
#include "../iterator/bst_iterator.hpp"
#include "BST_Node.hpp"

// Working on:
// erase
namespace ft
{
    template <typename T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>,
        class Alloc = std::allocator<T> >
    class BinarySearchTree
    {
        public:
            typedef T value_type;
			typedef Node node_type;
			typedef Node* node_pointer;
            typedef Alloc allocator_type;

			typedef ft::bst_iterator<node_type> iterator;
			typedef ft::bst_iterator<const node_type> const_iterator;

			typedef size_t size_type;

            BinarySearchTree(const allocator_type& allocator = allocator_type())
            {
                _alloc = allocator;

				_start = _alloc.allocate(1);
				_alloc.construct(_start, node_type());
				_end = _alloc.allocate(1);
				_start->setParent(_end);
            }

            ~BinarySearchTree()
			{
				clear();
				_alloc.deallocate(_end, 1);
				_alloc.destroy(_start);
				_alloc.deallocate(_start, 1);
			}

			iterator begin()
			{
				return iterator(_start->getParent());
			}
			const_iterator begin() const
			{
				return iterator(_start->getParent());
			}
			iterator end()
			{
				return iterator(_end);
			}
			const_iterator end() const
			{
				return iterator(_end);
			}

			ft::pair<iterator,bool> insert(const value_type& val)
			{
				(void)val;
				return ft::make_pair<iterator,bool>(end(), false);
			}

			size_type erase(node_pointer nd)
			{
				int side;

				if (_hasNoChild(nd))
				{
					_deleteNoChild(nd);
					return 1;
				}
				if ((side = _hasOneChild(nd)))
				{
					_deleteOneChild(nd, side);
					return 1;
				}
				if (_hasTwoChild(nd))
				{
					_deleteTwoChild(nd);
					return 1;
				}
				return 0;
			}

			void clear()
			{
				erase(begin(), end());
			}

        private:
			node_pointer _start;
			node_pointer _end;
            allocator_type _alloc;

			bool _hasNoChild(node_pointer nd) const
			{
				bool ret;

				ret = nd->isLeaf();
				ret = ret || (nd->getLeft() == _start && !nd->getRight());
				ret = ret || (nd->getRight() == _end && !nd->getLeft());
				ret = ret || ((nd->getRight() == _end) && (nd->getLeft() == _start));
				return ret;
			}

			int _hasOneChild(node_pointer nd) const
			{
				(void)nd;
				return 0;
			}

			bool _hasTwoChild(node_pointer nd) const
			{
				node_pointer left = nd->getLeft();
				node_pointer right = nd->getRight();

				return (left && (left != _start) && right && (right != _end));
			}

			void _deleteNoChild(node_pointer nd)
			{
				int side = nd->getSide();
				_alloc.destroy(nd);
				_alloc.deallocate(nd);
			}

			void _deleteOneChild(node_pointer nd, int side)
			{
				node_pointer new_child = nd->getUniqueChild(side);
				node_pointer parent = nd->getParent();

				

			}
    };
}
#endif
