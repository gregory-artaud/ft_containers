#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "../functional/functional.hpp"
#include "../utility/utility.hpp"
#include "../iterator/bst_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "BST_Node.hpp"

namespace ft
{
    template <typename T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>,
        class Alloc = std::allocator<Node> >
    class BinarySearchTree
    {
        public:
            typedef T value_type;
			typedef Node node_type;
			typedef Node* node_pointer;
            typedef Alloc allocator_type;

			typedef ft::bst_iterator<node_type, Compare> iterator;
			typedef ft::bst_const_iterator<node_type, Compare> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef size_t size_type;

            BinarySearchTree(const allocator_type& allocator = allocator_type())
            {
                _alloc = allocator;

				_start = _alloc.allocate(1);
				_alloc.construct(_start, node_type());
				_end = _alloc.allocate(1);
				_start->parent = _end;
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
				return iterator(_start->left);
			}
			const_iterator begin() const
			{
				return const_iterator(_start->left);
			}
			iterator end()
			{
				return iterator(_end);
			}
			const_iterator end() const
			{
				return const_iterator(_end);
			}
            
            void clear()
            {
                // TODO
            }

        private:
			node_pointer _start;
			node_pointer _end;
            allocator_type _alloc;
    };
}
#endif
