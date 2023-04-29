#include<iostream>
#include<memory>
#include"queue.h"
#include"qsort.h"

/// @brief Constructor for Quicksort object. The user may choose from the
/// following sort types:
///  0: partition of 2 is stopping case, first element is pivot,
///  this is default
///  1: partition of 50 is stopping case, first element is pivot
///  2: partition of 100 is stopping case, first element is pivot
///  3: partition of 2 is stopping case, median of 3 is pivot
/// @param queue a Queue of integer data, makes a copy on construction
/// @param type 
QuickSort::QuickSort(Queue<int> queue, int type)
{
    if (type < 0 || type > 3) type = 0;
    switch (type)
    {
        case 1:
            _partition = 50;
            _first_pivot = true;
            break;
        case 2:
            _partition = 100;
            _first_pivot = true;
            break;
        case 3:
            _partition = 2;
            break;
        default:
            _partition = 2;
            _first_pivot = true;
            break;
    }
    _size = queue.size();
    _data = std::unique_ptr<int[]>(new int[queue.size()]);
    int i {0};
    while(queue.size() > 0)
    {
        int temp = queue.dequeue();
        _data[i] = temp;
        i++;
    }
}

void QuickSort::qsort(int low, int high)
{
    _comparisons++;
    if (low < high)
    {
        _comparisons++;
        if (high - low + 1 <= _partition)
        {
            insertion_sort(low, high);
        }
        else
        {
            Tuple pivot = partition(low, high);

            qsort(low, pivot.a);
            qsort(pivot.b, high);
        }
    }
}

Tuple QuickSort::partition(int low, int high)
{
    int pivot_loc;
    _comparisons++;
    if (_first_pivot)
    {
        pivot_loc = low;
    }
    else
    {
        pivot_loc = median(low, (low + high) / 2, high);
    }

    int pivot = _data[pivot_loc];
    int left = low;
    int right = high;
    _comparisons++;
    while (left <= right)
    {
        _comparisons += 3;
        while((left <= right) && (_data[left] < pivot))
        {
            left++;
            _comparisons += 3;
        }
        _comparisons += 3;
        while((left <= right) && (_data[right] > pivot))
        {
            right--;
            _comparisons += 3;
        }
        _comparisons++;
        if (left <= right)
        {
            swap(left, right);
            left++;
            right--;
        }
        _comparisons++;
    }
    Tuple t {right, left};
    return t;
}

void QuickSort::swap(int i, int j)
{
    _swaps += 2;
    int t = _data[i];
    _data[i] = _data[j];
    _data[j] = t;
}

int QuickSort::median(int a, int b, int c)
{
    if (b >= a && b >= c)
    {
        _comparisons += 2;
        return (a >= c) ? a : c;
    }
    if (a >= b && a >= c)
    {
        _comparisons += 3;
        return (b >= c) ? b : c;
    }
    _comparisons += 3;
    return (a >= b) ? a : b;
}

void QuickSort::insertion_sort(int low, int high)
{
    int i, key, j;
    _comparisons++;
    for (i = low + 1; i <= high; i++) 
    {
        key = _data[i];
        j = i - 1;
        _comparisons++;
        while (j >= low && _data[j] > key) 
        {
            _swaps++;
            _data[j + 1] = _data[j];
            j--;
            _comparisons++;
        }
        _swaps++;
        _data[j + 1] = key;
        _comparisons++;
    }
}

void QuickSort::sort()
{
    qsort(0, _size - 1);
}

void QuickSort::write_output(std::ostream& os)
{
    int i = 0;
    while (i < _size)
    {
        os << _data[i++] << std::endl;
    }
}

std::ostream& operator<<(std::ostream& os, QuickSort& qs)
{
    os << "Quicksort:" << std::endl;
    os << "    Partition cutoff: " << qs._partition << std::endl;
    os << "    Pivot Type: ";
    if (qs._first_pivot)
    {
        os << "First";
    }
    else 
    {
        os << "Median";
    }
    os << std::endl;
    os << "    Dataset Size: " << qs._size << std::endl;
    os << "    Comparisons: " << qs._comparisons << std::endl;
    os << "    Assignments: " << qs._swaps << std::endl;
    return os;

}