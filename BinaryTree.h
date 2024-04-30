#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>

namespace BINARYTREE
{
    template <class datatype_A>
    struct BinaryTree
    {
    private:
        template <typename datatype_B>
        struct BinaryTreeNode
        {
            BinaryTreeNode<datatype_B> *right = nullptr,
                                       *left = nullptr;
            datatype_B data;
            BinaryTreeNode(datatype_B value) : left(nullptr), right(nullptr), data(value) {}
            ~BinaryTreeNode()
            {
                if (right)
                {
                    delete right;
                    right = nullptr;
                }
                if (left)
                {
                    delete left;
                    left = nullptr;
                }
            }
        };

    private:
        BinaryTreeNode<datatype_A> *head;
        size_t binary_tree_size;

    public:
        // CONST MEMBER FUNCTIONS
        BinaryTree() : head(nullptr), binary_tree_size(0) {}

        size_t size() const { return static_cast<size_t>(this->binary_tree_size); }

        bool isempty() const { return !this->head; }
        datatype_A peek() const
        {
            if (!this->head)
            {
                datatype_A();
            }
            return this->head->data;
        }
        bool iscomplete() const { return this->iscomplete(this->head); }

        bool isduplicate(datatype_A value) const { return this->isduplicate(this->head, value); }

        bool iscomplete() { return this->iscomplete_HELPER(this->head); }
        // MUTATOR MEMBER FUNCTION
        void insert(datatype_A value) { this->insert_HELPER(this->head, value); }
        void remove(datatype_A value)
        {
            this->remove_HELPER(this->head, value);
            this->binary_tree_size -= 1;
        }

        // MISC FUNCTIONS
        void output_tree()
        {
            this->output_tree_HELPER(this->head);
        }

    private: // PRIVATE HELPER FUNCTIONS
        void remove_HELPER(BinaryTreeNode<datatype_A> *&root, datatype_A value)
        {
            if (!root)
            {

                if (value < root->data)
                {
                    remove_HELPER(root->left, value);
                }
                else if (value > root->data)
                {
                    remove_HELPER(root->right, value);
                }
                else
                {
                    if (!root->left && !root->right)
                    {
                        delete root;
                        root = nullptr;
                    }
                    else if (root->left && !root->right)
                    {
                        BinaryTreeNode<datatype_A> *temp = root;
                        root = root->left;
                        temp->left = nullptr;
                        delete temp;
                    }
                    else if (!root->left && root->right)
                    {
                        BinaryTreeNode<datatype_A> *temp = root;
                        root = root->right;
                        temp->right = nullptr;
                        delete temp;
                    }
                    else
                    {
                        BinaryTreeNode<datatype_A> *temp = root->right;
                        while (temp && temp->left)
                        {
                            temp = temp->left;
                        }
                        root->data = temp->data;
                        remove_HELPER(root->right, temp->data);
                    }
                }
            }
        }

        void insert_HELPER(BinaryTreeNode<datatype_A> *&root, datatype_A value)
        {
            // Create a new node
            BinaryTreeNode<datatype_A> *newNode = new BinaryTreeNode<datatype_A>;
            newNode->data = value;

            // Special case: empty tree
            if (!root)
            {
                root = newNode;
            }
            else
            {
                BinaryTreeNode<datatype_A> *parentNode = nullptr,*currentNode = root;
                while (currentNode)
                {
                    parentNode = currentNode;
                    if (value < currentNode->data)
                    {
                        currentNode = currentNode->left;
                    }
                    else if (value > currentNode->data)
                    {
                        currentNode = currentNode->right;
                    }
                    else
                    {
                        delete newNode;
                        newNode = nullptr;
                    }
                }
                if (value < parentNode->data)
                {
                    parentNode->left = newNode;
                }
                else
                {
                    parentNode->right = newNode;
                }
            }
        }

        bool iscomplete_HELPER(BinaryTreeNode<datatype_A> *&root)
        {
            if (!root)
            {
                return true;
            }
            if (!root->left && !root->right)
            {
                return true;
            }
            else if (root->left && root->right)
            {
                return iscomplete_HELPER(root->left) && iscomplete_HELPER(root->right);
            }
            else
            {
                return false;
            }
            return false;
        }

        bool isduplicate_HELPER(BinaryTreeNode<datatype_A> *&root, datatype_A value)
        {
            if (!root)
            {
                return false;
            }
            if (root->data == value)
            {
                return true;
            }
            return isduplicate_HELPER(root->left, value) || isduplicate_HELPER(root->right, value);
        }

        void output_tree_HELPER(BinaryTreeNode<datatype_A> *&root)
        {
            // outs the tree in the same order as deconstruction
            if (root)
            {
                output_tree_HELPER(root->right);
                output_tree_HELPER(root->left);
                std::cout << root->data << " ";
            }
        }

    public:
        ~BinaryTree()
        {
            delete head;
            head = nullptr;
        }
    };
}
#endif // BINARYTREE_H