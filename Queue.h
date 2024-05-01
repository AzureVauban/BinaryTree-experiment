#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
namespace QUEUE
{
    template <class B>
    struct Queue
    {
    private:
        LINKEDLIST::Linked_List<class B> queue_heap;

    public:
        void Enqueue() { std::cout << "NOT IMPLEMENTED YET" << std::endl; }
        void Dequeue() { std::cout << "NOT IMPLEMENTED YET" << std::endl; }
        void Peek() { std::cout << "NOT IMPLEMENTED YET" << std::endl; }
        void IsEmpty() { std::cout << "NOT IMPLEMENTED YET" << std::endl; }
        void Size() { std::cout << "NOT IMPLEMENTED YET" << std::endl; }
    };
}
#endif // QUEUE_H