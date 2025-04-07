//oriasoffer8@gmail.com
#ifndef QUEUE_H
#define QUEUE_H

namespace graph {

class Queue {
private:
    int* data;       //dynamic array to store queue elements
    int capacity;    //maximum number of elements the queue can hold
    int start;       //head of the queue
    int end;         //tail of the queue
    int count;       //current number of elements in the queu

public:
    Queue(int size);        //constructor
    ~Queue();               //destructor

    void enqueue(int value);
    int dequeue();
    bool isEmpty() const;
};

}

#endif
