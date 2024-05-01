#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "LinkedList.h"
#include <cstddef>
// #include "Queue.h"

namespace BINARYTREE {
template <class datatype_A> struct BinaryTree {
private:
  template <class datatype_B> struct BinaryTreeNode {
    BinaryTreeNode<datatype_B> *right = nullptr, *left = nullptr;
    datatype_B data;
    BinaryTreeNode(datatype_B value)
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

private:
  BinaryTreeNode<datatype_A> *head;

public:
  // CONST MEMBER FUNCTIONS
  BinaryTree() : head(nullptr) {}

  size_t size() { return this->size_HELPER(head); }

  bool isempty() const { return !this->head; }

  bool iscomplete() const { return this->iscomplete(this->head); }

  bool isduplicate(datatype_A value) const {
    return this->isduplicate(this->head, value);
  }

  bool iscomplete() { return this->iscomplete_HELPER(this->head); }
  // MUTATOR MEMBER FUNCTION
  void insert(datatype_A value) { this->insert_HELPER(this->head, value); }
  void remove(datatype_A value) { this->remove_HELPER(this->head, value); }

private:
  void enqueue_all_nodes(
      BinaryTreeNode<datatype_A> *root,
      LINKEDLIST::Linked_List<BinaryTreeNode<datatype_A> *> &list) {

    if (root) {
      list.insert(root);
    }
    if (root->left) {
      enqueue_all_nodes(root->left, list);
    }
    if (root->right) {
      enqueue_all_nodes(root->right, list);
    }
  }

public:
  // MISC FUNCTIONS
  void output_tree() { this->output_tree_HELPER(this->head); }

  void balance_tree() {
    LINKEDLIST::Linked_List<BinaryTreeNode<datatype_A> *> list;
    // enqueue all nodes
    enqueue_all_nodes(head, list);
    for (int index = 0; index < list.size(); index++) {
      BinaryTreeNode<datatype_A> *current = list.get_node(index)->value;
      current->left = nullptr;
      current->right = nullptr;
    }
    // reheapify nodes
    for (int index = (size() / 2) - 1; index >= 0; index--) {
        this->heapify(list, index);
    }
    // OUTPUT LIST
    std::cout << "TEST REHEAP: ";
    for (int index = 0; index < list.size(); index++) {
      std::cout << list.get_node(index)->value->data << " ";
    }
    std::cout << std::endl;
    // relink nodes
    for (int index = 0; index <= (list.size() / 2) - 1; index++) {
      int left_child = (2 * index) + 1;
      int right_child = (2 * index) + 2;
    }
    std::cout << "BREAKPOINT\n";
  }

private: // PRIVATE HELPER FUNCTIONS
  void remove_HELPER(BinaryTreeNode<datatype_A> *&root, datatype_A value) {
    if (!root) {

      if (value < root->data) {
        remove_HELPER(root->left, value);
      } else if (value > root->data) {
        remove_HELPER(root->right, value);
      } else {
        if (!root->left && !root->right) {
          delete root;
          root = nullptr;
        } else if (root->left && !root->right) {
          BinaryTreeNode<datatype_A> *temp = root;
          root = root->left;
          temp->left = nullptr;
          delete temp;
        } else if (!root->left && root->right) {
          BinaryTreeNode<datatype_A> *temp = root;
          root = root->right;
          temp->right = nullptr;
          delete temp;
        } else {
          BinaryTreeNode<datatype_A> *temp = root->right;
          while (temp && temp->left) {
            temp = temp->left;
          }
          root->data = temp->data;
          remove_HELPER(root->right, temp->data);
        }
      }
    }
  }

  void insert_HELPER(BinaryTreeNode<datatype_A> *&root, datatype_A value) {
    // Create a new node
    BinaryTreeNode<datatype_A> *newNode = new BinaryTreeNode<datatype_A>(value);

    // Special case: empty tree
    if (!root) {
      root = newNode;
      return;
    }

    BinaryTreeNode<datatype_A> *parentNode = root, *currentNode = root;
    while (currentNode) {
      parentNode = currentNode;
      if (value < currentNode->data) {
        currentNode = currentNode->left;
      } // else if (value >= currentNode->data) {
      else {
        currentNode = currentNode->right;
      }
    }
    if (value < parentNode->data) {
      parentNode->left = newNode;
    } else {
      parentNode->right = newNode;
    }
  }
  //}

  bool iscomplete_HELPER(BinaryTreeNode<datatype_A> *&root) {
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

  bool isduplicate_HELPER(BinaryTreeNode<datatype_A> *&root, datatype_A value) {
    if (!root) {
      return false;
    }
    if (root->data == value) {
      return true;
    }
    return isduplicate_HELPER(root->left, value) ||
           isduplicate_HELPER(root->right, value);
  }

  void output_tree_HELPER(BinaryTreeNode<datatype_A> *&root) {
    // outs the tree in the same order as deconstruction
    if (root) {
      output_tree_HELPER(root->right);
      output_tree_HELPER(root->left);
      std::cout << root->data << " ";
    }
  }

  size_t size_HELPER(BinaryTreeNode<datatype_A> *&root) {
    if (!root) {
      return 0;
    }
    return static_cast<size_t>(size_HELPER(root->left) +
                               size_HELPER(root->right) + 1);
  }
  void heapify(LINKEDLIST::Linked_List<BinaryTreeNode<datatype_A> *> list,
               size_t index) {
    int greatest = index, left = (2 * index) + 1, right = (2 * index) + 2;

    // compare larger to children indicies
    if (left < list.size() &&
        list.get_node(left)->value->data > list.get_node(right)->value->data) {
      greatest = left;
    }
    if (right < list.size() &&
        list.get_node(right)->value->data > list.get_node(left)->value->data) {
      greatest = right;
    }

    // if largest is not root
    if (greatest != index) {
      list.swap(index, greatest);
    }
    heapify(list, index);
  }

public:
  ~BinaryTree() {
    delete head;
    head = nullptr;
  }
};
} // namespace BINARYTREE
#endif // BINARYTREE_H
