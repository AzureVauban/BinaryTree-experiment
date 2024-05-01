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
        B Dequeue()
        {
            std::cout << "NOT IMPLEMENTED YET" << std::endl;
            return B();
        }
        B Peek()
        {
            std::cout << "NOT IMPLEMENTED YET" << std::endl;
            return B();
        }
        void IsEmpty()
        {
            std::cout << "NOT IMPLEMENTED YET" << std::endl;
            return false;
        }
        size_t Size()
        {
            std::cout << "NOT IMPLEMENTED YET" << std::endl;
            return 0;
        }
    };
}
#endif // QUEUE_H