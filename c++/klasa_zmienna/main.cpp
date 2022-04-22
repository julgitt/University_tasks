#include "classes.h"

int main() {
    //tworzenie zmiennych
    const variable *a = new variable();
    const variable *b = new variable("first");
    const variable *c = new variable("second", 0.24);
    const variable *d = new variable("third", 1.55);
    const variable *e = new variable("fourth", 0.55);

    set_of_variables *array = new set_of_variables(4);
    array->add_variable(*a);
    array->add_variable(*b);
    array->add_variable(*c);
    array->add_variable(*d);
    //array->add_variable(*e);

    cout << "the first variable value: " << array->get_val("first") << endl;
    cout << "the second variable value: " << array->get_val("second") << endl;
    cout << "is non-existent variable contained in the array: " << array->contains("non-existent") << endl;
    cout << "is the first variable contained in the array: " <<array->contains("first") << endl;
    array->delete_variable("first");
    cout << "is the first variable contained in the array after it has been removed: " << array->contains("first") << endl;
    cout << "the third variable value: " << array->get_val("third") << endl;
    array->modify("third", 21.33);
    cout <<"the third variable value after modify: " <<  array->get_val("third") << endl;

    return 0;
}