/**
 * @file mergesort.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-04-29
 * 
 * @copyright Copyright (c) 2023
 * 
 * Source of imlpementation: https://leetcode.com/problems/sort-list/solutions/997518/java-natural-merge-sort-of-linked-list-o1-space/
 * 
 */

#include<iostream>
#include<memory>
#include"queue.h"
#include"mergesort.h"

NaturalMergeSort::Endpoints::Endpoints(
        std::shared_ptr<MergeNode> left,
        std::shared_ptr<MergeNode> right,
        int segment_size
)
{
        this->left = left;
        this->right = right;
        this->size = segment_size;
};

NaturalMergeSort::NaturalMergeSort(Queue<int> q)
{
    while(q.size())
    {
        enqueue(q.dequeue());
    }
}

// NaturalMergeSort::~NaturalMergeSort()
// {
//     std::cout << "destroying merge: " << _size << std::endl;
//     _tail = nullptr;
//     if (_head) _head->~MergeNode();

//     // while(current)
//     // {
//     //     next = current->next;
//     //     std::cout << "deleting " << current->data << std::endl;
//     //     current->~MergeNode();
//     //     current = next;
//     // }
// }

void NaturalMergeSort::enqueue(int x)
{
    node_pointer new_node = std::shared_ptr<MergeNode>(new MergeNode(x));
    // linked list is empty
    if (!_head)
    {
        _head = _tail = new_node;
    }
    else
    {
        _tail->next = new_node;
        _tail = new_node;
    }

    _size++;
}


void NaturalMergeSort::sort()
{
    Endpoints ep = mergesort(_head);
    _head = ep.left;
    _tail = ep.right;

}

NaturalMergeSort::Endpoints NaturalMergeSort::mergesort(node_pointer node)
{
    if(!node || !node->next )
    {
        Endpoints ep(_head, _tail, _size);
        return ep;
    }
    int merged_count = 2;
    Endpoints merged;
    while(merged_count > 1)
    {
        node_pointer next_head = node;
        node_pointer last_tail = nullptr;
        node = nullptr;
        merged_count = 0;
        while (next_head != nullptr)
        {
            Endpoints seg1 = next_partition(next_head);
            Endpoints seg2 = next_partition(seg1.right->next);
            
            next_head = (!seg2.right) ? nullptr : seg2.right->next;
            merged = merge(seg1, seg2);
            
            if (last_tail != nullptr) last_tail->next = merged.left;
            last_tail = merged.right;
            if (!node) node = merged.left;
            merged_count++;
        }
    }
    return merged;
}

NaturalMergeSort::Endpoints NaturalMergeSort::merge(Endpoints& seg1, Endpoints& seg2)
{
    if(!seg2.left) return seg1;
    node_pointer dummy = std::shared_ptr<MergeNode>(new MergeNode(0));
    node_pointer node1  = seg1.left;
    node_pointer node2 = seg2.left;
    node_pointer node = dummy;
    int size1 = seg1.size;
    int size2 = seg2.size;
    while (size1 > 0 && size2 > 0)
    {
        _comparisons++;
        if (node1->data <= node2->data)
        {
            node->next = node1;
            node1 = node1->next;
            size1--;
            _exchanges++;
        }
        else 
        {
            node->next = node2;
            node2 = node2->next;
            size2--;
            _exchanges++;
        }
        node = node->next;
    }
    node_pointer tail = node;
    if (size1 > 0)
    {
        node->next = node1;
        tail = seg1.right;
        _exchanges++;
    }
    else if (size2 > 0)
    {
        node->next = node2;
        tail = seg2.right;
        _exchanges++;
    }
    tail->next = nullptr;
    Endpoints ep (dummy->next,tail, seg1.size + seg2.size);
    return ep;
}

NaturalMergeSort::Endpoints NaturalMergeSort::next_partition(
    std::shared_ptr<MergeNode> left
)
{
    node_pointer curr = left;
    
    if (!curr)
    { 
        Endpoints ep (nullptr, nullptr, 0);
        return ep;
    }
    int segment_size = 1;
    while (curr)
    {
        if(curr->next == nullptr)
        {
            break;
        }
        _comparisons++;
        if (curr->data > curr->next->data)
        {
            break;
        }
        curr = curr->next;
        segment_size++;
        
    }
    Endpoints ep (left, curr, segment_size);
    return ep;
}

void NaturalMergeSort::write_output(std::ostream& os)
{
    node_pointer curr = _head;
    while(curr)
    {
        os << curr->data << std::endl;
        curr = curr->next;
    }
}

std::ostream& operator<<(std::ostream& os, NaturalMergeSort& merge)
{
    os << "Mergesort:" << std::endl;
    os << "    Dataset Size: " << merge._size << std::endl;
    os << "    Comparisons: " << merge._comparisons << std::endl;
    os << "    Exchanges: " << merge._exchanges << std::endl;
    return os;
}
