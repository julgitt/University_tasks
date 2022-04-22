#ifndef ULAMKI_FRACTIONS_H
#define ULAMKI_FRACTIONS_H

typedef struct Fraction {
    int numerator; //licznik
    int denominator; //mianownik
} Fraction;

int gcd(int a, int b);

int lcm(int a, int b);

Fraction *new_fraction(int num, int denom);

void show(Fraction *f);

Fraction *addition(Fraction *f, Fraction *e);

Fraction *subtraction(Fraction *f, Fraction *e);

Fraction *multiplication(Fraction *f, Fraction *e);

Fraction *division(Fraction *f, Fraction *e);

void add(Fraction *f, Fraction *e);

void sub(Fraction *f, Fraction *e);

void mult(Fraction *f, Fraction *e);

Fraction *divis(Fraction *f, Fraction *e);

#endif //ULAMKI_FRACTIONS_H
