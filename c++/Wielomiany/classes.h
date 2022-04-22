
#ifndef QUEUE_CLASSES_H
#define QUEUE_CLASSES_H
#include <iostream>
#include <string>
#include <initializer_list>
using namespace std;

class Wielomian {
private:
    int n;
    double *arr;

public:
    //constructors
    Wielomian (); //standard
    Wielomian (int st, const double wsp[]);
    Wielomian(const initializer_list<double> &list); //initializer list
    Wielomian(const Wielomian &other); //copy
    Wielomian(Wielomian &&other) noexcept; //move

    //assignment
    Wielomian &operator=(const Wielomian &other);

    Wielomian &operator=(Wielomian &&other) noexcept;

    //steam assigment
    friend istream& operator >> (istream &we, Wielomian &w);
    friend ostream& operator << (ostream &wy, const Wielomian &w);

    // operators
    friend Wielomian operator + (const Wielomian &u, const Wielomian &v);
    friend Wielomian operator - (const Wielomian &u, const Wielomian &v);
    friend Wielomian operator * (const Wielomian &u, const Wielomian &v);
    friend Wielomian operator * (const Wielomian &u,double c);
    Wielomian& operator += (const Wielomian &v);
    Wielomian& operator -= (const Wielomian &v);
    Wielomian& operator *= (const Wielomian &v);
    Wielomian& operator *= (double c);
    double operator () (double x) const; // wartość wielomianu dla x
    double operator [] (int i) const; // do odczytu współczynnika
    double& operator [] (int i); // do zapisu współczynnika
    //destructor
    ~Wielomian();
};

#endif //QUEUE_CLASSES_H
