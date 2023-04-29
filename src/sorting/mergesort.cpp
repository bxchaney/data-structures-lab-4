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
        new_node->prev = _tail;
        _tail = new_node;
    }

    _size++;
}


void MergeSort::sort()
{
    Endpoints ep = next_partition(_head);
    // check if the list is trivially sorted
    _comparisons += 3;
    if ((ep.left == _head) && (ep.right == _tail))
    {
        return;
    }
    merge(ep, Endpoints{ep.right->next, _tail});

}

void MergeSort::merge(Endpoints lhs, Endpoints rhs)
{
    // merging logic
    node_pointer left = lhs.left;
    node_pointer right = rhs.left;
    while (left != lhs.right && right != rhs.right)
    {
        if (left->data < right->data)
        {
            node_pointer next_right = right->next;
            move_behind(left, right);
            right = next_right;
            left = left->next;
        }
        else 
        {
            node_pointer next_left = left->next;
            move_behind(right, left);
            left = next_left;
            right = right->next;
        }
    }

    //either left or right (or both) have one node remaining
    
    // exactly one partition has one node remaining
    
    if (!(left == lhs.right && right == rhs.right))
    {
        // left partition has one node remaining
        if (left == lhs.right)
        {
            while(right != rhs.right)
            {
                
            }
        }
    }
    
    // one node remaining in each partition
        
    if (left->data < right->data)
    {
        move_behind(left, right);
    }
    else
    {
        move_behind(right, left);
    }
    



    // check if completely sorted
    if (lhs.left == _head && lhs.right == _tail) return;
    Endpoints ep = next_partition(lhs.right->next);
    merge(lhs, ep);
}

Endpoints MergeSort::next_partition(
    std::shared_ptr<MergeNode> left
)
{
    node_pointer curr = left;
    while (curr)
    {
        if(curr->next == nullptr) break;
        if (curr->data > curr->next->data)
        {
            break;
        }
        curr = curr->next;
    }
    return Endpoints{left, curr};
}
