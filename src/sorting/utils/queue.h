#pragma once
#include<memory>

template<typename T>
class Queue
{
    private:
        template<typename U>
        class __node
        {
            public:
            U data;
            std::shared_ptr<__node> next;
            __node() = default;
            __node(U);
        };

        typedef __node<T> Node;

        std::shared_ptr<Node> _head;
        std::shared_ptr<Node> _tail;
        int _size;

    public:
        Queue() = default;
        ~Queue();

        Queue(Queue<T>&);
        Queue& operator=(Queue&);

        void enqueue(T);
        T dequeue();
        int size();
};