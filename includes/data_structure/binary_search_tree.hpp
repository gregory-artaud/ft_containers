#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "../functional/functional.hpp"

namespace ft
{
    template <typename T>
    class BinarySearchTree
    {
        public:
            typedef T value_type;

            BinarySearchTree()
            {
                value = value_type();
                left = NULL;
                right = NULL;
            }

            ~BinarySearchTree() {}
        private:
            value_type value;
            BinarySearchTree* left;
            BinarySearchTree* right;
    };
}
#endif
