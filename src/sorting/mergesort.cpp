#include<iostream>
#include<memory>
#include"queue.h"
#include<mergesort.h>

MergeSort::MergeSort(Queue<int> q)
{
    while(q.size())
    {
        enqueue(q.dequeue());
    }
}

MergeSort::~MergeSort()
{
    node_pointer current = _head;
    node_pointer next;
    while(current)
    {
        next = current->next;
        current->~MergeNode();
        current = next;
    }
}

void MergeSort::enqueue(int x)
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


void MergeSort::sort()
{
    Endpoints ep = mergesort(_head);
    _head = ep.left;
    _tail = ep.right;

}

Endpoints MergeSort::mergesort(node_pointer node)
{
    if(!node || !node->next ) return Endpoints{_head, _tail, _size};
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
            
            next_head = seg2.right->next;
            merged = merge(seg1, seg2);
            
            if (last_tail != nullptr) last_tail->next = merged.left;
            last_tail = merged.right;
            if (!node) node = merged.left;
            merged_count++;
        }
    }
    return merged;
}

Endpoints MergeSort::merge(Endpoints& seg1, Endpoints& seg2)
{
    if(!seg2.left) return seg1;
    node_pointer dummy = std::shared_ptr<MergeNode>(new MergeNode(0));
    node_pointer node1 {seg1.left}, node2{seg2.left}, node {dummy};
    int size1 {seg1.size}, size2{seg2.size};
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
    return Endpoints{dummy->next,tail, seg1.size + seg2.size};
}

Endpoints MergeSort::next_partition(
    std::shared_ptr<MergeNode> left
)
{
    node_pointer curr = left;
    
    if (!curr) return Endpoints{nullptr, nullptr, 0};
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
    return Endpoints{left, curr, segment_size};
}

void MergeSort::write_output(std::ostream& os)
{
    node_pointer curr = _head;
    while(curr)
    {
        os << curr->data << std::endl;
        curr = curr->next;
    }
}

std::ostream& operator<<(std::ostream& os, MergeSort& merge)
{
    os << "Mergesort:" << std::endl;
    os << "    Dataset Size: " << merge._size << std::endl;
    os << "    Comparisons: " << merge._comparisons << std::endl;
    os << "    Exchanges: " << merge._exchanges << std::endl;
}
