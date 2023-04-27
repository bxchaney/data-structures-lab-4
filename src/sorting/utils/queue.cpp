#include<memory>
#include"queue.h"
#include<map>

template <typename T> template<typename U>
Queue<T>::__node<U>::__node(U data)
{
    this-> data = data;
    next = nullptr;
}


template<typename T>

Queue<T>::Queue(Queue<T>& other)
{
    _head = nullptr;
    _tail = nullptr;
    _size = 0;

    std::shared_ptr<Queue<T>::Node> curr_node = other._head;
    while(curr_node)
    {
        enqueue(curr_node->data);
        curr_node = curr_node->next;
    }
}

template <typename T>
void Queue<T>::enqueue(T data)
{
    _size++;
    
    std::shared_ptr<Node> 
    new_node std::shared_ptr<Node>(new Node(data));
        
    // Queue is empty
    if (_head == nullptr)
    {
        _head = new_node
        _tail = head;
    }
    else
    {
        _tail->next = new_node;
        _tail = new_node;
    }
}

template <typename T>
int Queue<T>::size()
{
    return _size;
}