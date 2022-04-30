#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "../functional/functional.hpp"

namespace ft
{
    template <typename T>
    class BST_Node
    {
        public:
            typedef T value_type;

            BST_Node()
            {
                _value = value_type();
                _left = NULL;
                _right = NULL;
            }

            BST_Node(const BST_Node& nd)
            {
                operator=(nd);
            }

            ~BST_Node() {}

            BST_Node& operator=(const BST_Node& nd)
            {
                _value = nd._value;
                _left = nd._left;
                _right = nd._right;
                return *this;
            }

            BST_Node* const & getLeft() const
            {
                return _left;
            }

            BST_Node* const & getRight() const
            {
                return _right;
            }

            value_type const & getValue() const
            {
                return _value;
            }

            BST_Node& setValue(const value_type& val)
            {
                _value = val;
                return *this;
            }

            BST_Node& setLeft(const BST_Node*& nd)
            {
                _left = nd;
                return *this;
            }

            BST_Node& setRight(const BST_Node*& nd)
            {
                _right = nd;
                return *this;
            }

        private:
            value_type _value;
            BST_Node* _left;
            BST_Node* _right;
    };


    template <typename T, class Compare = ft::less<T>, class Node = BST_Node<T>,
        class Alloc = std::allocator<T> >
    class BinarySearchTree
    {
        public:
            typedef T value_type;
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
