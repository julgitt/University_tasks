
#ifndef KLASA_ZMIENNA_CLASSES_H
#define KLASA_ZMIENNA_CLASSES_H
#include<iostream>
#include <string>

using namespace std;

class variable {
private:
    string key; //letters, numbers and underscore
    double value{}; // set to zero

public:
    variable();
    variable(string name);
    variable(string name, double val);
    string get_key();
    double get_value() const;
    void set_value(double n);
};

class set_of_variables {
private:
    const int n;
    variable *array;
    int counter;
public:
    set_of_variables(int number);
    ~set_of_variables();
    void add_variable(variable var);
    bool contains (string name);
    void delete_variable(string name);
    double get_val(string name);
    void modify (string name, double change);
};
#endif //KLASA_ZMIENNA_CLASSES_H
