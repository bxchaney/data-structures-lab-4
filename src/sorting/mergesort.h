#pragma once
#include<iostream>
#include<memory>
#include"queue.h"

struct Endpoints
{
    std::shared_ptr<MergeNode> left, right;
};

class MergeNode
{
    public:
    int data;
    std::shared_ptr<MergeNode> prev, next;
    MergeNode(int data) : data(data), prev(nullptr), next(nullptr) {}
    ~MergeNode() = default;
};

class MergeSort
{
    private:

        typedef std::shared_ptr<MergeNode> node_pointer;

        node_pointer _head {nullptr};
        node_pointer _tail {nullptr};
        int _size = 0;

        int _comparisons = 0;
        int _swaps = 0;

        void enqueue(int);

        Endpoints next_partition(node_pointer);

        void move_behind(node_pointer, node_pointer);

        void merge(Endpoints, Endpoints);

    public:

        MergeSort(Queue<int>);
        ~MergeSort();

        void sort();

        void write_output(std::ostream&);

        friend std::ostream& operator<<(std::ostream&, MergeSort&);
};
