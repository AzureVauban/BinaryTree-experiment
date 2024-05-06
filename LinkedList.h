#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <cstdio>
#include <functional>
#include <iostream>
#include <istream>
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

  // Re-indexes the nodes in the list.
  //
  // Pre-condition: None
  //
  // Post-condition: All nodes in the list have been re-indexed in order from 0
  // to size() - 1.
  void reindex() {
    Node *current = head;
    size_t index = 0;
    while (current) {
      current->index = index;
      current = current->next;
      index += 1;
    }
  }
  // Checks if the given index is valid.
  //
  // Pre-condition: None
  //
  // Post-condition: Returns true if the index is valid (i.e., it is greater
  // than or equal to 0 and less than the current size of the list), and false
  // otherwise.
  bool isindexvalid(size_t index) const {
    // index is only valid if index >= 0 && index < size()
    return index >= 0 && index < current_size;
  }

  // Checks if the given index is invalid.
  //
  // Pre-condition: None
  //
  // Post-condition: Returns true if the index is invalid (i.e., it is less than
  // 0 or greater than or equal to the current size of the list), and false
  // otherwise.
  bool isinvalidindex(const size_t index) const {
    return index < 0 && index >= current_size;
  }

  // Gets the last node in the list.
  //
  // Pre-condition: None
  //
  // Post-condition: Returns a pointer to the last node in the list. If the list
  // is empty, returns a pointer to the head of the list.
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

  // Gets the value at the given index.
  //
  // Pre-condition: The given index is valid.
  //
  // Post-condition: Returns the value at the given index.
  const Data &at(const size_t index) const { return get_node(index)->value; }

  // Gets the node at the given index.
  //
  // Pre-condition: The given index is valid.
  //
  // Post-condition: Returns a pointer to the node at the given index. If the
  // index is invalid, returns nullptr.
  Node *get_node(size_t index) const {
    if (isinvalidindex(index)) {
      return nullptr;
    }
    if (index == size() - 1) {
      Node *current = head;
      while (current->next) {
        current = current->next;
      }
      return current;
      // return get_endpoint();
    } else if (index == 0) {
      return head;
    } else {
      // traverse to the node
      Node *current = head;
      while (current->index < index) {
        current = current->next;
      }
      return current;
    }
  }
  // Gets the current size of the list.
  //
  // Pre-condition: None
  //
  // Post-condition: Returns the current size of the list.
  size_t size() const { return static_cast<size_t>(current_size); }

  // Checks if the list is empty.
  //
  // Pre-condition: None
  //
  // Post-condition: Returns true if the list is empty, and false otherwise.
  bool isempty() const { return current_size == 0; }

  // Checks if the given value is in the list.
  //
  // Pre-condition: None
  //
  // Post-condition: Returns true if the given value is in the list, and false
  // otherwise.
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
  // MUTATOR MEMBER FUNCTIONS

  // Reverses the order of the nodes in the list.
  //
  // Pre-condition: None
  //
  // Post-condition: The order of the nodes in the list has been reversed.
  void reverse() {
    size_t n = size();
    if (n > 1) {
      for (size_t i = 0; i < n / 2; i++) {
        swap(i, n - 1 - i);
      }
    }
  }

  // Inserts a new node with the given value at the given index.
  //
  // Pre-condition: The given index is valid.
  //
  // Post-condition: A new node with the given value has been inserted at the
  // given index. If the index is invalid, no node is inserted.
  void insert(Data value, const size_t index) {
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

  // Inserts a new node with the given value at the end of the list.
  //
  // Pre-condition: None
  //
  // Post-condition: A new node with the given value has been inserted at the
  // end of the list.
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

  // Removes the node at the given index.
  //
  // Pre-condition: The given index is valid.
  //
  // Post-condition: The node at the given index has been removed. If the index
  // is invalid, no node is removed.
  void remove(const size_t index = 0) {
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
    } else if (index == n - 1) {
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
        // if (current == 0) { break; }
        Node *NodeA = get_node(current), *NodeB = get_node(current + 1);
        NodeA->value = NodeB->value;
      }
      remove(size() - 1);
      reindex();
    }
  }

  // Swaps the values of the nodes at the given indices.
  //
  // Pre-condition: The given indices are valid.
  //
  // Post-condition: The values of the nodes at the given indices have been
  // swapped. If either index is invalid, no values are swapped.
  void swap(const size_t left_index, const size_t right_index) {
    if (isinvalidindex(left_index) || isinvalidindex(right_index)) {
      return;
    }
    Node *left_node = get_node(left_index), *right_node = get_node(right_index);
    datatype_T temp_value = left_node->value;
    left_node->value = right_node->value;
    right_node->value = temp_value;
  }

  // Removes all nodes from the list.
  //
  // Pre-condition: None
  //
  // Post-condition: All nodes have been removed from the list.
  void clear() {
    // const size_t sizecopy = current_size;
    if (isempty()) {
      return;
    }
    for (size_t i = current_size; i > 0; i--) {
      remove();
    }
  }

  // OVERLOAD OPERATORS

  // Accesses the value at the given index.
  //
  // Pre-condition: The given index is valid.
  //
  // Post-condition: Returns a reference to the value at the given index. If the
  // index is invalid, the behavior is undefined.
  Data &operator[](const size_t index) { return get_node(index)->value; }

  typedef LINKEDLIST::Linked_List<Data> List;
  // Assigns the values from the source list to the current list.
  //
  // Pre-condition: None
  //
  // Post-condition: The current list has been cleared and then filled with
  // the values from the source list. Returns a reference to the current
  // list.
  List &operator=(const List &Source) {
    clear(); // Clear the list instance
    for (int i = 0; i < Source.size(); i++) {
      insert(Source[i]); // Insert elements from Source2 into the current list
    }
    return *this; // Return the current list
  }

  // Prints the list to the given output stream.
  //
  // Pre-condition: None
  //
  // Post-condition: The values in the list have been printed to the given
  // output stream in the format "[value1, value2, ...]". Returns the output
  // stream.
  friend std::ostream &operator<<(std::ostream &os, const List &list) {
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

  // Concatenates the given list to the current list and returns the current
  // list.
  //
  // Pre-condition: None
  //
  // Post-condition: The elements of the given list have been inserted at the
  // end of the current list. The current list is returned. The given list is
  // not modified.
  List operator+(const List &Right) {
    for (size_t index = 0; index < Right.size(); index++) {
      insert(Right[index]);
    }
    return *this;
  }

  // Appends the elements of the given list to the current list and returns the
  // current list.
  //
  // Pre-condition: None
  //
  // Post-condition: The elements of the given list have been inserted at the
  // end of the current list. The current list is returned. The given list is
  // not modified.
  List operator+=(List &Right) {
    // append values of list
    for (size_t index = 0; index < Right.size(); index++) {
      insert(Right[index]);
    }
    return *this;
  }
  ~Linked_List() { clear(); }
};

template <class Data> Linked_List<Data> Copy(const Linked_List<Data> &Source) {
  Linked_List<Data> Copied;
  size_t n = Source.size();
  for (size_t index = 0; index < n; index++) {
    Copied.insert(Source.get_node(index)->value);
  }
  return Copied;
}

} // namespace LINKEDLIST
namespace ASSOCIATIVEARRAY {

template <class DataType_A, class DataType_B> struct AssociativeArray {
  typedef DataType_A Key;
  typedef DataType_B Value;
  typedef size_t Index;

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

  Map Table;

public:
  static const size_t DEFAULT_CAPACITY = 0;
  const size_t MAX_SIZE;
  explicit AssociativeArray(size_t inital_size = DEFAULT_CAPACITY,
                            size_t max_size = 50)
      : Table(Map()), MAX_SIZE(max_size) {
    for (Index i = 0; i < inital_size; i++) {
      Table.insert(MapElement());
    }
  }
  // CONST MEMBER FUNCTIONS

  // current number of key-value pairs
  //
  // Pre-condition: None
  //
  // Post-condition: Returns the current number of key-value pairs in the table,
  // which is the count of all pairs, exlcuding non-null pairs.
  size_t size() const {
    // return how many non-empty pairs are in the list
    size_t counter = 0;
    for (Index i = 0; i < capacity(); i++) {
      if (!Table.at(i).empty_keyvalue()) {
        counter += 1;
      }
    }
    return counter;
  }

  // current size of the table (the table includes nullable pairs representing
  // {key:value} mappings)
  //
  // Pre-condition: None
  //
  // Post-condition: Returns the current size of the table, which is the number
  // of non-null pairs in the table
  size_t capacity() const { return Table.size(); }

  // Checks if a key exists in the table
  //
  // Pre-condition: The key is a valid Key type
  //
  // Post-condition: Returns true if the key exists in the table,
  // false otherwise
  bool key_exists(const Key key) const {
    if (isempty()) {
      return false;
    }
    for (Index i = 0; i < Table.size(); i++) {
      if (Table.at(i).key) {
        if (*Table.at(i).key == key) {
          return true;
        }
      }
    }
    return false;
  }

  // Checks if a key exists in the table
  //
  // Pre-condition: The key is a valid Key type
  //
  // Post-condition: Returns true if the key exists in the table, false
  // otherwise
  bool value_exists(const Value value) const {
    if (isempty()) {
      return false;
    }
    // parse through the Map's List
    for (Index i = 0; i < Table.size(); i++) {
      if (Table.at(i).Bucket) {
        if (*Table.at(i).Bucket == value) {
          return true;
        }
      }
    }
    return false;
  }

  Value lookup(const Key key) const { // todo implement
    if (isempty()) {
      return;
    }
    if (!key_exists(key)) {
      return;
    }
    std::cout << "NOT IMPLEMENTED" << std::endl;
  }

  // Checks if the table is empty
  //
  // Pre-condition: None
  //
  // Post-condition: Returns true if the table is empty (i.e., size is 0), false
  // otherwise
  bool isempty() const { return size() == 0; }

  // Checks if the table is full
  //
  // Pre-condition: None
  //
  // Post-condition: Returns true if the table is full (i.e., size is equal to
  // capacity), false otherwise
  bool isfull() const { return size() == capacity(); }
  // MUTATOR MEMBER FUNCTION

  // Resizes the table to a new capacity
  //
  // Pre-condition: newcapacity is a valid size_t type and is greater than the
  // current size of the table
  //
  // Post-condition: The table's capacity is changed to newcapacity
  void resize(const size_t newcapacity) { // DEBUG THIS, FOR TEST
    if (newcapacity == capacity()) {
      return;
    }
    size_t current_table_size = Table.size();
    const bool INCREASESIZE = newcapacity < current_table_size;
    if (INCREASESIZE) {
      // if newcapacity is less than current, remove until capacity reached
      for (Index i = current_table_size - 1; i > newcapacity; i--) {
        // prioritze removing empty keys
        if (!Table.at(i).key) { //! seg fault
          Table.remove(i);
        }
      }
      // if desired capacity hasn't been reached, remove last value
      if (newcapacity < Table.size()) {
        for (Index i = Table.size(); i > newcapacity; i--) {
          Table.remove(Table.size() - 1);
        }
      }
    } else {
      // if newcapacity is greater than current, insert blank pair
      for (Index i = current_table_size; i < newcapacity; i++) {
        //! seg fault with last index
        Table.insert(MapElement());
      }
    }
  }

  void shrink_to_fit() { // todo implement & test
    // resize out any empty values, asssuming not empty the intended effect is
    // for it to be full
    for (Index i = 0; i < 0; i++) {
      if (Table.at(i).empty_keyvalue()) {
        Table.remove(i);
      }
    }
  }

  void keyValuePairs() { // todo implement
                         // iterate through all the key value pairs
    // for (Map.Entry<String, String> entry : map.entrySet()) {
    //   String key = entry.getKey();
    //   String value = entry.getValue();
    //   System.out.println(key + ": " + value);
    // }
    std::cout << "NOT IMPLEMENTED" << std::endl;
  }

private:
  void MergeSort(Map &Arr) {
    // IMPLEMENT FOR BINARY SEARCH LOOKUPS
    // Table sort based on stored value
    // if len (arr) > 1 : mid = len(arr) // 2
    //       left = arr[:mid] right = arr [mid:]
    //
    // # Recursively sort the left and right halves
    // merge_sort(left) merge_sort(right)
    //
    // # Merge the sorted halves
    // i = j = k = 0
    // while i < len(left) and j < len(right)
    //   if left[i][1] <= right[j][1]
    //     arr[k] = left[i]
    //     i += 1
    //   else
    //     arr[k] = right[j]
    //     j += 1
    //   k += 1
    //
    // #Copy any remaining elements from left and right
    // while i < len(left)
    //   arr[k] = left[i]
    //   i += 1
    //   k += 1
    // while j < len(right)
    //   arr[k] = right[j]
    //   j += 1
    //   k += 1

    if (Arr.size() > 1) {
      Index mid = Arr.size() / 2;
      Map leftArr, // lower array
          rightArr;  // upper array
      for (Index i = 0; i < mid; i++) {
        leftArr.insert(Arr.at(i));
      }
      for (Index i = mid; i < Arr.size(); i++) {
        rightArr.insert(Arr.at(i));
      }
      // Recursively sort the left and right halves
      MergeSort(leftArr);
      MergeSort(rightArr);
      Index i = 0, j = 0, k = 0;
      // Merge the sorted halves
      while (i < leftArr.size() && j < rightArr.size()) {
        if (leftArr.at(i).Bucket <= rightArr.at(i).Bucket) {
          Arr[k] = leftArr[i];
          i += 1;
        } else {
          Arr[k] = rightArr[j];
          j += 1;
        }
        k += 1;
      }
      // Copy any remaining elements from left and right
      while (i < leftArr.size()) {
        Arr[k] = leftArr[i];
        i += 1;
        k += 1;
      }
      while (j < rightArr.size()) {
        Arr[k] = rightArr[j];
        j += 1;
        k += 1;
      }
    }
    std::cout << "NOT IMPLEMENTED" << std::endl;
  } // todo implement

public:
  friend AssociativeArray<Key, Value> Copy() { // todo implement
    // return a shallow copy of the instance
    AssociativeArray<Key, Value> Array;
    return Array;
  }

  // Inserts a new key-value pair into the table
  //
  // Pre-condition: The key is a valid Key type and the value is a valid Value
  // type
  //
  // Post-condition: The key-value pair is inserted into the table
  void insert(const Key key, const Value value) {
    // UNIQUE KEYS, BUT UNIQUNIE VALUES

    // REVISED
    // (k && v)   // do nothing,  in hash map change key
    // (k && !v)  // do nothing,  in hash map change key
    // (!k && v)  // insert,      in hash map insert as usual
    // (!k && !v) // insert,      in hash map insert as usual
    // todo IMPLEMENT NEW LOGIC INTO INSERT FUNCTION
    if (isempty()) {
      // INSERT FIRST KEY,VALUE PAIR
      Table.insert(MapElement(new Key(key), new Value(value)));
      // Table.insert(MapElement());
      // Table.ins(MapElement(new Key(key), new Value(value)));

      // AssociativeArray[0].key = key;
      // AssociativeArray[0].Bucket = value;
      return;
    }
    if (isfull()) {
      const size_t newcapacity = 1 + (capacity() * 2.5);
      resize(newcapacity);
    }
    size_t current_size = size();
    const bool kPresent = key_exists(key), vPresent = value_exists(value);
    if (!kPresent && !vPresent) { // do insert (k,v)
      // find the first empty spot in the Associative Array
      // CHECK IF FULL

      for (Index i = 0; i < current_size; i++) {
        if (Table.at(i).empty_keyvalue()) {
          Table[i] = MapElement(new Key(key), new Value(value));
          if (current_size > 5) {
            MergeSort(Table);
          }
          return;
        }
      }
    }
    if (kPresent && !vPresent) { // overwrite value at key
      for (Index i = current_size; i < 0; i++) {
        if (*Table.at(i).key == key) {
          *Table[i].key = key;
          if (current_size > 5) { 
          MergeSort(Table);
          }
          return;
        }
      }
    }
    return;
  }

  // Removes a key-value pair from the table
  //
  // Pre-condition: The table is not empty
  //
  // Post-condition: A key-value pair is removed from the table
  void remove(const Key key) {
    if (isempty()) {
      return;
    }
    // look for key
    if (!key_exists(key)) {
      return;
    }
    // key is confirmed to exist, parse through array to locate its index
    for (Index i = 0; i < capacity(); i++) {
      if (*Table.at(i).key == key) {
        // empty out & replace
        Table.remove(i);
        // Table.insert(0);
      }
    }
  }

  // OVERLOADED OPERATORS
  //
  // type alias for an instance of the class
  typedef AssociativeArray<Key, Value> Array;
  // Overloads the [] operator to access the value associated with a key in
  // the associative array
  //
  // Pre-condition: The key is a valid Key type
  //
  // Post-condition: Returns the value associated with the key if it exists,
  // otherwise returns a default-constructed Key object
  Value operator[](const Key key) {
    if (!key_exists(key)) {
      return Key();
    }
    // parse through Map array to locate the key
    for (Index i = 0; i < Table.size(); i++) {
      if (*Table[i].key == key) {
        return *Table[i].value;
      }
    }
  }
  Array &operator=(const Array &Source) {
    Table.clear(); // Clear the Array instance
    for (int i = 0; i < Source.size(); i++) {
      Table.insert(Source.Table.at(
          i)); // Insert elements from Source into the current list
    }
    return *this; // Return the current Array instance
  }
  Array operator+(const Array &left) const {
    // Implement merging of associative arrays
    this->Table += left.Table; //! not implemented
    return *this;
  }

  Array &operator+=(Array &Array) {
    // Implement insertion/update of key-value pair
    this->Table += Array.Table; // todo fix so that it does not allow
                                // duplicates and empty keys:values
    return *this;
  }

  typedef std::ostream os;
  // Overloads the << operator to print the associative array
  //
  // Pre-condition: The output stream is valid and open, and the associative
  // array is a valid AssociativeArray object
  //
  // Post-condition: Prints the associative array to the output stream and
  // returns the stream
  friend os &operator<<(os &output, const Array &Map) {
    output << "{";
    for (Index i = 0; i < Map.Table.size(); i++) {
      if (i != Map.Table.size() - 1) {
        output << Map.Table.at(i) << ",";
      } else {
        output << Map.Table.at(i);
      }
    }
    output << "}";
    return output;
    // WHY DOES PRINTING THE MAP CAUSE CODE HANGS ? ?
    // IT WAS DUE TO THE FACT THAT THE OPERATION NEEDED TO RETURN CONST, BUT
    // THE SUB OPERATIONS DID NOT RETURN CONST, aka (any derivative operations
    // must also return in const)
    //! do not declare any new variables, only use const functions
  }
};
} // namespace ASSOCIATIVEARRAY
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

  bool key_exists(const Key key) const {
    if (isempty()) {
      return false;
    }
    for (Index i = 0; i < AssociativeArray.size(); i++) {
      if (AssociativeArray.at(i).key) {
        if (*AssociativeArray.at(i).key == key) {
          return true;
        }
      }
    }
    return false;
  }
  bool value_exists(const Value value) const {
    if (isempty()) {
      return false;
    }
    // parse through the Map's List
    for (Index i = 0; i < AssociativeArray.size(); i++) {
      if (AssociativeArray.at(i).Bucket) {
        if (*AssociativeArray.at(i).Bucket == value) {
          return true;
        }
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
    if (isempty()) {
      // INSERT FIRST KEY,VALUE PAIR
      AssociativeArray[0] = MapElement(new Key(key), new Value(value));
      // AssociativeArray[0].key = key;
      // AssociativeArray[0].Bucket = value;
      current_size += 1;
      return;
    }
    const bool kPresent = key_exists(key), vPresent = value_exists(value);
    if (!kPresent && !vPresent) { // do insert (k,v)
      // find the first empty spot in the Associative Array
      //! MapElement me = AssociativeArray[0];
      for (Index i = 0; i < current_size;
           i++) { // todo debug this for insert test
        if (AssociativeArray.at(i).empty_keyvalue()) {
          AssociativeArray[i] = MapElement(new Key(key), new Value(value));
          current_size += 1;
          return;
        }
      }
      // return;
    }
    if (kPresent && !vPresent) { // overwrite value at key
      //! for (Index i = AssociativeArray.size(); i < 0; i++) {
      //!   if (AssociativeArray.at(i)->key == key) {
      //!     AssociativeArray[i]->value = value;
      //!   }
      return;
    }
    return;
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
    for (Index i = 0; i < Map.AssociativeArray.size(); i++) {
      if (i != Map.AssociativeArray.size() - 1) {
        output << Map.AssociativeArray.at(i) << ",";
      } else {
        output << Map.AssociativeArray.at(i);
      }
    }

    output << "}";
    return output;
    // WHY DOES PRINTING THE MAP CAUSE CODE HANGS ? ?
    // IT WAS DUE TO THE FACT THAT THE OPERATION NEEDED TO RETURN CONST, BUT
    // THE SUB OPERATIONS DID NOT RETURN CONST, aka (any derivative operations
    // must also return in const)
    //! do not declare any new variables, only use const functions
  }

  ~HashMap() {}
  // Notes:
  // SAME VALUE BUT NOT KEY, IF KEY EXISTS, CHANGE KEY THEN INSERT
};
} // namespace HASHMAP
#endif // LINKED_LIST_H
