#include<memory>
#include"queue.h"
#include"stack.h"

template<typename T>
void Stack<T>::push(T& value)
{
    node_pointer new_node = std::shared_ptr<Node<T>>(new Node(value));
    if (!_head)
    {
        _head = new_node;
    }
    else
    {
        new_node->next = _head;
        _head = new_node;
    }

    _size++;
}

template<typename T>
T Stack<T>::pop()
{
    if (!_head) throw std::exception();
    T data = _head->data;
    _head = _head->next;
    _size--;
    return data;
}

template<typename T>
bool Stack<T>::is_empty()
{
    return _head == nullptr;
}

template<typename T>
int Stack<T>::size()
{
    return _size;
}

template class Stack<Tuple>;
template class Node<Tuple>;