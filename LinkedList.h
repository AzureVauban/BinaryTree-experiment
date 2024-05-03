#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <cstdio>
#include <iostream>

namespace LINKEDLIST {

template <class datatype_K> struct LinkedListNode {
  LinkedListNode<datatype_K> *next;
  size_t index;
  datatype_K value;
  LinkedListNode(datatype_K value, size_t index)
      : next(nullptr), index(index), value(value) {}

  ~LinkedListNode() { // DELETION IS HANDLED BY THE LINKED LIST WRAPPER CLASS
  }
};
template <class datatype_T> struct Linked_List {
private:
  typedef datatype_T Data;
  typedef LinkedListNode<Data> Node;
  Node *head;
  size_t current_size;

public:
  Linked_List() : head(nullptr), current_size(0) {}

private:
  // PRIVATE HELPER FUNCTIONS
  void reindex() {
    Node *current = head;
    size_t index = 0;
    while (current) {
      current->index = index;
      current = current->next;
      index += 1;
    }
  }
  // index is only valid if index >= 0 && index < size()
  bool isindexvalid(size_t index) const {
    // const size_t n = size();
    return index >= 0 && index < current_size;
  }

  bool isinvalidindex(const size_t index) const {
    return index < 0 && index >= current_size;
  }
  Node *get_endpoint() {
    if (isempty()) {
      return head;
    }
    Node *current = head;
    while (current->next) {
      current = current->next;
    }
    return current;
  }

public:
  // CONST MEMBER FUNCTIONS

  Node *get_node(size_t index) {
    if (isinvalidindex(index)) {
      return nullptr;
    }
    if (index == size() - 1) {
      return get_endpoint();
    } else if (index == 0) {
      return head;
    } else {
      // traverse to the node
      Node *current = head;
      while (current->index != index) {
        current = current->next;
      }
      return current;
    }
  }
  size_t size() const { return static_cast<size_t>(current_size); }
  bool isempty() const { return current_size == 0; }

  bool in(const Data value) const {
    if (isempty()) {
      return false;
    }
    Node *current = head;
    while (current) {
      if (current->value == value) {
        return true;
      }
      current = current->next;
    }
    return false;
  }
  // MISC HELPER FUNCTIONS

  void print_list(const bool includeWS = false) {
    Node *current = head;
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

  void reverse() {
    size_t n = size();
    if (n > 1) {
      for (size_t i = 0; i < n / 2; i++) {
        swap(i, n - 1 - i);
      }
    }
  }

  void insert(Data value, size_t index) {
    if (isempty() && index == 0) {
      head = new Node(value, 0);
      current_size += 1;
    }
    if (isinvalidindex(index)) {
      return;
    }
    // add dummy value to end
    insert(get_endpoint()->value);
    // shift values at desired index to the right
    Node *current = get_node(index);
    while (current->next) {
      current->value = current->next->value;
      current = current->next;
    }
    // overwrite value at desired index
    current = get_node(index);
    current->value = value;
    current_size += 1;
  }

  void insert(Data value) {
    if (isempty()) {
      head = new Node(value, 0);
      current_size += 1;
      return;
    }
    Node *endpoint = get_endpoint();
    endpoint->next = new Node(value, endpoint->index + 1);
    current_size += 1;
  }

  void remove(size_t index = 0) {
    // there are 3 cases
    if (isempty()) {
      return;
    }
    if (isinvalidindex(index) && index != 0) {
      return;
    }

    size_t n = size();

    if (index == 0 && current_size == 1) {
      delete head;
      head = nullptr;
      current_size = 0;
    } else if (index == 0) { // if no parent (index = 0)
      Node *old_head = head, *new_head = nullptr;
      if (old_head->next) {
        new_head = old_head->next;
        old_head->next = nullptr;
      }
      head = new_head;
      current_size -= 1;
      delete old_head;
      reindex();
      return;
    } // if no child
    else if (index == n - 1) {
      // traverse to the second last Node
      Node *current = head, *current_prev = nullptr;
      while (current->next) {
        current_prev = current;
        current = current->next;
      }
      if (current_prev) {
        current_prev->next = nullptr;
      }
      current_size -= 1;
      delete current;
      reindex();
      return;
    }

    else {
      // if parent and child at index
      for (int current = index; current < n - 1; current++) {
        Node *NodeA = get_node(current), *NodeB = get_node(current + 1);
        NodeA->value = NodeB->value;
      }
      remove(size() - 1);
      reindex();
    }
  }

  void swap(size_t left_index, size_t right_index) {
    if (isinvalidindex(left_index) || isinvalidindex(right_index)) {
      return;
    }
    Node *left_node = get_node(left_index), *right_node = get_node(right_index);
    datatype_T temp_value = left_node->value;
    left_node->value = right_node->value;
    right_node->value = temp_value;
  }

  void clear() {
    const size_t sizecopy = size();
    for (int i = 0; i < sizecopy; i++) {
      remove();
    }
  }

  // OVERLOAD OPERATORS

  Data &operator[](size_t index) { return this->get_node(index)->value; }

  template <class Data>
  LINKEDLIST::Linked_List<Data> &
  operator=(LINKEDLIST::Linked_List<Data> &Source2) {
    clear(); // Clear the current list
    for (int i = 0; i < Source2.size(); i++) {
      insert(Source2[i]); // Insert elements from Source2 into the current list
    }
    return *this; // Return the current list
  }

  ~Linked_List() { clear(); }
};

template <class Data> Linked_List<Data> Copy(Linked_List<Data> &Source) {
  Linked_List<Data> Copied;
  size_t n = Source.size();
  for (size_t index = 0; index != n; index++) {
    Copied.insert(Source.get_node(index)->value);
  }
  return Copied;
}

} // namespace LINKEDLIST

#endif // LINKED_LIST_H
