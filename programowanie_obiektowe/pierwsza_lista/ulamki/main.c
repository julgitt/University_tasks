#include <stdio.h>
#include <stdlib.h>
#include "fractions.h"

int main() {
    Fraction f = *new_fraction(3, 4);
    Fraction e = *new_fraction(3, 4);
    show(&f);
    show(addition(&f, &e));
    show(multiplication(&f, &e));
    show(subtraction(&f, &e));
    show(division(&f, &e));

    //second method
    add(&f, &e);
    show(&e);
    sub(&f, &e);
    show(&e);
    mult(&f, &e);
    show(&e);
    divis(&f, &e);
    show(&e);
    return 0;
}