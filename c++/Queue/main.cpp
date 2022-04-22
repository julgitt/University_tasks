#include "classes.h"

int main() {
    //standard constructor
    cout << ("Testing standard constructor") << endl;
    Queue *first = new Queue(3);
    first->Insert("1 ");
    first->Insert("2 ");
    first->Insert("3 ");
    cout << "length: " << first->Length() << endl;
    cout << ("front: " + first->Front()) << endl;
    cout << ("deleted: " + first->Del()) << endl;
    cout << ("deleted: " + first->Del()) << endl;
    cout << ("front: " + first->Front()) << endl;
    cout << ("deleted: " + first->Del()) << endl;

    first->Insert("4 ");
    cout << "length: " << first->Length() << endl;

    cout << ("front: " + first->Front()) << endl;
    cout << ("deleted: " + first->Del()) << endl;

    //initializer list constructor
    cout << endl << ("Testing initializer list constructor") << endl;
    Queue *second = new Queue({"a", "b"});
    cout << ("front: " + second->Front()) << endl;
    cout << ("deleted: " + second->Del()) << endl;
    cout << ("deleted: " + second->Del()) << endl;

    //copy constructor
    cout << endl << ("Testing copy constructor") << endl;
    //assignment
    second = new Queue({"x", "y"});
    Queue *third = second;
    cout << ("third front: " + third->Front()) << endl;
    cout << ("second front: " + second->Front()) << endl;
    cout << ("deleted: " + second->Del()) << endl;
    cout << ("third front: " + third->Front()) << endl;
    return 0;
}
