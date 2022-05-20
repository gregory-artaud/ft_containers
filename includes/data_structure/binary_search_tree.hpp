#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include "../functional/functional.hpp"
#include "../utility/utility.hpp"
#include "../iterator/bst_iterator.hpp"
#include "../iterator/reverse_iterator.hpp"
#include "BST_Node.hpp"

namespace ft
{
    template <typename T, class Compare = ft::less<T>,
        class Node = ft::BST_Node<T>,
        class Alloc = std::allocator<Node> >
    class BinarySearchTree
    {
        public:
            typedef T value_type;
			typedef Node node_type;
			typedef Node* node_pointer;
            typedef Alloc allocator_type;
            typedef Compare compare_type;

			typedef ft::bst_iterator<node_type, Compare> iterator;
			typedef ft::bst_const_iterator<node_type, Compare> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef size_t size_type;

            BinarySearchTree(const allocator_type& allocator = allocator_type(),
                    const compare_type& compare = compare_type())
            {
                _alloc = allocator;
                _comp = compare;

                _start = _alloc.allocate(1);
                _alloc.construct(_start, node_type());
				_end = _alloc.allocate(1);
                _size = 0;
                _root = NULL;
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
				return iterator(_start->parent);
			}
			const_iterator begin() const
			{
				return const_iterator(_start->parent);
			}
			iterator end()
			{
				return iterator(_end);
			}
			const_iterator end() const
			{
				return const_iterator(_end);
			}

            size_type erase(const value_type& val)
            {
                size_type initialSize = _size;

                _deleteByKey(_root, val);
                return (initialSize - _size);
            }
            
            void clear()
            {
                // TODO
            }

            node_pointer searchByKey(value_type toSearch)
            {
               if (!_root)
               {
                   return NULL;
               }
               return _searchByKey(toSearch, _root);
            }

            size_type size() const
            {
                return _size;
            }

            ft::pair<iterator,bool> insert(const value_type& val)
            {
                node_pointer position;
                bool newNodeHasBeenInserted;
                size_type initialSize = _size;

                position = _insert(_root, val);

                // On first element inserted
                if (!_root)
                {
                    _root = position;
                    _root->left = _start;
                    _start->parent = _root;
                    _root->right = _end;
                }
                newNodeHasBeenInserted = (initialSize != _size);
                return ft::make_pair<iterator,bool>(iterator(position), newNodeHasBeenInserted);
            }

            bool isLeaf(const node_type& nd) const
            {
                return nd.isLeaf() || (nd.left == _start && nd.right == _end);
            }

        private:
            node_pointer _start;
            node_pointer _root;
			node_pointer _end;
            allocator_type _alloc;
            compare_type _comp;
            size_type _size;

            node_pointer _deleteByKey(node_pointer root, const value_type& val)
            {
                if (!root)
                {
                    return NULL;
                }
                // Going in right subtree
                if (_comp(root->value.first, val.first))
                {
                    // Special case to keep iterators consistency
                    if (root->right == _end)
                    {
                        return NULL;
                    }
                    else
                    {
                        root->right = _deleteByKey(root->right, val);
                    }
                }
                // Going in left subtree
                else if (_comp(val.first, root->value.first))
                {
                    // Special case to keep iterators consistency
                    if (root->left == _start)
                    {
                        return NULL;
                    }
                    else
                    {
                        root->left = _deleteByKey(root->left, val);
                    }
                }
                // Deletion happens here
                else
                {
                    // root is leaf
                    if (isLeaf(*root))
                    {
                        _destroy(root);
                        return NULL;
                    }
                    // root has right child
                    else if (root->left == NULL || root->left == _start)
                    {
                        node_pointer tmp = root->right;

                        _destroy(root);
                        return tmp;
                    }
                    // root has left child
                    else if (root->right == NULL || root->right == _end)
                    {
                        node_pointer tmp = root->left;

                        _destroy(root);
                        return tmp;
                    }
                    // root has both left and right child
                    else
                    {
                        root->value = _getMin(root->right)->value;
                        root->right = _deleteByKey(root->right, root->value);
                    }
                }
                return root;
            }

            void _unlink(node_pointer node)
            {
                if (node->isRoot())
                {
                    _start->parent = NULL;
                    return ;
                }
                if (node->left == _start)
                {
                    node->parent->left = _start;
                    _start->parent = node->parent->left;
                }
                if (node->right == _end)
                {
                    node->parent->right = _end;
                }
            }

            void _destroy(node_pointer node)
            {
                _unlink(node);
                _alloc.destroy(node);
                _alloc.deallocate(node, 1);
            }

            node_pointer _getNewNode(const value_type& val = value_type())
            {
                node_pointer newNode = _alloc.allocate(1);

                _alloc.construct(newNode, node_type(val));
                return newNode;
            }

            node_pointer _getMax(node_pointer root) const
            {
                node_pointer nd = root;

                while (nd && nd->right != _end)
                {
                    nd = nd->right;
                }
                return nd;
            }

            node_pointer _getMin(node_pointer root) const
            {
                node_pointer nd = root;

                while (nd && nd->left != _start)
                {
                    nd = nd->left;
                }
                return nd;
            }

            void _placeBeforeEnd(node_pointer newNode, node_pointer max)
            {
                if (!max)
                {
                    return ;
                }
                max->right = newNode;
                newNode->parent = max;
                newNode->right = _end;
            }

            void _placeAfterStart(node_pointer newNode, node_pointer min)
            {
                if (!min)
                {
                    return ;
                }
                min->left = newNode;
                newNode->parent = min;
                newNode->left = _start;
                _start->parent = newNode;
            }

            node_pointer _insert(node_pointer root, const value_type& val)
            {
                if (!root)
                {
                    _size++;
                    return _getNewNode(val);
                }
                if (_comp(root->value.first, val.first))
                {
                    if (root->right == _end)
                    {
                        // Insert new node between root and _end to keep iterator consistency
                        _placeBeforeEnd(_getNewNode(val), root);
                        _size++;
                    }
                    else
                    {
                        root->right = _insert(root->right, val);
                        root->right->parent = root;
                    }
                }
                if (_comp(val.first, root->value.first))
                {
                    // Insert new node between root and _start to keep iterator consistency
                    if (root->left == _start)
                    {
                        _placeAfterStart(_getNewNode(val), root);
                        _size++;
                    }
                    else
                    {
                        root->left = _insert(root->left, val);
                        root->left->parent = root;
                    }
                }
                return root; // In case of root->value == val

            }

            node_pointer _searchByKey(value_type toSearch, node_pointer nd)
            {
                if (!nd)
                {
                    return NULL;
                }

                value_type ndValue = nd->value;

                if (ndValue.first == toSearch.first)
                {
                    return nd;
                }
                if (ndValue.first < toSearch.first)
                {
                    return _searchByKey(toSearch, nd->right);
                }
                return _searchByKey(toSearch, nd->left);
            }
    };
}
#endif
