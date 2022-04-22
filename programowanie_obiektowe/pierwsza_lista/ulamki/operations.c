#include <stdio.h>
#include <stdlib.h>
#include "fractions.h"

void add(Fraction *f, Fraction *e) {
    int denom = lcm(f->denominator, e->denominator); // do wspolnego mianownika
    int num = (denom / f->denominator) * f->numerator + (denom / e->denominator) * e->numerator;
    int divisor = gcd(num, denom);
    e->numerator = num / divisor;
    e->denominator = denom / divisor;
}

void sub(Fraction *f, Fraction *e) {
    int denom = lcm(f->denominator, e->denominator); // do wspolnego mianownika
    int num = (denom / f->denominator) * f->numerator - (denom / e->denominator) * e->numerator;
    int divisor = gcd(num, denom);
    e->numerator = num / divisor;
    e->denominator = denom / divisor;
}

void mult(Fraction *f, Fraction *e) {
    int denom = f->denominator * e->denominator;
    int num = f->numerator * e->numerator;
    int divisor = gcd(num, denom);
    e->numerator = num / divisor;
    e->denominator = denom / divisor;
}

Fraction *divis(Fraction *f, Fraction *e) {
    int denom = f->denominator * e->numerator;
    int num = f->numerator * e->denominator;
    int divisor = gcd(num, denom);
    e->numerator = num / divisor;
    e->denominator = denom / divisor;
}