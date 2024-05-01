#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include <cstddef>
namespace QUEUE {
template <class datatype_T> struct Queue {
private:
  LINKEDLIST::Linked_List<datatype_T> linkedQueue;

public:
  void Enqueue(datatype_T value) { linkedQueue.insert(value); }

  void Dequeue() {
    if (!IsEmpty()) {
      linkedQueue.remove(0);
    }
  }

  datatype_T Peek() {
    if (IsEmpty()) {
      return datatype_T();
    }
    return linkedQueue.get_node(0)->value;
  }

  bool IsEmpty() { return linkedQueue.isempty(); }

  size_t Size() const { return linkedQueue.size(); }
  ~Queue() {
    while (!linkedQueue.isempty()) {
      linkedQueue.remove();
    }
  }
};
} // namespace QUEUE
namespace PRIORITY_QUEUE {
template <class datatype_K> struct PriorityQueue { // UNTESTED
private:
  template <class datatype_N> struct PriorityQueueNode {
    size_t priority;
    datatype_N value;

    explicit PriorityQueueNode(size_t priority, datatype_N value)
        : priority(priority), value(value) {}
  };

  LINKEDLIST::Linked_List<PriorityQueueNode<datatype_K>> Heap;

  datatype_K Peek() {
    if (IsEmpty()) {
      return datatype_K();
    }
    return Heap.get_node(0)->value;
  }
  void heapify(LINKEDLIST::Linked_List<datatype_K> &list, size_t index) {
    size_t largest = index, left = (2 * index) + 1, right = (2 * index) + 2;

    // Compare node with left child
    if (left < list.size() && list.get_node(left)->value->data >
                                  list.get_node(largest)->value->data) {
      largest = left;
    }

    // Compare largest so far with right child
    if (right < list.size() && list.get_node(right)->value->data >
                                   list.get_node(largest)->value->data) {
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
  bool IsEmpty() { return Heap.isempty(); }

  size_t Size() { return Heap.size(); }

  void Enqueue(datatype_K value, size_t priority) {
    Heap.insert(value);
    heapify(Heap, 0);
  }

  void Dequeue() {
    if (!IsEmpty()) {
      Heap.remove(0);
      heapify(Heap, 0);
    }
  }
};
}; // namespace PRIORITY_QUEUE
#endif // QUEUE_H