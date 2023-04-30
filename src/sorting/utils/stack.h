#pragma once
#include<memory>
#include"queue.h"

struct Tuple
{
    int a, b;
};

template<typename T>
class Stack
{
    private:
        typedef Node<T> node_type;
        typedef std::shared_ptr<node_type> node_pointer;

        node_pointer _head = nullptr;
        size_t _size = 0;

    public:
        typedef typename node_type::value_type value_type;
        typedef typename node_type::reference reference;
        typedef typename node_type::const_reference const_reference;

        Stack() = default;
        ~Stack() = default;

        void push(T&);
        T pop();

        bool is_empty();
        int size();
};