#include "BinaryTree.h"
#include "LinkedList.h"
#include <random>

int randomBetween(int a, int b) {
  std::random_device rd;  // obtain a random number from hardware
  std::mt19937 gen(rd()); // seed the generator
  std::uniform_int_distribution<> distr(a, b); // define the range

  return distr(gen); // generate numbers
}

void binarytree_test() {
  BINARYTREE::BinaryTree<int> myBinaryTree;
  for (int i = 0; i != 5; i++) {
    int chosen_value = randomBetween(0, 100);
    // std::cout << chosen_value << std::endl;
    myBinaryTree.insert(chosen_value);
    // std::cout << i << std::endl;
  }
  // std::cout << "SIZE: " << myBinaryTree.size() << std::endl;
  myBinaryTree.output_tree();
  std::cout << std::endl;
  // myBinaryTree.balance_tree();
  // myBinaryTree.output_tree();
  std::cout << std::endl;
}
int main() {
  LINKEDLIST::Linked_List<int> mynums;
  for (int i = 0; i < 10; i++) {
    std::cout << i << std::endl;
    mynums.insert(i);
  }
  for (int i = mynums.size() - 1; i >= 0; i--) {
    std::cout << mynums[i] << std::endl;
  }
  std::cout << "terminating process" << std::endl;
  return 0;
}
