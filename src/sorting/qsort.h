#pragma once
#include<iostream>
#include<memory>
#include"queue.h"
#include"stack.h"

class QuickSort
{
    private:
        std::unique_ptr<int[]> _data;
        int _size;
        int _partition;

        unsigned long long _swaps {0};
        unsigned long long _comparisons {0};

        bool _first_pivot {0};

        void qsort(int, int);
        Tuple partition(int, int);

        int median(int, int, int);
        void swap(int, int);

        void insertion_sort(int, int);

    public:
        QuickSort(Queue<int>, int);
        ~QuickSort() = default;

        void sort();

        void write_output(std::ostream&);
        void write_summary(std::ostream&);

        friend std::ostream& operator<<(std::ostream&, QuickSort&);
};