#ifndef BST_NODE_HPP
#define BST_NODE_HPP

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
				_parent = NULL;
                _left = NULL;
                _right = NULL;
            }

            BST_Node(const BST_Node& nd)
            {
                operator=(nd);
            }

			BST_Node(const value_type& val)
			{
                _value = val;
				_parent = NULL;
                _left = NULL;
                _right = NULL;
			}

            ~BST_Node() {}

            BST_Node& operator=(const BST_Node& nd)
            {
                _value = nd._value;
                _left = nd._left;
                _right = nd._right;
				_parent = nd._parent;
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

			BST_Node* const & getParent() const
			{
				return _parent;
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

            BST_Node& setParent(const BST_Node*& nd)
            {
                _parent = nd;
                return *this;
            }

			BST_Node* findMinimum(BST_Node* nd)
			{
				if (!nd)
				{
					return NULL;
				}
				while (nd->_left)
				{
					nd = nd->left;
				}
				return nd;
			}

			BST_Node* findMaximum(BST_Node* nd)
			{
				if (!nd)
				{
					return NULL;
				}
				while (nd->_right)
				{
					nd = nd->right;
				}
				return nd;
			}

			BST_Node* previous() const
			{
				BST_Node* ret;
				BST_Node* tmp;

				tmp = this;
				if (tmp->_left)
				{
					return findMaximum(tmp->_left);
				}
				// climbing the tree until tmp is the right child of ret
				ret = tmp->_parent;
				while (ret && ret->_left == tmp)
				{
					tmp = ret;
					ret = tmp->_parent;
				}
				return ret;
			}

			BST_Node* next() const
			{
				BST_Node* ret;
				BST_Node* tmp;

				tmp = this;
				if (tmp->_right)
				{
					return findMinimum(tmp->_right);
				}
				// climbing the tree until tmp is the left child of ret
				ret = tmp->_parent;
				while (ret && ret->_right == tmp)
				{
					tmp = ret;
					ret = tmp->_parent;
				}
				return ret;
			}

			bool isLeaf() const
			{
				return (!_left && !_right);
			}

        private:
            value_type _value;
			BST_Node* _parent;
            BST_Node* _left;
            BST_Node* _right;
    };
}

#endif
