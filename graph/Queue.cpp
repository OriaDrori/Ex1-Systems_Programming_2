//oriasoffer8@gmail.com
#include "Queue.h"
#include <stdexcept> 

namespace graph {

//constructor
Queue::Queue(int size) {
    capacity = size;
    data = new int[capacity];
    start = 0;
    end = -1;
    count = 0;   //number of elements in the queue
}

//destructor
Queue::~Queue() {
    delete[] data;
}

//adds an element to the end of the queue
void Queue::enqueue(int value) {
    if (count == capacity) {
        throw std::runtime_error("Queue overflow");
    }
    end = (end + 1) % capacity;   //advance 'end' to the next position; wraps around to 0 if it reaches the end of the array
    data[end] = value;
    count++;
}

//removes and returns the element at the front of the queue
int Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Queue underflow");
    }
    int value = data[start];
    start = (start + 1) % capacity;  // Advance 'start' to the next position; wraps around to 0 if it reaches the end of the array
    count--;
    return value;
}

//returns true if the queue is empty
bool Queue::isEmpty() const {
    return count == 0;
}

}

