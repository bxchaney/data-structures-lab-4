#include<memory>
#include"queue.h"

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
    _tail = nullptr;
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
    node->next = nullptr;
    _size--;
    return node->data;
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