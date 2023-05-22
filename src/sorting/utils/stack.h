#pragma once
#include"queue.h"

struct Tuple
{
    int a, b;
};

template<typename T>
class Stack
{
    private:
        using node_type = Node<T>;
        using node_pointer = Node<T>*;
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;


        node_pointer _head = nullptr;
        size_t _size = 0;

    public:

        Stack() = default;
        ~Stack();

        void push(T&);
        T pop();

        bool is_empty();
        int size();
};

template<typename T>
Stack<T>::~Stack() 
{
    while(_head)
    {
        pop();
    }
}

/// @brief adds a new value to the end of the stack.
/// @tparam T type of parameter.
/// @param value the value being added to the stack.
template<typename T>
void Stack<T>::push(T& value)
{
    node_pointer new_node = new Node(value);
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
    node_pointer old_node = _head;
    _head = _head->next;
    old_node->~Node();
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
