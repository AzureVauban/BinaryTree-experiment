
#include <iostream>
#include <random>

int randomBetween(int a, int b)
{
    std::random_device rd;                       // obtain a random number from hardware
    std::mt19937 gen(rd());                      // seed the generator
    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen); // generate numbers
}

//@namespace BINARY_TREE
//@{
//@    //  binary tree functions
//@    template <typename A>
//@    struct BTNode
//@    {
//@        BTNode<A> *right = nullptr,
//@                  *left = nullptr;
//@        A data;
//@        ~BTNode()
//@        {
//@            if (right)
//@            {
//@                delete right;
//@                right = nullptr;
//@            }
//@            if (left)
//@            {
//@                delete left;
//@                left = nullptr;
//@            }
//@        }
//@    }; // BTNode
//@
//@    template <typename A>
//@    int size_BTNode(BTNode<A> *&root)
//@    {
//@        if (!root)
//@        {
//@            return 0;
//@        }
//@        int subtreesize = size_BTNode(root->right);
//@        subtreesize += size_BTNode(root->left);
//@        return subtreesize + 1;
//@    }
//@
//@    template <typename A>
//@
//@
//@    template <typename A>
//@    void delete_top_BTNode(std::vector<A> &values)
//@    {
//@        BTNode<A> *root = nullptr;
//@        for (int i = 0; i < values.size(); i++)
//@        {
//@            insert_BTNode(root, values.at(i));
//@        }
//@        std::cout << "ROOT ~:        ";
//@        while (root) // CAUSES SEGMENTATION FAULTS
//@        {
//@            std::cout << root->data << " ";
//@            // prioritize rightmost for returning
//@        }
//@        std::cout << std::endl;
//@        delete root;
//@        root = nullptr;
//@    }
//@};

template <class A>
struct BinaryTree
{
private:
    template <typename B>
    struct BinaryTreeNode
    {
        BinaryTreeNode<B> *right = nullptr,
                          *left = nullptr;
        B data;
        BinaryTreeNode(B value) : left(nullptr), right(nullptr), data(value) {}
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
    BinaryTreeNode<A> *head;
    size_t binary_tree_size;

public:
    // CONST MEMBER FUNCTIONS
    BinaryTree() : head(nullptr), binary_tree_size(0) {}

    size_t size() const { return static_cast<size_t>(this->binary_tree_size); }

    bool isempty() const { return !this->head; }

    bool iscomplete() const { return this->iscomplete(this->head); }

    bool isduplicate(A value) const { return this->isduplicate(this->head, value); }

    bool iscomplete() { return this->iscomplete_HELPER(this->head); }
    // MUTATOR MEMBER FUNCTION
    void insert(A value)
    {
        BinaryTreeNode<A> *root = this->head,
                          *nNode = new BinaryTreeNode<A>(value);

        // Special case: empty tree
        if (!root)
        {
            root = nNode;
            this->binary_tree_size += 1;
            return;
        }

        BinaryTreeNode<A> *parentNode = root,
                          *currentNode = root;
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
                delete nNode;
                nNode = nullptr;
            }
        }
        if (value < parentNode->data)
        {
            parentNode->left = nNode;
        }
        else
        {
            parentNode->right = nNode;
        }
        this->binary_tree_size += 1;
    }

    void remove(A value)
    {
        this->remove_HELPER(this->head, value);
        this->binary_tree_size -= 1;
    }

    // MISC FUNCTIONS
    void output_tree()
    {
        this->output_tree_HELPER(this->root);
    }

private: // PRIVATE HELPER FUNCTIONS
    void remove_HELPER(BinaryTreeNode<A> *&root, A value)
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
                    BinaryTreeNode<A> *temp = root;
                    root = root->left;
                    temp->left = nullptr;
                    delete temp;
                }
                else if (!root->left && root->right)
                {
                    BinaryTreeNode<A> *temp = root;
                    root = root->right;
                    temp->right = nullptr;
                    delete temp;
                }
                else
                {
                    BinaryTreeNode<A> *temp = root->right;
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

    bool iscomplete_HELPER(BinaryTreeNode<A> *&root)
    {

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

    bool isduplicate_HELPER(BinaryTreeNode<A> *&root, A value)
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

    void output_tree_HELPER(BinaryTreeNode<A> *&root)
    {
        // outs the tree in te same order as deconstruction
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

int main()
{
    std::vector<int> nums = {};
    BinaryTree<int> myBinaryTree;
    for (int i = 0; i < randomBetween(10, 100); i++)
    {
        int chosen_value = randomBetween(0, 100);
        nums.emplace_back(chosen_value);
        myBinaryTree.insert(chosen_value);
        std::cout << chosen_value << " ";
    }
    std::cout << std::endl;
    std::cout << "SIZE OF BT TREE: " << myBinaryTree.size() << std::endl;
    myBinaryTree.output_tree();
}