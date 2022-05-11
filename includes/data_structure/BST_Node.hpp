#ifndef BST_NODE_HPP
#define BST_NODE_HPP

namespace ft
{
	template <typename T>
    class BST_Node
    {
        public:
            typedef T value_type;

            BST_Node() : value(), parent(NULL), left(NULL), right(NULL) {}

            BST_Node(const BST_Node& nd)
            {
                operator=(nd);
            }

			BST_Node(const value_type& val)
			{
                value = val;
				parent = NULL;
                left = NULL;
                right = NULL;
			}

            ~BST_Node() {}

            BST_Node& operator=(const BST_Node& nd)
            {
                value = nd.value;
                left = nd.left;
                right = nd.right;
				parent = nd.parent;
                return *this;
            }

			BST_Node* findMinimum(BST_Node* nd) const
			{
				if (!nd)
				{
					return NULL;
				}
				while (nd->left)
				{
					nd = nd->left;
				}
				return nd;
			}

			BST_Node* findMaximum(BST_Node* nd) const
			{
				if (!nd)
				{
					return NULL;
				}
				while (nd->right)
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
				if (tmp->left)
				{
					return findMaximum(tmp->left);
				}
				// climbing the tree until tmp is the right child of ret
				ret = tmp->parent;
				while (ret && ret->left == tmp)
				{
					tmp = ret;
					ret = tmp->parent;
				}
				return ret;
			}

			BST_Node* next() const
			{
				BST_Node* ret;
				BST_Node tmp;

				tmp = *this;
				if (tmp.right)
				{
					return findMinimum(tmp.right);
				}
				// climbing the tree until tmp is the left child of ret
				ret = tmp.parent;
				while (ret && *(ret->right) == tmp)
				{
					tmp = *ret;
					ret = tmp.parent;
				}
				return ret;
			}

			bool isLeaf() const
			{
				return (!left && !right);
			}

            bool operator==(const BST_Node& nd) const
            {
                return (value == nd.value &&
                        parent == nd.parent &&
                        left == nd.left &&
                        right == nd.right);
            }

            value_type value;
			BST_Node* parent;
            BST_Node* left;
            BST_Node* right;
    };
}

#endif
