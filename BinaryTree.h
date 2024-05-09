#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "LinkedList.h"
#include <cstddef>

namespace BINARYTREE {

template <class datatype_valueA> struct BinaryTreeNode {
  BinaryTreeNode<datatype_valueA> *right = nullptr, *left = nullptr;
  datatype_valueA data;
  BinaryTreeNode(datatype_valueA value)
      : left(nullptr), right(nullptr), data(value) {}
  ~BinaryTreeNode() {
    if (right) {
      delete right;
      right = nullptr;
    }
    if (left) {
      delete left;
      left = nullptr;
    }
  }
};
template <class datatype_valueB> struct BinaryTree {

private:
  typedef datatype_valueB data;
  typedef BinaryTreeNode<data> Node;
  Node *head;

public:
  BinaryTree() : head(nullptr) {}
  // typedef BINARYTREE::CompleteBinaryTree<class datatype__valueB>
  // CompleteTree;
  //  CONST MEMBER FUNCTIONS

  size_t size() { return size_HELPER(head); }

  bool isempty() { return size() == 0; }

  bool iscomplete() const { return iscomplete(head); }

  bool isduplicate(data value) const { return isduplicate(head, value); }

  bool iscomplete() { return iscomplete_HELPER(head); }
  // MUTATOR MEMBER FUNCTION
  void insert(data value) { insert_HELPER(head, value); }
  void remove(data value) { remove_HELPER(head, value); }
  void remove() {
    // remove this most value
    if (isempty()) {
      return;
    }
    Node *current = this->head;
    while (current->right) {
      current = current->right;
    }
    delete current;
  }

  data peek() {
    if (isempty()) {
      return data();
    }
    return this->head->data;
  }

public:
  // MISC FUNCTIONS
  void output_tree() { output_tree_HELPER(head); }

private: // PRIVATE HELPER FUNCTIONS
  void remove_HELPER(Node *&root, data value) {
    if (root == nullptr) {
      return;
    }

    if (value < root->data) {
      remove_HELPER(root->left, value);
    } else if (value > root->data) {
      remove_HELPER(root->right, value);
    } else {
      if (!root->left && !root->right) {
        delete root;
        root = nullptr;
      } else if (root->left && !root->right) {
        Node *temp = root;
        root = root->left;
        delete temp;
      } else if (!root->left && root->right) {
        Node *temp = root;
        root = root->right;
        delete temp;
      } else {
        Node *temp = root->right;
        Node *parent = root;
        while (temp->left) {
          parent = temp;
          temp = temp->left;
          if (!temp) {
            break;
          }
        }
        root->data = temp->data;
        if (parent->left == temp) {
          parent->left = temp->right;
        } else {
          parent->right = temp->right;
        }
        delete temp;
      }
    }
  }

  void insert_HELPER(Node *&root, data value) {
    // Create a new node
    Node *newNode = new Node(value);

    // Special case: empty tree
    if (!root) {
      root = newNode;
      return;
    }

    Node *parent = root, *current = root;
    while (current) {
      parent = current;
      if (value < current->data) {
        current = current->left;
      } // else if (value >= currentNode->data) {
      else {
        current = current->right;
      }
    }
    if (value < parent->data) {
      parent->left = newNode;
    } else {
      parent->right = newNode;
    }
  }

  bool iscomplete_HELPER(Node *&root) {
    if (!root) {
      return true;
    }
    if (!root->left && !root->right) {
      return true;
    } else if (root->left && root->right) {
      return iscomplete_HELPER(root->left) && iscomplete_HELPER(root->right);
    } else {
      return false;
    }
    return false;
  }

  bool isduplicate_HELPER(Node *&root, data value) {
    if (!root) {
      return false;
    }
    if (root->data == value) {
      return true;
    }
    return isduplicate_HELPER(root->left, value) ||
           isduplicate_HELPER(root->right, value);
  }

  void output_tree_HELPER(const Node *root) {
    // outs the tree in the same order as deconstruction
    if (!root) {
      return;
    }
    output_tree_HELPER(root->left);

    output_tree_HELPER(root->right);
    std::cout << root->data << " ";
  }

  int size_HELPER(const Node *root) {
    if (!root) {
      return 0;
    }
    return size_HELPER(root->left) + size_HELPER(root->right) + 1;
  }

  // datatype_A &operator[](size_t index) { return Heap.get_node(index); }

public:
  ~BinaryTree() {
    delete head;
    head = nullptr;
  }
};

template <class datatype__valueC> struct CompleteBinaryTree {

  typedef datatype__valueC data;
  typedef BinaryTreeNode<data> Node;
  typedef LINKEDLIST::Linked_List<Node> Array;
  Array Values;

public:
  CompleteBinaryTree() : Values(Array()) {}

  explicit CompleteBinaryTree(BinaryTree<data> Tree) {
    LINKEDLIST::Linked_List<data> List;
    while (!Tree.isempty()) {
      List.insert(Tree.peek(), List.size());
      Tree.remove(Tree.peek());
    }
    std::cout << std::endl;
  }
  bool isempty() { return Values.isempty(); }

  size_t size() const { return static_cast<size_t>(Values.size()); }
  void insert(data value) { Values.insert(Node(value)); }

  void remove(size_t index = 0) {
    if (!this->isempty()) {
      Values.remove(index);
    }
  }

  data peak() { return Values[0]; }
  data operator[](const size_t index) {
    return Values.get_node(index)->value.data;
  }

public:
  ~CompleteBinaryTree() {
    // deallocate list
    while (!Values.isempty()) {
      Values.remove(0);
    }
  }
};

} // namespace BINARYTREE
#endif // BINARYTREE_H

// # private:
// #   void heapify(Heap &list, const priority idx) {
// #     priority max = idx, left = (idx * 2) + 1, right = left + 1;
// #
// #     if (left < list.size() && list[idx].priority < list[left].priority) {
// #       max = left;
// #     }
// #     if (right < list.size() && list[max].priority < list[right].priority)
// { #       max = right; #     }
// #
// #     if (max != idx) {
// #       std::cout << "SWAPPING " << list[idx].data << " WITH " <<
// list[max].data #                 << std::endl; #       list.swap(idx, max);
// #       heapify(list, max);
// #     }
// #   }

// #  void balance_tree() {
// #    LINKEDLIST::Linked_List<BinaryTreeNode<datatype_A> *> list;
// #    enqueue_all_nodes(head, list);
// #
// #    // Reheapify nodes
// #    for (int index = (list.size() / 2) - 1; index >= 0; index--) {
// #      LINKEDLIST::heapify(list, index);
// #    }
// #    // Output the list (for testing)
// #    std::cout << "TEST REHEAP: ";
// #    for (int index = 0; index < list.size(); index++) {
// #      std::cout << list.get_node(index)->value->data << " ";
// #    }
// #    std::cout << std::endl;
// #    // Relink nodes
// #    this->head = list.get_node(0)->value;
// #    list.remove(0);
// #    for (int index = 0; index < list.size() / 2; index++) {
// #      int left_child = (2 * index) + 1;
// #      int right_child = (2 * index) + 2;
// #      bool isrightvalid = right_child >= 0 && right_child < list.size();
// #      BinaryTreeNode<datatype_A> *current = list.get_node(index)->value;
// #
// #      // if (left_child < list.size()) {
// #      current->left = list.get_node(left_child)->value;
// #
// #      //}
// #      if (isrightvalid && right_child < list.size()) {
// #        current->right = list.get_node(right_child)->value;
// #      }
// #    }
// #    std::cout << "TREE HAS BEEN REBALANCED" << std::endl;
// #  }

// CREDIT TO JACKSON WU
// void printSpaces(int n) {
//   for (int i = 0; i < n; ++i)
//     cout << " ";
// }
//
// void printTree(TreeNode *root, int depth) {
//   if (root == nullptr) {
//     printSpaces(4 * depth);
//     cout << "- NULL" << endl;
//     return;
//   }
//
//   printTree(root->right, depth + 1);
//
//   printSpaces(4 * depth);
//   cout << "- " << root->val << endl;
//
//   printTree(root->left, depth + 1);
// }