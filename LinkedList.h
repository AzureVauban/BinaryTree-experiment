#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <iostream>
#include <regex>

namespace LINKEDLIST {

template <class datatype_K> struct LinkedListNode {
  LinkedListNode<datatype_K> *next;
  size_t index;
  datatype_K value;
  LinkedListNode(datatype_K value, size_t index)
      : next(nullptr), index(index), value(value) {}

  ~LinkedListNode() {
    delete next;
    next = nullptr;
  }
};
template <class datatype_T> struct Linked_List {
private:
  typedef datatype_T Data;
  typedef LinkedListNode<Data> Array;
  Array *head;

public:
  Linked_List() : head(nullptr) {}

private:
  // PRIVATE HELPER FUNCTIONS
  void reindex() {
    Array *current = head;
    size_t index = 0;
    while (current) {
      current->index = index;
      current = current->next;
      index += 1;
    }
  }
  // index is only valid if index >= 0 && index < size()
  bool isindexvalid(size_t index) const { return index >= 0 && index < size(); }

  Array *get_endpoint() {
    if (isempty()) {
      return head;
    }
    Array *current = head;
    while (current->next) {
      current = current->next;
    }
    return current;
  }

public:
  Array *get_node(size_t index) {
    if (!isindexvalid(index)) {
      return nullptr;
    }
    if (index == size() - 1) {
      return get_endpoint();
    } else if (index == 0) {
      return head;
    } else {
      // traverse to the node
      Array *current = head;
      while (current->index != index) {
        current = current->next;
      }
      return current;
    }
  }

public:
  // CONST MEMBER FUNCTIONS
  size_t size() const {
    if (!head) {
      return 0;
    }
    Array *current = head;
    size_t counter = 0;
    while (current) {
      current = current->next;
      counter += 1;
    }
    return static_cast<size_t>(counter);
  }

  bool isempty() const { return head == 0; }

  bool in(const Data value) const {
    if (isempty()) {
      return false;
    }
    Array *current = head;
    while (current) {
      if (current->value == value) {
        return true;
      }
      current = current->next;
    }
    return false;
  }
  // MISC HELPER FUNCTIONS

  void print_index(const size_t index, const bool includeWS) {
    if (!isindexvalid(index)) {
      return;
    }
    Array *current = head;
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
    Array *current = head;
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

  void insert(Data value, size_t index) {
    if (isempty() && index == 0) {
      head = new Array(value, 0);
    }
    if (!isindexvalid(index)) {
      return;
    }
    // add dummy value to end
    insert(get_endpoint()->value);
    // shift values at desired index to the right
    Array *current = get_node(index);
    while (current->next) {
      current->value = current->next->value;
      current = current->next;
    }
    // overwrite value at desired index
    current = get_node(index);
    current->value = value;
  }

  void insert(Data value) {
    if (isempty()) {
      head = new Array(value, 0);
      return;
    }
    Array *endpoint = get_endpoint();
    endpoint->next = new Array(value, endpoint->index + 1);
  }

  void remove(size_t index = 0) {
    // there are 3 cases
    if (!isindexvalid(index) || isempty()) {
      return;
    }

    // if no parent (index = 0)
    if (index == 0) {
      Array *old_head = head, *new_head = nullptr;
      if (old_head->next) {
        new_head = old_head->next;
        old_head->next = nullptr;
      }
      head = new_head;
      delete old_head;
      reindex();
    }
    // if no child
    else if (index == size() - 1) {
      // traverse to the second last Node
      Array *current = head, *current_prev = nullptr;
      while (current->next) {
        current_prev = current;
        current = current->next;
      }
      if (current_prev) {
        current_prev->next = nullptr;
      }
      delete current;
      reindex();
      return;
    } else {
      // if parent and child at index
      for (int current = index; current < size() - 1; current++) {
        Array *NodeA = get_node(current), *NodeB = get_node(current + 1);
        NodeA->value = NodeB->value;
      }
      remove(size() - 1);
      reindex();
    }
  }
  Data &operator[](size_t index) { return this->get_node(index)->value; }

  Array operator=(Array &Source) {
    if (Source == this) {
      return *this;
    }
    for (int i = 0; i < Source.size(); i++) {
      insert(Source[i], i);
    }
    // resize
    //    while (size() != Source.size()) {
    //      remove(size() - 1);
    //    }
    return *this;
  }
  Array operator+(const Array &Source) {
    // concatenate two lists together and return the result
    for (int i = 0; i < Source.size(); i++) {
      insert(Source[i], size() - 1);
    }
    return *this; // NOT IMPLEMENTED
  }
  Array operator+=(const Array &Source) {
    // Append data of right onto this
    for (int i = 0; i < Source.size(); i++) {
      insert(Source[i], i);
    }
    // resize
    while (size() != Source.size()) {
      remove(size() - 1);
    }
    return *this; // NOT IMPLEMENTED
  }
  Array operator-(const Array &Source) {
    // Return an instance of a List that has all the elements in Source but not
    // in this instance
    for (int i = 0; i < Source.size(); i++) {
      insert(Source[i], i);
    }
    // resize
    while (size() != Source.size()) {
      remove(size() - 1);
    }
    return *this; // NOT IMPLEMENTED
  }
  Array operator-=(const Array &Source) {
    // Remove any values present in Source that are also present in this
    // instance
    for (int i = 0; i < Source.size(); i++) {
      insert(Source[i], i);
    }
    // resize
    while (size() != Source.size()) {
      remove(size() - 1);
    }
    return *this; // NOT IMPLEMENTED
  }

  void swap(size_t left_index, size_t right_index) {
    if (!isindexvalid(left_index) || !isindexvalid(right_index)) {
      return;
    }
    Array *left_node = get_node(left_index),
          *right_node = get_node(right_index);
    datatype_T temp_value = left_node->value;
    left_node->value = right_node->value;
    right_node->value = temp_value;
  }
  void clear() {
    while (!isempty()) {
      remove();
    }
  }

  void reverse() {
    // reverses the current list, DOES not return reversed list
    if (size() > 1) {
      for (size_t index = 0; index < size(); index++) {
        for (size_t index2 = 0; index2 < size(); index2++) {
          swap(index2, index2);
        }
      }
    }
  }

  ~Linked_List() {
    Array *current = head;
    while (current != nullptr) {
      Array *nodeToDelete = current;
      current = current->next;
      nodeToDelete->next = nullptr;
      delete nodeToDelete;
    }
  }
};

} // namespace LINKEDLIST

#endif // LINKED_LIST_H
