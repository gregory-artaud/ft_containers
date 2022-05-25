#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <fstream>
#include <string>
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
			typedef ft::bst_const_iterator<node_type, const value_type, Compare> const_iterator;
            typedef ft::reverse_iterator<iterator> reverse_iterator;
            typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

			typedef size_t size_type;

            BinarySearchTree(const allocator_type& allocator = allocator_type(),
                    const compare_type& compare = compare_type())
            {
                _alloc = allocator;
                _comp = compare;

                _start = _getNewNode();
				_end = _getNewNode();
                _start->parent = _end;
                _size = 0;
                _root = NULL;
            }

            ~BinarySearchTree()
			{
                clear();
                _destroy(_start);
                _destroy(_end);
			}

            void clear()
            {
                while (size() > 0)
                {
                    erase(begin());
                }
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
                if (size() == 0)
                {
                    return begin();
                }
				return iterator(_end);
			}
			const_iterator end() const
			{
                if (size() == 0)
                {
                    return begin();
                }
				return const_iterator(_end);
			}
            reverse_iterator rbegin()
            {
                return reverse_iterator(_end);
            }
            const_reverse_iterator rbegin() const
            {
                return const_reverse_iterator(_end);
            }
            reverse_iterator rend()
            {
                return reverse_iterator(_start->parent);
            }
            const_reverse_iterator rend() const
            {
                return const_reverse_iterator(_start->parent);
            }

            void erase(iterator it)
            {
                if (_searchByKey(*it, _root))
                {
                    _deleteByKey(_root, *it);
                }
            } 
            
            iterator searchByKey(value_type toSearch)
            {
                node_pointer nd = _searchByKey(toSearch, _root);

                if (!nd)
                {
                    return end();
                }
                return iterator(nd);
            }

            const_iterator searchByKey(value_type toSearch) const
            {
                node_pointer nd = _searchByKey(toSearch, _root);

                if (!nd)
                {
                    return end();
                }
                return const_iterator(nd);
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
                    _end->parent = _root;
                }
                newNodeHasBeenInserted = (initialSize != _size);
                if (newNodeHasBeenInserted)
                {
                    position = _searchByKey(val, _root);
                }
                return ft::make_pair<iterator,bool>(iterator(position), newNodeHasBeenInserted);
            }

            bool isLeaf(const node_type& nd) const
            {
                return nd.isLeaf();
            }

            void swap(BinarySearchTree& tree)
            {
                node_pointer tmp;
                size_type sz;

                tmp = tree._root;
                tree._root = _root;
                _root = tmp;

                tmp = tree._end;
                tree._end = _end;
                _end = tmp;

                tmp = tree._start;
                tree._start = _start;
                _start = tmp;

                sz = tree._size;
                tree._size = _size;
                _size = sz;
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
                    root->right = _deleteByKey(root->right, val);
                    if (root->right)
                    {
                        root->right->parent = root;
                    }
                }
                // Going in left subtree
                else if (_comp(val.first, root->value.first))
                {
                    root->left = _deleteByKey(root->left, val);
                    if (root->left)
                    {
                        root->left->parent = root;
                    }
                }
                // Deletion happens here
                else
                {
                    // root is leaf
                    if (root->isLeaf())
                    {
                        if (root->isRoot())
                        {
                           _start->parent = NULL;
                           _end->parent = NULL;
                           _root = NULL;
                        }
                        _destroy(root);
                        _size--;
                        return NULL;
                    }
                    // root has right child
                    else if (root->left == NULL)
                    {
                        node_pointer tmp = root->right;
                        
                        _destroy(root);
                        _size--;
                        return tmp;
                    }
                    // root has left child
                    else if (root->right == NULL)
                    {
                        node_pointer tmp = root->left;

                        _destroy(root);
                        _size--;
                        return tmp;
                    }
                    // root is the last node
                    else if (root->left == _start && root->right == _end)
                    {
                        _start->parent = NULL;
                        _end->parent = NULL;
                        _root = NULL;
                        _destroy(root);
                        _size--;
                        return NULL;
                    }
                    // root has both left and right child
                    else
                    {
                        root->value = _getMin(root->right)->value;
                        root->right = _deleteByKey(root->right, root->value);
                        if (root->right)
                        {
                            root->right->parent = root;
                        }
                    }
                }
                return root;
            }

            void _relink(node_pointer node)
            {
                if (node->left == _start)
                {
                    node->parent->left = _start;
                    _start->parent = node->parent->left;
                }
                if (node->right == _end)
                {
                    node->parent->right = _end;
                    _end->parent = node->parent->right;
                }
            }

            void _destroy(node_pointer node)
            {
                if (!node->isRoot())
                {
                    _relink(node);
                }
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

                while (nd && nd->right && nd->right != _end)
                {
                    nd = nd->right;
                }
                return nd;
            }

            node_pointer _getMin(node_pointer root) const
            {
                node_pointer nd = root;

                while (nd && nd->left && nd->left != _start)
                {
                    nd = nd->left;
                }
                return nd;
            }

            node_pointer _insert(node_pointer root, const value_type& val)
            {
                if (!root)
                {
                    _size++;
                    return _getNewNode(val);
                }
                if (root == _start)
                {
                    node_pointer newNode = _getNewNode(val);

                    newNode->left = _start;
                    _start->parent = newNode;
                    _size++;
                    return newNode;
                }
                if (root == _end)
                {
                    node_pointer newNode = _getNewNode(val);

                    newNode->right = _end;
                    _end->parent = newNode;
                    _size++;
                    return newNode;
                }
                if (_comp(root->value.first, val.first))
                {
                    root->right = _insert(root->right, val);
                    if (root->right)
                    {
                        root->right->parent = root;
                    }
                }
                if (_comp(val.first, root->value.first))
                {
                    root->left = _insert(root->left, val);
                    if (root->left)
                    {
                        root->left->parent = root;
                    }
                }
                return root; // In case of root->value == val

            }

            node_pointer _searchByKey(value_type toSearch, node_pointer nd) const
            {
                if (!nd || nd == _start || nd == _end)
                {
                    return NULL;
                }

                value_type ndValue = nd->value;

                if (_comp(ndValue.first, toSearch.first))
                {
                    return _searchByKey(toSearch, nd->right);
                }
                else if (_comp(toSearch.first, ndValue.first))
                {
                    return _searchByKey(toSearch, nd->left);
                }
                return nd;
            }
            
            void _writeTree(node_pointer node, std::ofstream& fs) const
            {
                node_pointer child;

                if (!node)
                {
                    return ;
                }
                if (isLeaf(*node) && node->isRoot())
                {
                    fs << "\t\"" << node << "\"";
                    return ;
                }
                child = node->left;
                if (child)
                {
                    fs << "\t\"" << node << "\" -- \"" << child << "\"\n";
                }
                child = node->right;
                if (child)
                {
                    fs << "\t\"" << node << "\" -- \"" << child << "\"\n";
                }
                child = node->left;
                if (child)
                {
                    _writeTree(child, fs);
                }
                child = node->right;
                if (child)
                {
                    _writeTree(child, fs);
                }
            }

        public:
            void genDot() const
            {
                static int id = 0;
                const char name[6] = { id++ + 'a', '.', 'd', 'o', 't', 0 };
                std::ofstream file(name);
                const_iterator it = begin();

                file << "graph tree {\n\tforcelabels=true\n";

                // parse labels
                while (it != end())
                {
                    // write labels
                    file << "\t\"" << it.base() << "\"[label=\"" <<
                        it->first << "," << it->second << "\"]\n";
                    it++;
                }
                file << "\t\"" << _start << "\"[label=\"start\"]\n";
                file << "\t\"" << _end << "\"[label=\"end\"]\n";

                _writeTree(_root, file);
                file << "\n}";
                file.close();
            }
    };
}
#endif
