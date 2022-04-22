#include <stdio.h>
#include <stdlib.h>
#include "fractions.h"

int gcd(int a, int b) {
    int t;
    while (b != 0) {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int lcm(int a, int b) //least common multiple
{
    return a / (gcd(a, b)) * b;
}

Fraction *new_fraction(int num, int denom) {
    Fraction *pnew = malloc(sizeof(Fraction));
    if (!pnew) return NULL;
    int divisor = gcd(num, denom);
    pnew->numerator = num / divisor;
    pnew->denominator = denom / divisor;
    return pnew;
}

void show(Fraction *f) {
    if (f->denominator == 0)
        printf("division by zero!\n");
    else if (f->denominator == 1)
        printf("%d\n", f->numerator);
    else
        printf("%d / %d = %f\n", f->numerator, f->denominator, (float) f->numerator / (float) f->denominator);
}

Fraction *addition(Fraction *f, Fraction *e) {
    Fraction *pointer;
    pointer = malloc(sizeof(Fraction));
    if (!pointer) return NULL;

    int denom = lcm(f->denominator, e->denominator); // do wspolnego mianownika
    int num = (denom / f->denominator) * f->numerator + (denom / e->denominator) * e->numerator;
    int divisor = gcd(num, denom);
    pointer->numerator = num / divisor;
    pointer->denominator = denom / divisor;
    return pointer;
}

Fraction *subtraction(Fraction *f, Fraction *e) {
    Fraction *pointer;
    pointer = malloc(sizeof(Fraction));
    if (!pointer) return NULL;

    int denom = lcm(f->denominator, e->denominator); // do wspolnego mianownika
    int num = (denom / f->denominator) * f->numerator - (denom / e->denominator) * e->numerator;
    int divisor = gcd(num, denom);
    pointer->numerator = num / divisor;
    pointer->denominator = denom / divisor;
    return pointer;
}

Fraction *multiplication(Fraction *f, Fraction *e) {
    Fraction *pointer;
    pointer = malloc(sizeof(Fraction));
    if (!pointer) return NULL;

    int denom = f->denominator * e->denominator;
    int num = f->numerator * e->numerator;
    int divisor = gcd(num, denom);
    pointer->numerator = num / divisor;
    pointer->denominator = denom / divisor;
    return pointer;
}

Fraction *division(Fraction *f, Fraction *e) {
    Fraction *pointer;
    pointer = malloc(sizeof(Fraction));
    if (!pointer) return NULL;

    int denom = f->denominator * e->numerator;
    int num = f->numerator * e->denominator;
    int divisor = gcd(num, denom);
    pointer->numerator = num / divisor;
    pointer->denominator = denom / divisor;
    return pointer;
}