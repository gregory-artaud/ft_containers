#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "../functional/functional.hpp"
#include "BST_Node.hpp"

namespace ft
{
    template <typename T, class Compare = ft::less<T>, class Node = ft::BST_Node<T>,
        class Alloc = std::allocator<T> >
    class BinarySearchTree
    {
        public:
            typedef T value_type;
			typedef Node node_type;
            typedef Alloc allocator_type;

            BinarySearchTree(const allocator_type& allocator = allocator_type())
            {
                _root = NULL;
                _alloc = allocator;
            }

            ~BinarySearchTree() {}

        private:
            Node* _root;
            allocator_type _alloc;
    };
}
#endif
