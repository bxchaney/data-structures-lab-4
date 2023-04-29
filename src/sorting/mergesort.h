#pragma once
#include<iostream>
#include<memory>
#include"queue.h"

struct Endpoints
{
    std::shared_ptr<MergeNode> left, right;
    int size;
    Endpoints() : left(nullptr), right(nullptr), size(0){};
    Endpoints(
        MergeSort::node_pointer left,
        MergeSort::node_pointer right,
        int segment_size
    ) : left(left), right(right), size(segment_size) {};
};

class MergeNode
{
    public:
    int data;
    std::shared_ptr<MergeNode> next;
    MergeNode(int data) : data(data), next(nullptr) {}
    ~MergeNode() = default;
};

class MergeSort
{
    public: 
        typedef std::shared_ptr<MergeNode> node_pointer;
    private:

        

        // sentinel node
        node_pointer _head {nullptr};
        node_pointer _tail {nullptr};
        int _size = 0;

        int _comparisons = 0;
        int _exchanges = 0;

        void enqueue(int);

        Endpoints next_partition(node_pointer);

        // void move_behind(node_pointer, node_pointer);

        Endpoints mergesort(node_pointer);

        Endpoints merge(Endpoints&, Endpoints&);

    public:

        

        MergeSort(Queue<int>);
        ~MergeSort();

        void sort();

        void write_output(std::ostream&);

        friend std::ostream& operator<<(std::ostream&, MergeSort&);
};
