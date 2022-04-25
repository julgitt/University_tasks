#ifndef PRIORITY_QUEUE_QUEUE_H
#define PRIORITY_QUEUE_QUEUE_H
extern int len;
struct heap{
    int priority; //value
    int key; //index
};
void swap(int *a, int *b);
int top(struct heap *queue);
int top_priority(struct heap queue[]);
void push(struct heap *queue, int newNum);
void pop(struct heap queue[]);
void dequeue(struct heap *queue);
void printQueue(struct heap *queue);
#endif //PRIORITY_QUEUE_QUEUE_H