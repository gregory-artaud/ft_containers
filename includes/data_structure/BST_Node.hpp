#ifndef BST_NODE_HPP
#define BST_NODE_HPP

namespace ft
{
	template <typename T>
    class BST_Node
    {
        private:
            void copyLinks(const BST_Node& nd)
            {
                parent = nd.parent;
                left= nd.left;
                right = nd.right;
            }

        public:
            typedef T value_type;

            BST_Node() : value(), parent(NULL), left(NULL), right(NULL) {}

            BST_Node(const BST_Node& nd)
            {
                copyLinks(nd);
                value = nd.value;
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
                if (this != &nd)
                {
                    value = nd.value;
                    copyLinks(nd);
                }
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

            BST_Node* findMinimum(void) const
            {
                BST_Node* tmp = (BST_Node*)this;

                while (tmp->left)
                {
                    tmp = tmp->left;
                }
                return tmp;
            }

            BST_Node* findMaximum(void) const
            {
                BST_Node* tmp = (BST_Node*)this;

                while (tmp->right)
                {
                    tmp = tmp->right;
                }
                return tmp;
            }

			BST_Node* previous() const
			{
				BST_Node* ret;
				BST_Node* tmp = (BST_Node*)this;

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
				BST_Node* tmp = (BST_Node*)this;

				if (right)
				{
					return findMinimum(right);
				}
				// climbing the tree until tmp is the left child of ret
				ret = parent;
				while (ret && ret->right == tmp)
				{
					tmp = ret;
					ret = tmp->parent;
				}
				return ret;
			}

			bool isLeaf() const
			{
				return (!left && !right);
			}
            
            bool isRoot() const
            {
                return (!parent);
            }

            bool operator==(const BST_Node& nd) const
            {
                return (value == nd.value);
            }

            value_type value;
			BST_Node* parent;
            BST_Node* left;
            BST_Node* right;
    };
}

#endif
