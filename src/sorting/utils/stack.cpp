#include<memory>
#include"queue.h"
#include"stack.h"

/// @brief adds a new value to the end of the stack.
/// @tparam T type of parameter.
/// @param value the value being added to the stack.
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

/// @brief returns and removes the last value of the stack.
/// @tparam T type of parameter.
/// @return the value at the top of the stack. Throws an exception when the
/// stack is empty.
template<typename T>
T Stack<T>::pop()
{
    if (!_head) throw std::exception();
    T data = _head->data;
    _head = _head->next;
    _size--;
    return data;
}

/// @brief Returns true when the stack is empty.
/// @tparam T the type of values in the stack.
/// @return 
template<typename T>
bool Stack<T>::is_empty()
{
    return _head == nullptr;
}

/// @brief Returns the number of elements in the stack.
/// @tparam T the type of elements in the stack.
/// @return 
template<typename T>
int Stack<T>::size()
{
    return _size;
}

template class Stack<Tuple>;
template class Node<Tuple>;