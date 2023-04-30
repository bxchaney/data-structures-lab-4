#pragma once
#include<iostream>
#include<memory>
#include"queue.h"

class MergeNode
{
    public:
    int data;
    std::shared_ptr<MergeNode> next;
    MergeNode(int data) : data(data), next(nullptr) {}
    ~MergeNode() = default;
};

class NaturalMergeSort
{
    public: 
        typedef std::shared_ptr<MergeNode> node_pointer;
    private:

        class Endpoints
        {
            public:
            std::shared_ptr<MergeNode> left, right;
            int size;
            Endpoints() = default;
            Endpoints(
                std::shared_ptr<MergeNode> left,
                std::shared_ptr<MergeNode> right,
                int segment_size
            );
        };

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

        

        NaturalMergeSort(Queue<int>);
        ~NaturalMergeSort() = default;

        void sort();

        void write_output(std::ostream&);

        friend std::ostream& operator<<(std::ostream&, NaturalMergeSort&);
};
