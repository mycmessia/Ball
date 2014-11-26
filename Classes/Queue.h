//
//  Queue.h
//  Ball
//
//  Created by meiyuchen on 14-11-18.
//
//

#ifndef __Ball__Queue__
#define __Ball__Queue__

#define MAX_CELL 63

struct pathCell {
    int col;
    int row;
    int predecessor;
};

class Queue
{
private:
    pathCell queue[MAX_CELL];
    int tail = 0;
    int head = 0;
public:
    int getHead();
    int getTail();
    
    pathCell getByIndex(const unsigned int index);
    
    pathCell dequeue();
    void enqueue(pathCell pc);
    bool isEmpty();
    void print();
    int size();
};

#endif /* defined(__Ball__Queue__) */
