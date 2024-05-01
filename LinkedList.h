#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

namespace LINKEDLIST {

template <class T> struct Linked_List {
private:
  template <class A> struct Node {
    Node<A> *next;
    size_t index;
    A value;
    Node(A value, size_t index) : next(nullptr), index(index), value(value) {}
    ~Node() {
      delete next;
      next = nullptr;
    }
  };

  Node<T> *head;

public:
  Linked_List() : head(nullptr) {}

private:
  // PRIVATE HELPER FUNCTIONS

  // index is only valid if index >= 0 && index < size()
  bool isindexvalid(size_t index) const { return index >= 0 && index < size(); }

  Node<T> *get_endpoint() {
    if (isempty()) {
      return head;
    }
    Node<T> *current = this->head;
    while (current->next) {
      current = current->next;
    }
    return current;
  }

public:
  Node<T> *get_node(size_t index) {
    if (index == size() - 1) {
      return this->get_endpoint();
    } else if (index == 0) {
      return this->head;
    } else {
      // traverse to the node
      Node<T> *current = this->head;
      while (current->index != index) {
        current = current->next;
      }
      return current;
    }
  }

public:
  // CONST MEMBER FUNCTIONS
  size_t size() const {
    Node<T> *current = this->head;
    size_t counter = 0;
    while (current) {
      current = current->next;
      counter += 1;
    }
    return static_cast<size_t>(counter);
  }

  bool isempty() const { return this->head == 0; }

  // MISC HELPER FUNCTIONS

  void print_index(const size_t index, const bool includeWS) {
    if (!isindexvalid(index)) {
      return;
    }
    Node<T> *current = this->head;
    while (current->index != index) {
      current = current->next;
    }
    // current->value = value;
    if (!includeWS) {
      std::cout << current->value;
    } else {
      std::cout << current->value << " ";
    }
  }
  void print_list(const bool includeWS = false) {
    Node<T> *current = this->head;
    while (current) {

      if (includeWS) {
        std::cout << current->value << " ";
      } else {
        std::cout << current->value;
      }
      current = current->next;
    }
    std::cout << std::endl;
  }
  // MUTATOR MEMBER FUNCTIONS

  void insert(T value, size_t index) {
    if (!isindexvalid(index)) {
      return;
    }
    // traverse to index and overwite data present
    Node<T> *current = this->head;
    while (current->index != index) {
      current = current->next;
    }
    current->value = value;
  }

  void insert(T value) {
    if (this->isempty()) {
      this->head = new Node<T>(value, 0);
      return;
    }
    Node<T> *endpoint = get_endpoint();
    endpoint->next = new Node<T>(value, endpoint->index + 1);
  }

  void remove(size_t index = 0) {
    // there are 3 cases
    if (!isindexvalid(index) || isempty()) {
      return;
    }

    // if no parent (index = 0)
    if (index == 0) {
      Node<T> *old_head = this->head, *new_head = nullptr;
      if (old_head->next) {
        new_head = old_head->next;
        old_head->next = nullptr;
      }
      this->head = new_head;
      delete old_head;
    }
    // if no child
    else if (index == this->size() - 1) {
      // traverse to the second last Node
      Node<T> *current = this->head, *current_prev = nullptr;
      while (current->next) {
        current_prev = current;
        current = current->next;
      }
      if (current_prev) {
        current_prev->next = nullptr;
      }
      delete current;
      return;
    } else {
      // if parent and child at index
      for (int current = index; current < size() - 1; current++) {
        Node<T> *NodeA = this->get_node(current),
                *NodeB = this->get_node(current + 1);
        NodeA->value = NodeB->value;
      }
      this->remove(this->size() - 1);
    }
  }

  void swap(size_t left_index, size_t right_index) {
    if (!this->isindexvalid(left_index) || !this->isindexvalid(right_index)) {
      return;
    }
    Node<T> *left_node = this->get_node(left_index),
            *right_node = this->get_node(right_index);
    T temp_value = left_node->value;
    left_node->value = right_node->value;
    right_node->value = temp_value;
  }

  ~Linked_List() { delete this->head; }
};


} // namespace LINKEDLIST

#endif // LINKED_LIST_H
