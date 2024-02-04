#include <utility>
#include "classes.h"

set_of_variables::~set_of_variables(){
    delete[] array;
}
bool set_of_variables::contains (string name){
    for (int i = 0; i < counter; i++){
        if(array[i].get_key() == name){
            return true;
        }
    }
    return false;
}
void set_of_variables::delete_variable(string name){
    for (int i = 0; i < counter; i++){
        if(array[i].get_key() == name){
            array[i] = array[counter-1];
            counter--;
        }
    }
}
double set_of_variables::get_val(string name){
    for (int i = 0; i < counter; i++){
        if(array[i].get_key() == name){
            return array[i].get_value();
        }
    }
    throw invalid_argument("there is no variable with this name in array\n");
}
void set_of_variables::modify(string name, double change){
    for (int i = 0; i < counter; i++){
        if(array[i].get_key() == name){
            array[i].set_value(change);
            return;
        }
    }
    throw invalid_argument("there is no variable with this name in array\n");
}

set_of_variables :: set_of_variables(int number) : n(number){
    if (n < 0){
        throw invalid_argument ("received negative value");
    }
    this->array = new variable[n];
    this->counter = 0;
}

void set_of_variables :: add_variable(variable var){
    if(counter>=n){
        throw out_of_range ("there is no space in the array\n");
    }
    if (contains(var.get_key()))
        throw invalid_argument ("the array already contains this variable\n");

    array[counter] = var;
    counter++;
}
