
#include "heap.h"
#include "binary_tree.h"
#include <random>

template <typename T>
struct priorityqueue{
    std::vector<T> heap;
    explicit priorityqueue() {
        heap = {};
    }
    explicit priorityqueue(const std::vector<T>&values) {
        for (int i = 0; i < values.size();i++)
        {
            heap.emplace_back(values.at(i));
        }
    }
    T enqueue(T value)
    {
        heap.emplace_back(value);
    
    }
    ~priorityqueue() {
        // deallocate heap but since its a vector 
        // c++ does it automatically
        std::cout << "deallocated object at " << this << std::endl;
    }

};  
int randomBetween(int a, int b)
{
    std::random_device rd;                       // obtain a random number from hardware
    std::mt19937 gen(rd());                      // seed the generator
    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen); // generate numbers
}

void temp()
{
    using namespace std;
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
    std::vector<int> nums = {};
    for (int i = 0; i < randomBetween(10, 100);i++)
    {
        int chosen_value = randomBetween(0, 100);
        nums.emplace_back(chosen_value);
        std::cout << chosen_value << " ";
    }
    std::cout << std::endl;
    HEAP::heapSort(nums);
    for (int i = 0; i < nums.size(); i++)
    {
        
        std::cout << nums.at(i) << " ";
    }
    std::cout << std::endl;
    //make a balanced tree
    BINARY_TREE::BTNode<int> *root = nullptr;
    for (int i = 0; i < nums.size(); i++)
    {
        BINARY_TREE::insert_BTNode(root, nums.at(i));
    }
    delete root;
    root = nullptr;
    std::cout << "terminating process" << std::endl;
    return 0;
    }