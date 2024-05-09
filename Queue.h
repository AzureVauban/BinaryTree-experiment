#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include <cstddef>
#include <cstdio>

namespace LINKEDQUEUE {
template <class datatype_V> struct Queue {
  typedef datatype_V Value;
  typedef size_t Index;
  LINKEDLIST::Linked_List<Value> Array;

  explicit Queue() : Array(LINKEDLIST::Linked_List<Value>()) {}

  // Enqueues a value into the queue
  //
  // Pre-condition: The value to be enqueued is of type Value
  //
  // Post-condition: The value is added to the end of the queue
  void enqueue(const Value value) {
    // Index i = (Array.size() > 0) ? Array.size() - 1 : 0;
    //,(Array.size() > 0) ? Array.size() - 1 : 0
    Array.insert(value);
  }

  // Dequeues a value from the queue
  //
  // Pre-condition: The queue is not empty
  //
  // Post-condition: The value at the front of the queue is removed
  void dequeue() { Array.remove(0); }
  
  // Returns the value at the front of the queue without removing it
  //
  // Pre-condition: The queue is not empty
  //
  // Post-condition: The value at the front of the queue is returned
  Value Peek() const {
    if (Array.isempty()) {
      return Value();
    }
    return Array.at(0);
  }

  bool value_exists(const Value value) {
    return Array.in(value);
  }
  // Returns the number of elements in the queue
  //
  // Pre-condition: None
  //
  // Post-condition: The number of elements in the queue is returned
  size_t Size() const { return Array.size(); }

  // Checks if the queue is empty
  //
  // Pre-condition: None
  //
  // Post-condition: Returns true if the queue is empty, false otherwise
  bool isEmpty() const { return Array.isempty(); }

  // Clears the queue
  //
  // Pre-condition: None
  //
  // Post-condition: The queue is empty
  void clear() { Array.clear(); }

  typedef std::ostream os;
  // Overloads the << operator to print the Queue
  //
  // Pre-condition: The output stream is valid and open, and the associative
  // array is a valid AssociativeArray object
  //
  // Post-condition: Prints the Queue to the output stream and
  // returns the stream
  friend os &operator<<(os &output, const Queue &Queue) {
    output << Queue.Array;
    return output;
  }
  ~Queue() { Array.clear(); }
};
} // namespace LINKEDQUEUE
namespace PRIORITYQUEUE {
template <class datatype_V> struct PriorityQueue {
  typedef datatype_V Value;
  typedef size_t Index;
  typedef size_t Priority;
  LINKEDLIST::Linked_List<Value> Array;
  struct PriorityQueueNode {
    Priority priority;
    const Value value;
    PriorityQueueNode(const Value &value, Priority priority)
        : value(value), priority(priority) {}
  };

  typedef PriorityQueueNode Node;
  explicit PriorityQueue() : Array(LINKEDLIST::Linked_List<Node>()) {}

private:
  void heapify(LINKEDLIST::Linked_List<Node> &list, Index index) {
    Index largest = index, left = (2 * index) + 1, right = (2 * index) + 2;

    // Compare node with left child
    if (left < list.size() &&
        list.at(left)->value->data > list.at(largest)->value->data) {
      largest = left;
    }

    // Compare largest so far with right child
    if (right < list.size() &&
        list.at(right)->value->data > list.at(largest)->value->data) {
      largest = right;
    }

    // If largest is not the current node, swap and continue heapifying
    if (largest != index) {
      list.swap(index, largest);
      heapify(list,
              largest); // Call heapify on the child index that was swapped
    }
  }

public:
  void enqueue(const Value value, const Priority priority) {
    Array.insert(Node(value, priority));
  };
  void dequeue() { Array.remove(0); }
  size_t Size() const { return Array.size(); }
  bool isEmpty() const { return Array.isempty(); }
  void clear() { Array.clear(); }
  typedef std::ostream os;
  friend os &operator<<(os &output, const PriorityQueue &Queue) {
    output << Queue.Array;
    return output;
  }
  ~PriorityQueue() { Array.clear(); }
};
} // namespace PRIORITYQUEUE
#endif // QUEUE_H