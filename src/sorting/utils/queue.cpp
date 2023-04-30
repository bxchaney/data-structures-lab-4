#include<memory>
#include"queue.h"

template<typename T>
Queue<T>::Queue(Queue<T>& other)
{
    _head = nullptr;
    _tail = nullptr;
    _size = 0;

    node_pointer curr_node = other._head;
    while(curr_node)
    {
        enqueue(curr_node->data);
        curr_node = curr_node->next;
    }
}

template<typename T>
Queue<T>::~Queue()
{
    while(_head)
    {
        node_pointer curr = _head;
        _head = _head->next;
        curr->~Node();
    }
    _tail = nullptr;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    _head = nullptr;
    _tail = nullptr;
    _size = 0;

    node_pointer curr_node = other._head;
    while(curr_node)
    {
        enqueue(curr_node->data);
        curr_node = curr_node->next;
    }
    return *this;
}

template <typename T>
void Queue<T>::enqueue(value_type data)
{
    
    
    node_pointer new_node = std::shared_ptr<node_type>(new Node(data));
        
    // Queue is empty
    if (_head == nullptr)
    {
        _head = new_node;
        _tail = _head;
    }
    else
    {
        // add new nodes to the tail of the list
        _tail->next = new_node;
        new_node->prev = _tail;
        _tail = new_node;
    }
    _size++;
}

template<typename T>
typename Queue<T>::value_type Queue<T>::dequeue()
{
    node_pointer node = _head;
        
    // one node remaining
    if (_head == _tail)
    {
        _head = _tail = nullptr;
    }
    else
    {
        _head = _head->next;
        _head->prev = nullptr;
    }
    node->next = nullptr;
    _size--;
    return node->data;
}

template <typename T>
size_t Queue<T>::size()
{
    return _size;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, Queue<T>& q)
{
    std::shared_ptr<Node<T>> current = q._head;
    while(current)
    {
        os << current->data << std::endl;
        current = current->next;
    }
    return os;
}

template class Node<int>;
template class Queue<int>;
template std::ostream& operator<< <int>(std::ostream&, Queue<int>&);