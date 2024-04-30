#include "BinaryTree.h"
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
    using namespace BINARYTREE;
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
    //int oldsize = myBinaryTree.size();
    if (!myBinaryTree.iscomplete())
    {
        std::cout << "BINARY TREE IS NOT COMPLETE" << std::endl;
    }
    
    std::cout << "BINARY TREE IS COMPLETE" << std::endl;
    while (!myBinaryTree.isempty())
    {
        std::cout << myBinaryTree.peek();
        myBinaryTree.remove(myBinaryTree.peek());
    }
    std::cout << std::endl;
}