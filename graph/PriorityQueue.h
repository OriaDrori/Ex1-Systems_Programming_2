//oriasoffer8@gmail.com
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

namespace graph {

class PriorityQueue {
private:
    struct Node {
        int vertex;
        int priority;
    };
    Node* data;
    int capacity;          //maximum number of elements that can be stored
    int size;              //current number of elements in the queue
    void swap(int i, int j);
    void bubbleUp(int index);
    void bubbleDown(int index);

public:
    PriorityQueue(int cap = 100);    //constructor initializes with optional capacity
    ~PriorityQueue();                //destructor

    void push(int vertex, int priority);
    int pop();
    bool isEmpty() const;
    void decreaseKey(int vertex, int newPriority);
    bool contains(int vertex) const;
};

}

#endif // PRIORITY_QUEUE_H
