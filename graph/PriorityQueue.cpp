//oriasoffer8@gmail.com
#include "PriorityQueue.h"
#include <stdexcept>
#include <climits>

namespace graph {

//constructor
PriorityQueue::PriorityQueue(int cap) : capacity(cap), size(0) {
    size = 0;
    data = new Node[capacity];
    for (int i = 0; i < capacity; ++i) {    //initialization
        data[i].vertex = -1;
        data[i].priority = INT_MAX;
    }
}

//destructor
PriorityQueue::~PriorityQueue() {
    delete[] data;   
}

void PriorityQueue::swap(int i, int j) {
    Node temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

//maintains the min-heap property by moving a node up. called after inserting a new node
void PriorityQueue::bubbleUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (data[index].priority >= data[parent].priority)
            break;
        swap(index, parent);   //swap with parent if current is smaller
        index = parent;        //move up
    }
}

//Maintains the min-heap property by moving a node down.  called after removing the root and moving the last node to root.
void PriorityQueue::bubbleDown(int index) {
    int left, right, smallest;
    while (true) {
        left = 2 * index + 1;     //index of left child
        right = 2 * index + 2;    //index of right child
        smallest = index;         //assume current is smallest
        //compare with left child
        if (left < size && data[left].priority < data[smallest].priority)
            smallest = left;
        //compare with right child
        if (right < size && data[right].priority < data[smallest].priority)
            smallest = right;

        if (smallest == index)
            break;   //no need to move down

        swap(index, smallest);    //swap with the smallest child
        index = smallest;
    }
}

//inserts a new node into the priority queue.
void PriorityQueue::push(int vertex, int priority) {
    if (size == capacity){
        throw std::overflow_error("PriorityQueue full");
    }
    data[size] = {vertex, priority};
    bubbleUp(size);
    size++;
}

//returns true if the priority queue has no elements
bool PriorityQueue::isEmpty() const {
    return size == 0;
}

//removes and returns the vertex with the smallest priority
int PriorityQueue::pop() {
    if (isEmpty()){
        throw std::underflow_error("PriorityQueue empty");
    }
    int top = data[0].vertex;
    data[0] = data[size - 1];
    size--;
    bubbleDown(0);
    return top;
}

//checks whether a specific vertex exists in the priority queue
bool PriorityQueue::contains(int vertex) const {
    for (int i = 0; i < size; ++i) {
        if (data[i].vertex == vertex)
            return true;
    }
    return false;
}

//lowers the priority of a given vertex if the new priority is smaller
void PriorityQueue::decreaseKey(int vertex, int newPriority) {
    for (int i = 0; i < size; ++i) {
        if (data[i].vertex == vertex) {
            if (newPriority < data[i].priority) {
                data[i].priority = newPriority;
                bubbleUp(i);
            }
            break;
        }
    }
}

} 
