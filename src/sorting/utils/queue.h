#pragma once
#include<iostream>

template<typename T>
struct Node
{
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        
        value_type data;
        Node<T> *next;
        Node<T> *prev;
        Node(reference data) : data(data), next(nullptr), prev(nullptr){}
        ~Node() = default;
};

template<typename T>
class Queue
{
    private:
        using node_type = Node<T>;
        using node_pointer = node_type*;
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;

        node_pointer _head, _tail;
        size_t _size;

    public:

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

/// @brief The copy constructor for Queue<T>. Creates new instance of Queue<T>
/// with copies of the same elements in the same order.
/// @tparam T 
/// @param other 
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

/// @brief Queue<T> destructor.
/// @tparam T 
template<typename T>
Queue<T>::~Queue()
{
    // Iteritively delete each node in Queue.
    while(_head)
    {
        node_pointer curr = _head;
        _head = _head->next;
        curr->~Node();
    }
}

/// @brief Assignment operator for Queue<T>.
/// @tparam T 
/// @param other 
/// @return 
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

/// @brief Adds new element to the end of the queue.
/// @tparam T type of elements in the queue.
/// @param data value being added to the queue.
template <typename T>
void Queue<T>::enqueue(value_type data)
{
    node_pointer new_node = new Node<T>(data);
        
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

/// @brief Returns and removes the front element of the queue.
/// @tparam T value type of elements in the queue.
/// @return front element of the queue.
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
    value_type data = node->data;
    node->~Node();
    _size--;
    return data;
}

/// @brief Returns the number of elements in the queue.
/// @tparam T the type of elements in the queue.
/// @return 
template <typename T>
size_t Queue<T>::size()
{
    return _size;
}

/// @brief ostream operator overloaded to support printing of Queue<T>
/// objects.
/// @tparam T type of elements in the queue. 
/// @param os an ostream.
/// @param q a Queue<T>.
/// @return os.
template<typename T>
std::ostream& operator<< (std::ostream& os, Queue<T>& q)
{
    Node<T> *current = q._head;
    while(current)
    {
        os << current->data << std::endl;
        current = current->next;
    }
    return os;
}
