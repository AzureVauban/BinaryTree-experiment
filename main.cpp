/*
none main branch
*/
#include <iostream>
#include <random>
#include <vector>
using namespace std;
int randomBetween(int a, int b)
{
    std::random_device rd;                       // obtain a random number from hardware
    std::mt19937 gen(rd());                      // seed the generator
    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen); // generate numbers
}

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
    void remove_maxBTNode(BTNode<T> *&root, T removed)
    {
        // Base case: if the tree is empty, do nothing
        if (!root)
            return;

        // If there is a right child, then the maximum value is in the right subtree
        if (root->right)
        {
            remove_maxBTNode(root->right, removed); // SEGMENT FAULT FROM REMOVE_MAXBTNODE()
        }
        else
        {
            removed = root->data;
            BTNode<T> *temp = root->left;
            delete root;
            root = temp;
        }
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
            cout << root->data << " ";
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
        // BTNODE<T> is defined as follows:
        // template <typename T>
        // struct BTNode
        // {
        //     BTNode<T> *right = nullptr,
        //               *left = nullptr;
        //     T data;
        //     ~BTNode()
        //     {
        //         if (right)
        //         {
        //             delete right;
        //             right = nullptr;
        //         }
        //         if (left)
        //         {
        //             delete left;
        //             left = nullptr;
        //         }
        //     }
        // }; // BTNode
        BTNode<T> *root = nullptr;
        for (int i = 0; i < values.size(); i++)
        {
            insert_BTNode(root, values.at(i));
        }
        cout << "ROOT ~:        ";
        while (root) // CAUSES SEGMENTATION FAULTS
        {
            cout << root->data << " ";
            // prioritize rightmost for returning
        }
        cout << endl;
        delete root;
        root = nullptr;
    }
}

template <typename T>
struct PriorityQueue
{
    /*
    Node: i
    Left child: 2i + 1
    Right child: 2i + 2
    parent: (i-1)/2
    */

    typedef std::size_t size_type;

private:
    static const size_type DEFAULT_CAPACITY = 1;
    template <typename TT>
    struct PQNode : public BINARY_TREE::BTNode<T>
    {
        size_type index;

    public:
        PQNode(TT value, std::size_t index)
        {
            this->data = value;
            this->index = index;
            this->left = nullptr;
            this->right = nullptr;
        }
    };
    PQNode<T> *heap;

public:
    PriorityQueue()
    {
        heap = nullptr;
    }
    ~PriorityQueue()
    {
        if (heap)
        {
            delete heap;
            heap = nullptr;
        }
    }
    bool isempty() const { return !this->heap; }

    //MEMBER FUNCTIONS
    void enqueue(T value, size_type priority)
    {
        if (isempty())
        {
            this->heap = new PQNode<T>(value, priority);
            // this->heap->data = value;
            // this->heap->index = priority;
        } else {
        }
    }
    T peak()
    {
        if (this->isempty())
        {
            return T();
        }
        else
        {
            return this->heap->data;
        }
    }
    void update() {
        //NOT IMPLEMENTED YET
    }
};
// template <typename T>
// struct PriorityQueue
//{
//     // parent is never less than the item of its children
//     typedef int value_type;
//     typedef size_t size_type;
//     static const size_type DEFAULT_CAPACITY = 1;
//     // CONSTRUCTORS AND DESTRUCTOR
// private:
//     struct ItemType
//     {
//         value_type data;
//         size_type priority;
//     };
//     ItemType *Heap;
//     size_type = index;
//
// public:
// PriorityQueue(size_type capacity) {
//     Heap = new ItemType[capacity];
// }
//~PriorityQueue() {
//     delete [] Heap;
//     Heap = nullptr;
// }
// void enqueue(const size_type& entry,size_type priority){
//
// }
// };
//
void temp()
{
    const bool DOSORTCASE = false;
    // USE BREATH-FIRST ALGORITHM TO BALANCE THE BINARY TREE
    vector<int> comparisonstack, // FIFO
        comparisonqueue;         // FILO
    BINARY_TREE::BTNode<int> *head = nullptr;
    const int expected_tree_size = // randomBetween(10, 50);
        10;
    cout << "Expected size of Binary Tree: " << expected_tree_size << endl;
    //    cout << "Current size of Binary Tree: " << size_BTNode(head) << endl;

    // print in order of what a queue would look like
    cout << "STACK ORDER:   ";
    while (BINARY_TREE::size_BTNode(head) != expected_tree_size)
    {
        auto chosen_value = randomBetween(0, 100);
        if (!BINARY_TREE::isduplicate(head, chosen_value))
        {
            comparisonstack.emplace_back(chosen_value);
            // add to the front of the queue
            comparisonqueue.insert(comparisonqueue.begin(), chosen_value);

            BINARY_TREE::insert_BTNode(head, chosen_value);

            cout << chosen_value << " ";
        }
    }
    cout << endl;
    // print in order of what a queue would look like
    cout << "QUEUE ORDER:   ";
    for (int i = comparisonqueue.size(); i > 0; i--)
    {
        cout << comparisonqueue.front() << " ";
        comparisonqueue.erase(comparisonqueue.begin()); // remove the front value from the
    }
    cout << endl;
    // print in order of what the tree deconstruction would look like
    cout << "TREE ORDER:    ";
    BINARY_TREE::output_tree(head);
    cout << endl;
    BINARY_TREE::delete_top_BTNode(comparisonstack);
    if (DOSORTCASE)
    {
        // sort vector from least to greatest
        for (int i = 0; i < comparisonstack.size(); i++)
        {
            for (int j = i + 1; j < comparisonstack.size(); j++)
            {
                if (comparisonstack[i] > comparisonstack[j])
                {
                    // Swap v[i] and v[j]
                    int temp = comparisonstack[i];
                    comparisonstack[i] = comparisonstack[j];
                    comparisonstack[j] = temp;
                }
            }
        }
        delete head;
        head = nullptr;
        if (comparisonstack.size() % 2 == 0)
        {
            // get the greater value of the two middle indicies and swap it with the front value
            int middle = comparisonstack.size() / 2;
            int front = comparisonstack.at(0);
            if (comparisonstack.at(middle) > comparisonstack.at(middle - 1))
            {
                comparisonstack.at(0) = comparisonstack.at(middle);
                comparisonstack.at(middle) = front;
            }
            else
            {
                comparisonstack.at(0) = comparisonstack.at(middle - 1);
                comparisonstack.at(middle - 1) = front;
            }
        }
        else
        {
            // swap the front value with the exact middle value
            int middle = comparisonstack.size() / 2;
            int front = comparisonstack.at(0);
            comparisonstack.at(0) = comparisonstack.at(middle);
            comparisonstack.at(middle) = front;
        }
        for (int i = 0; i < comparisonstack.size(); i++)
        {
            BINARY_TREE::insert_BTNode(head, comparisonstack.at(i));
        }
        // cout << "The binary tree has a size " << size(<int>head)<< endl;
        // print in order of what the tree deconstruction would look like once sorted in ascending order
        cout << "TREE (SORTED): ";
        BINARY_TREE::output_tree(head);
        cout << endl;
    }

    if (head)
    {
        delete head;
        cout << endl;
        head = nullptr;
    }
}
int main()
{
    PriorityQueue<int> greatestheap;
    for (int i = 0; i < 10; i++)
    {
        int value = randomBetween(0, 100);
        greatestheap.enqueue(value, i);
    }

    cout << greatestheap.peak() << endl;
    std::cout << "terminating process" << std::endl;
    return 0;
}