#include "BinaryTree.h"
#include "LinkedList.h"
#include <random>
int randomBetween(int a, int b)
{
    std::random_device rd;                       // obtain a random number from hardware
    std::mt19937 gen(rd());                      // seed the generator
    std::uniform_int_distribution<> distr(a, b); // define the range

    return distr(gen); // generate numbers
}

int main()
{
    LINKEDLIST::Linked_List<int> myList;
    BINARYTREE::BinaryTree<int> myBinaryTree;
    for (int i = 0; i != 40; i++)
    {
        int chosen_value = i;
        myList.insert(chosen_value);
    }
    myList.print_list(true);
    for (int i = myList.size() / 2 - 1; i >= 0; i--)
    {
        for (int i = myList.size() / 2 - 1; i >= 0; i--)
        {
            int current_index = i;
            int left_child = (current_index * 2) + 1;
            int right_child = (current_index * 2) + 2;
            int greatest_index = current_index;

            if (left_child < myList.size() && myList.get_node(left_child)->value > myList.get_node(greatest_index)->value)
            {
                greatest_index = left_child;
            }

            if (right_child < myList.size() && myList.get_node(right_child)->value > myList.get_node(greatest_index)->value)
            {
                greatest_index = right_child;
            }

            if (greatest_index != current_index)
            {
                myList.swap(current_index, greatest_index);
                i = greatest_index;
            }
        }
    }
    myList.print_list(true);

        // create a binary tree
    for (int current_index = 0; current_index <= (myList.size() / 2); current_index++)
    {
        int left_child = (current_index * 2) + 1;
        int right_child = (current_index * 2) + 2;
        if (left_child < myList.size())
        {
            myBinaryTree.insert(left_child);
        }
        if (right_child < myList.size())
        {
            myBinaryTree.insert(right_child);
        }
    }
    // std::cout << std::endl;
    myBinaryTree.output_tree();
    std::cout << std::endl;
    std::cout << "terminating process" << std::endl;
    return 0;
}
