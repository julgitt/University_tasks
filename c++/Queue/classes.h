
#ifndef QUEUE_CLASSES_H
#define QUEUE_CLASSES_H
#include <iostream>
#include <string>
#include <initializer_list>
using namespace std;

class Queue {
private:
    int capacity, begin = 0, count = 0;
    string *array;

public:
    //constructors
    Queue(int c); //standard
    Queue(); //delegate
    Queue(const initializer_list<string> &list); //initializer list string
    Queue(const Queue &other); //copy
    Queue(Queue &&other) noexcept; //move

    //assignment
    Queue &operator=(const Queue &other);

    Queue &operator=(Queue &&other) noexcept;

    //destructor
    ~Queue();

    //methods
    void Insert(string value);

    string Del();

    string Front();

    int Length() const;
};

#endif //QUEUE_CLASSES_H
