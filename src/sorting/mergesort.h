#pragma once
#include<iostream>
#include"queue.h"

class MergeNode
{
    public:
    int data;
    MergeNode *next;
    MergeNode(int data) : data(data), next(nullptr) {}
    ~MergeNode() = default;
};

class NaturalMergeSort
{
    public: 
        using node_pointer = MergeNode*;        
    private:

        class Endpoints
        {
            public:
            node_pointer left;
            node_pointer right;
            int size;
            Endpoints() = default;
            Endpoints(
                node_pointer left,
                node_pointer right,
                int segment_size
            );
        };

        // sentinel node
        node_pointer _head {nullptr};
        node_pointer _tail {nullptr};
        int _size = 0;

        unsigned long long _comparisons = 0;
        unsigned long long _exchanges = 0;

        void enqueue(int);

        Endpoints next_partition(node_pointer);

        Endpoints mergesort(node_pointer);

        Endpoints merge(Endpoints&, Endpoints&);

    public:

        

        NaturalMergeSort(Queue<int>);
        ~NaturalMergeSort();

        void sort();

        void write_output(std::ostream&);

        void write_summary(std::ostream&);

        friend std::ostream& operator<<(std::ostream&, NaturalMergeSort&);
};
