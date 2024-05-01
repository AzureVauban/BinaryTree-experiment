#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"

namespace QUEUE {
    template <class T>
    struct Queue {
    private:
        LINKEDLIST::Linked_List<T> linkedQueue;

    public:
        void Enqueue(T value) {
            linkedQueue.insert(value);
        }

        void Dequeue() {
            if (!IsEmpty()) {
                linkedQueue.remove(0);
            }
        }

        T Peek() {
            if (IsEmpty()) {
                return T();
            }
            return linkedQueue.get_node(0)->value;
        }

        bool IsEmpty() {
            return linkedQueue.isempty();
        }

        size_t Size() const {
            return linkedQueue.size();
        }
        ~Queue() {
            while (!linkedQueue.isempty()) {
                linkedQueue.remove();
            }
        }
    };
}

#endif // QUEUE_H