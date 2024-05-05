#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <cstdio>
#include <functional>
#include <iostream>
#include <iterator>
#include <ostream>
#include <utility>

namespace LINKEDLIST {

template <class datatype_K> struct LinkedListNode {
  LinkedListNode<datatype_K> *next;
  std::size_t index;
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

  const Data &at(const size_t index) { return get_node(index)->value; }

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
    const size_t sizecopy = current_size;
    if (isempty()) {
      return;
    }
    for (int i = 0; i < sizecopy; i++) {
      remove();
    }
  }

  // OVERLOAD OPERATORS

  Data &operator[](size_t index) { return get_node(index)->value; }

  template <class Data>
  LINKEDLIST::Linked_List<Data> &
  operator=(const LINKEDLIST::Linked_List<Data> &Source) {
    clear(); // Clear the list instance
    for (int i = 0; i < Source.size(); i++) {
      insert(Source[i]); // Insert elements from Source2 into the current list
    }
    return *this; // Return the current list
  }

  typedef Linked_List<datatype_T> Array;
  friend std::ostream &operator<<(std::ostream &os, const Array &list) {
    os << '[';
    Node *current = list.head;
    while (current) {
      if (!current->next) {
        os << current->value << "";
      } else {
        os << current->value << ", ";
      }
      current = current->next;
    }
    os << ']';
    return os;
  }

  ~Linked_List() { clear(); }
};

template <class Data> Linked_List<Data> Copy(Linked_List<Data> &Source) {
  Linked_List<Data> Copied;
  size_t n = Source.size();
  for (size_t index = 0; index < n; index++) {
    Copied.insert(Source.get_node(index)->value);
  }
  return Copied;
}

template <class Data>
Linked_List<Data> operator+(Linked_List<Data> &Left, Linked_List<Data> &Right) {
  Linked_List<Data> Array;
  for (size_t index = 0; index < Left.size(); index++) {
    Array.insert(Left[index]);
  }
  for (size_t index = 0; index < Right.size(); index++) {
    Array.insert(Right[index]);
  }
  return Array;
}

template <class Data>
Linked_List<Data> operator+=(Linked_List<Data> &Left,
                             Linked_List<Data> &Right) {
  for (size_t index = 0; index < Right.size(); index++) {
    Left.insert(Right[index]);
  }
  return Left;
}

} // namespace LINKEDLIST

namespace HASHMAP {

// complete binary tree of Buckets, each Bucket is a Linked List corresponding
// to a key
template <class DataType_A, class DataType_B>
struct HashMap { // THINK VENDING MACHINE
  typedef DataType_A Key;
  typedef DataType_B Value;
  typedef size_t Index;
  static const size_t DEFAULT_CAPACITY = 10;
  // DECLARATION: NAMESPACE::Hashmap<KEY_DATATYPE,VALUE_DATATYPE>VARNAME;
  // STD::HashMap<studentID,studentname>StudentsDatabase;

private:
  template <class Key, class Value> struct Pair {
    Key *key;
    Value *Bucket;

  public:
    explicit Pair<Key, Value>(Key *key = nullptr, Value *v = nullptr)
        : key(key), Bucket(v) {}

    typedef Pair<Key, Value> P;
    typedef std::ostream os;
    friend os &operator<<(os &output, const P &pair) {
      output << "{";
      if (!pair.key) { // print key
        output << "0x0";
      } else {
        output << *pair.key;
      }
      output << ":";
      if (!pair.Bucket) { // print bucket
        output << "0x0";
      } else {
        output << *pair.Bucket;
      }
      output << "}";
      return output;
    }
    bool empty_bucket() const { return !Bucket; }
    bool empty_key() const { return !key; }
    bool empty_keyvalue() const { return empty_key() & empty_bucket(); }
    bool iskey(Key _key) const {
      if (empty_key()) {
        return false;
      }
      return &_key == key;
    }
    bool const isvalue(Value v) {
      if (!Bucket) {
        return false;
      }
      return true;
    }
    ~Pair() {}
  };

  typedef Pair<Key, Value> MapElement;
  typedef LINKEDLIST::Linked_List<MapElement> Map;
  size_t current_capacity;
  float load_factor;
  Map AssociativeArray;

public:
  size_t current_size;
  explicit HashMap<Key, Value>(size_t inital_capacity = DEFAULT_CAPACITY)
      : AssociativeArray(Map()), load_factor(0),
        current_capacity(inital_capacity), current_size(0) {
    for (Index i = 0; i < inital_capacity; i++) {
      AssociativeArray.insert(MapElement(nullptr, nullptr));
    }
  }

  // CONST MEMBER FUNCTIONS
  //?  bool value_exists(const Data &value) const {
  //?    for (Index i = 0; i < AssociativeArray.size(); i++) {
  //?      if (value == AssociativeArray[i].value) {
  //?        return true;
  //?      }
  //?    }
  //?    return false;
  //?  }

  bool key_exists(const Key key) {
    if (isempty()) {
      return false;
    }
    // for (Index i = 0; i < AssociativeArray.size(); i++) {
    //
    //   if (AssociativeArray[i].iskey(key)) {
    //     return true;
    //   }
    // }
    // return false;
    return true;
  }
  bool value_exists(const Value value) {
    if (isempty()) {
      return false;
    }
    // parse through the Map's List
    for (Index i = 0; i < AssociativeArray.size(); i++) {
      MapElement &temp = AssociativeArray[i];
      bool valueispresent = temp.isvalue(value);
      if (valueispresent) {
        return true;
      }
    }
    return false;
  }
  bool isempty() const { return current_size == 0; }

  bool full() { return false; }

  void size() {
    size_t counter = 0;
    for (Index i = 0; i < AssociativeArray.size(); i++) {
      MapElement stored_value = AssociativeArray[i];
      // std::cout << stored_value << std::endl;
      if (!stored_value.empty_keyvalue()) {
        counter += 1;
      }
    }
    current_size = counter;
  }
  Key get_key(const MapElement value) { Key(); }
  MapElement get_value(const Key key) { return MapElement(); }

private:
  // HELPER FUNCTIONS

  float calc_load_factor() { return 0.00; } // load factor = capacity / used
  float max_load_factor() { return 1.00; }
  Key Hash(Value value) const { return Key(); }
  Key Rehash(Index index) { Key(); }

public:
  // MUTATOR MEMBER FUNCTIONS

  void resize(size_t newcapacity) {}
  void insert(const Key key, Value value) {
    // k = KEY EXISTS, v = VALUE EXIST
    // (k && v) // do nothing
    // (k && !v) // overwrite value at key
    // (!k && v) // do nothing
    // (!k && !v) // do insert(k,v)
    const bool kPresent = key_exists(key), vPresent = value_exists(value);
  }
  void remove(const Key key) {}
  void clear() {}

  // OVERLOADED OPERATORS

  // void operator=(Map &Source) {}
  MapElement operator[](const Key key) {}

  typedef std::ostream os;
  friend os &operator<<(os &output, const HashMap<Key, Value> &Map) {
    //   Pair<Key, Value>(Key &key, Value *v = nullptr) : key(key), Bucket(v) {}
    output << "{";
    LINKEDLIST::Linked_List<MapElement> map_value = Map.AssociativeArray;
    for (Index i = 0; i < Map.current_capacity; i++) {
      //! PASSING KEY BY REFERENCE IN PAIR MAKES IT HARDER TO PRINT
      MapElement NEEDNAME1 = map_value[i];
      output << "{}";
    }
    output << "}";
    return output;
  }

  ~HashMap() {
    std::cout << "DESTORYING HASH MAP\n";
  }
};
} // namespace HASHMAP
#endif // LINKED_LIST_H
