#include <stdio.h>
#include"queue.h"

int len = 0;

inline void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}

int top(struct heap queue[])
{
    return queue[0].key;
}
int top_priority(struct heap queue[])
{
    return queue[0].priority;
}
void heapify(struct heap queue[], int i) // For Re-Balance the tree
{
    if (len>1)
    {
        int largest = i;
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        if (l < len && queue[l].priority > queue[largest].priority)
            largest = l;
        if (r < len && queue[r].priority > queue[largest].priority)
            largest = r;
        if (largest != i)
        {
            swap(&queue[i].priority, &queue[largest].priority);
            swap(&queue[i].key, &queue[largest].key);
            heapify(queue, largest);
        }
    }
}
void push(struct heap queue[], int newNum) // For adding new element
{
    if (len == 0)
    {
        queue[0].priority = newNum;
        queue[0].key = 0;
        len ++;
    }
    else
    {
        queue[len].priority = newNum;
        queue[len].key = len;
        len ++;
        for (int i = len/2-1; i >= 0 ; i--)
        {
            heapify(queue, i);
        }
    }
}

void pop(struct heap queue[]) // For deleting max element
{
    swap(&queue[0].priority,&queue[len-1].priority);
    swap(&queue[0].key,&queue[len-1].key);
    len -= 1;
    heapify(queue, 0);
    for (int i = len/2-1; i >= 0 ; i--)
    {
        heapify(queue, i);
    }
}

void dequeue(struct heap queue[]) // For printing sorted array
{
    while (len>0)
    {
        printf("%d\n",top_priority(queue));
        pop(queue);
    }
}

void printQueue(struct heap queue[]) // For printing the elements
{
    for (int i = 0 ; i < len ; ++i)
        printf("key: %d, priority: %d\n" , queue[i].key, queue[i].priority);
    printf("\n");
}