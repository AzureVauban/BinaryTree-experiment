#pragma once

namespace BINARY_TREE
{
    //  binary tree functions
    template <typename T>
    struct BTNode
    {
        BTNode<T> *right = nullptr,
                  *left = nullptr;
        T data;
        ~BTNode()
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
    }; // BTNode
    template <typename T>
    bool isduplicate(BTNode<T> *&root, T value)
    {
        if (!root)
        {
            return false;
        }
        if (root->data == value)
        {
            return true;
        }
        return isduplicate(root->left, value) || isduplicate(root->right, value);
    }
    template <typename T>
    void insert_BTNode(BTNode<T> *&root, T value)
    {
        // Create a new node
        BTNode<T> *newNode = new BTNode<T>;
        newNode->data = value;

        // Special case: empty tree
        if (!root)
        {
            root = newNode;
        }
        else
        {
            BTNode<T> *parentNode = nullptr;
            BTNode<T> *currentNode = root;
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
    template <typename T>
    int size_BTNode(BTNode<T> *&root)
    {
        if (!root)
        {
            return 0;
        }
        int subtreesize = size_BTNode(root->right);
        subtreesize += size_BTNode(root->left);
        return subtreesize + 1;
    }

    template <typename T>
    void output_tree(BTNode<T> *&root)
    {
        // outs the tree in te same order as deconstruction
        if (root)
        {
            output_tree(root->right);
            output_tree(root->left);
            std::cout << root->data << " ";
        }
    }
    template <typename T>
    void remove_BTNode(BTNode<T> *&root, T value)
    {
        if (!root)
        {

            if (value < root->data)
            {
                remove_BTNode(root->left, value);
            }
            else if (value > root->data)
            {
                remove_BTNode(root->right, value);
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
                    BTNode<T> *temp = root;
                    root = root->left;
                    temp->left = nullptr;
                    delete temp;
                }
                else if (!root->left && root->right)
                {
                    BTNode<T> *temp = root;
                    root = root->right;
                    temp->right = nullptr;
                    delete temp;
                }
                else
                {
                    BTNode<T> *temp = root->right;
                    while (temp && temp->left)
                    {
                        temp = temp->left;
                    }
                    root->data = temp->data;
                    remove_BTNode(root->right, temp->data);
                }
            }
        }
    }
    template <typename T>
    bool iscomplete(BTNode<T> *&root)
    {

        if (!root->left && !root->right)
        {
            return true;
        }
        else if (root->left && root->right)
        {
            return iscomplete(root->left) && iscomplete(root->right);
        }
        else
        {
            return false;
        }
        return false;
    }

    template <typename T>
    void delete_top_BTNode(std::vector<T> &values)
    {
        BTNode<T> *root = nullptr;
        for (int i = 0; i < values.size(); i++)
        {
            insert_BTNode(root, values.at(i));
        }
        std::cout << "ROOT ~:        ";
        while (root) // CAUSES SEGMENTATION FAULTS
        {
            std::cout << root->data << " ";
            // prioritize rightmost for returning
        }
        std::cout << std::endl;
        delete root;
        root = nullptr;
    }
};
