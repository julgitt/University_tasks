#include "classes.h"

//constructors
Queue::Queue(int c) {
    if (c < 0) {
        throw invalid_argument("capacity cannot be lower than zero");
    }
    this->capacity = c;
    this->array = new string[capacity];
}

Queue::Queue() : Queue(1){}//delegate

Queue::Queue(const initializer_list<string> &arr) {
    this->capacity = (int) arr.size();
    this->array = new string[capacity];
    this->begin = 0;
    initializer_list<string>::iterator it;
    for (it = arr.begin(); it != arr.end(); ++it) {
        array[count] = *it;
        count++;
    }
} //initializer list string

Queue::Queue(const Queue &other)
: capacity(other.capacity), begin(other.begin), count(other.count) {
    this->array = new string[capacity];
    std::copy(other.array, other.array + other.count, this->array);
} //copy

Queue::Queue(Queue && other) noexcept
:array(nullptr),capacity(0) {
    array = other.array;
    capacity = other.capacity;
    other.capacity = 0;
    other.begin = 0;
    other.count = 0;
    other.array = nullptr;
} //move

//destructor
Queue::~Queue() {
    delete[] array;
}

//assignment operator
Queue & Queue::operator= (const Queue &other) {
    if (this != &other) {
        delete[] array;
        capacity = other.capacity;
        begin = other.begin;
        count = other.count;
        array = new string[capacity];
        std::copy(other.array, other.array + other.capacity, array);
    }
    return *this;
}

Queue & Queue::operator= (Queue && other) noexcept {
    if (this != &other) {
        delete[] array;
        capacity = other.capacity;
        begin = other.begin;
        count = other.count;
        array = other.array;
        other.capacity = 0;
        other.begin = 0;
        other.count = 0;
        other.array = nullptr;
    }
    return *this;
}

//methods
void Queue::Insert(string value) {
    if (count >= capacity)
        throw out_of_range("There is no space in the queue");

    array[(begin + count) % capacity] = value;
    count++;
}

string Queue::Del() {
    if (count == 0)
        throw out_of_range("The queue is empty, there is nothing to delete");

    string result = array[begin];
    begin = (begin + 1) % capacity;
    count--;
    return result;
}

string Queue::Front() {
    if (count == 0)
        throw out_of_range("The queue is empty");
    return array[begin];
}

int Queue::Length() const {
    return count;
}