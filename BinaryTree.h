#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "LinkedList.h"
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
  size_t binary_tree_size;

public:
  // CONST MEMBER FUNCTIONS
  BinaryTree() : head(nullptr), binary_tree_size(0) {}

  size_t size() const { return static_cast<size_t>(this->binary_tree_size); }

  bool isempty() const { return !this->head; }

  bool iscomplete() const { return this->iscomplete(this->head); }

  bool isduplicate(datatype_A value) const {
    return this->isduplicate(this->head, value);
  }

  bool iscomplete() { return this->iscomplete_HELPER(this->head); }
  // MUTATOR MEMBER FUNCTION
  void insert(datatype_A value) { this->insert_HELPER(this->head, value); }
  void remove(datatype_A value) {
    this->remove_HELPER(this->head, value);
    this->binary_tree_size -= 1;
  }

  // MISC FUNCTIONS
  void output_tree() { this->output_tree_HELPER(this->head); }


  void balance_tree() {
    LINKEDLIST::Linked_List<int> list;
    enqueue_all_nodes(head, list);
    std::cout << "BREAKPOINT\n";
//!    for (int index = 0; index < list.size(); index++) {
//!      BinaryTreeNode<datatype_A> &current = list.get_node(index)->value;
//!      current.left = nullptr;
//!      current.right = nullptr;
//!    }
    // reheap the binary tree
//!    std::cout << "PRE-HEAP: ";
//!    // recreate the binary tree
//!    this->head = temp.get_node(0)->value;
//!    // temp.remove();
//!    for (int index = 1; index <= (temp.size() / 2); index++) {
//!      // each node is guaranteed a left child
//!      int left_child = (index * 2) + 1;
//!      int right_child = (index * 2) + 2;
//!      if (left_child < temp.size()) {
//!        temp.get_node(index)->left = temp.get_node(left_child);
//!      }
//!      if (right_child < temp.size()) {
//!        temp.get_node(index)->right = temp.get_node(right_child);
//!      }
//!    }
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

    if (isempty()) {
      this->head = newNode;
      return;
    }

    if (value < root->data) {
      if (root->left == nullptr) {
        root->left = newNode;
      } else {
        insert_HELPER(root->left, value);
      }
    } else if (value > root->data) {
      if (root->right == nullptr) {
        root->right = newNode;
      } else {
        insert_HELPER(root->right, value);
      }
    }
  }

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

  

  void enqueue_all_nodes(BinaryTreeNode<datatype_A> *&root,
                    LINKEDLIST::Linked_List<datatype_A> &list) {

    if (!root) {
    enqueue_all_nodes(root->left, list);
    enqueue_all_nodes(root->right, list);
    }
  
  }

public:
  ~BinaryTree() {
    delete head;
    head = nullptr;
  }

  
};
} // namespace BINARYTREE
#endif // BINARYTREE_H
