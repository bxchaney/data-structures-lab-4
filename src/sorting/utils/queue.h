#pragma once
#include<iostream>
#include<memory>

template<typename T>
struct Node
{
    public:
        typedef T value_type;
        typedef T& reference;
        typedef const T& const_reference;

        value_type data;
        std::shared_ptr<Node<T>> next, prev;
        Node(reference data) : data(data), next(nullptr), prev(nullptr){}
        ~Node() = default;
};



template<typename T>
class Queue
{
    private:
        
        typedef Node<T> node_type;
        typedef std::shared_ptr<node_type> node_pointer;

        node_pointer _head, _tail;
        size_t _size;

    public:
        typedef typename node_type::value_type value_type;
        typedef typename node_type::reference reference;
        typedef typename node_type::const_reference const_reference;

        Queue() = default;
        ~Queue();

        Queue(Queue<T>&);
        Queue& operator=(const Queue&);

        void enqueue(value_type);
        value_type dequeue();
        size_t size();

        template<typename U>
        friend std::ostream& operator<<(std::ostream&, Queue<U>&);
};