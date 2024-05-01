#include "BinaryTree.h"
#include "LinkedList.h"
// #include "Queue.h"
#include <random>

int randomBetween(int a, int b) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(a, b); // define the range

  return distr(gen); // generate numbers
}

int main() {
  BINARYTREE::BinaryTree<int> myBinaryTree;
  LINKEDLIST::Linked_List<int> myList;
  // create a binary tree
//@  for (int current_index = 0; current_index <= (myList.size() / 2);
//@       current_index++)
//@  // current_index++)
//@  {
//@    int left_child = (current_index * 2) + 1;
//@    int right_child = (current_index_ * 2) + 2;
//@    if (left_child < myList.size()) {
//@      myBinaryTree.insert(left_child);
//@    }
//@    if (right_child < myList.size()) {
//@      myBinaryTree.insert(right_child);
//@    }
//@  }
  while (myBinaryTree.size() != randomBetween(5, 100)) {
    myBinaryTree.insert(randomBetween(1, 100));
  }
  myBinaryTree.balance_tree();
  std::cout << "terminating process" << std::endl;
  return 0;
}
