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
            _first_pivot = false;
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
    Stack<Tuple> stack {};
    Tuple t {low, high};
    stack.push(t);
    while (!stack.is_empty())
    {
        _comparisons++;
        t = stack.pop();
        if (t.a < t.b)
        {
            _comparisons++;
            if ((t.b - t.a + 1) <= _partition)
            {
                insertion_sort(t.a, t.b);
            }
            else
            {
                Tuple pivot = partition(t.a, t.b);

                Tuple low_partition {t.a, pivot.a};
                Tuple high_partition {pivot.b, t.b};
                stack.push(low_partition);
                stack.push(high_partition);
            }
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
    while (left <= right)
    {
        _comparisons += 1;
        while((left <= right) && (_data[left] < pivot))
        {
            left++;
            _comparisons++;
        }
        _comparisons++;
        while((left <= right) && (_data[right] > pivot))
        {
            right--;
            _comparisons++;
        }
        if (left <= right)
        {
            swap(left, right);
            left++;
            right--;
        }
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
    if (_data[b] >= _data[a] && _data[b] >= _data[c])
    {
        _comparisons += 2;
        return (_data[a] >= _data[c]) ? a : c;
    }
    if (_data[a] >= _data[b] && _data[a] >= _data[c])
    {
        _comparisons += 3;
        return (_data[b] >= _data[c]) ? b : c;
    }
    _comparisons += 3;
    return (_data[a] >= _data[b]) ? a : b;
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

void QuickSort::write_summary(std::ostream& os)
{
    os << "QuickSort" << ",";
    os << _partition << ",";
    os << _first_pivot << ",";
    os << _comparisons << ",";
    os << _swaps << std::endl;
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