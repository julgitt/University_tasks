#include "classes.h"

//constructors
Wielomian::Wielomian() {
    this->n = 0;
    this->arr = new double[n+1];
    this->arr[0] = 1.0;
}

Wielomian::Wielomian(int st, const double wsp[]) {
    if (st < 0)
        throw invalid_argument("Stopien nie moze byc ujemny");
    this->n = st;
    this->arr = new double[n+1];

    for (int i = 0; i <= n; i++)
        this->arr[i] = wsp[i];
}

Wielomian::Wielomian(const initializer_list<double> &list) {
    this->n = (int) list.size()-1;
    this->arr = new double[n+1];
    int i = 0;
    initializer_list<double>::iterator it;
    for (it = list.begin(); it != list.end(); ++it) {
        arr[i] = *it;
        i++;
    }
} //initializer list string

Wielomian::Wielomian(const Wielomian &other) : n(other.n){
    this->arr = new double[n+1];
    std::copy(other.arr, other.arr + other.n + 1, this->arr);
} //copy

Wielomian::Wielomian(Wielomian && other) noexcept
:arr(nullptr),n(0) {
    arr = other.arr;
    n = other.n;
    other.n = 0;
    other.arr = nullptr;
} //move

//destructor
Wielomian::~Wielomian() {
    delete[] arr;
}

//assignment operator
Wielomian & Wielomian::operator= (const Wielomian &other) {
    if (this != &other) {
        delete[] arr;
        n = other.n;
        arr = new double[n+1];
        std::copy(other.arr, other.arr + other.n +1, this->arr);
    }
    return *this;
}

Wielomian & Wielomian::operator= (Wielomian && other) noexcept {
    if (this != &other) {
        delete[] arr;
        n = other.n;
        arr = other.arr;
        other.n = 0;
        other.arr = nullptr;
    }
    return *this;
}
istream& operator >> (istream &in, Wielomian &w){
    cout << "Podaj stopien wielomianu: " <<endl;
    in >> w.n;
    if (w.n< 0)
        throw invalid_argument("Wspolczynnik nie moze byc ujemny");
    cout << "Podaj kolejne wspolczynniki wielomianu: "<<endl;
    for (int i = 0; i <= w.n; i++){
        in >> w.arr[i];
    }
    return in;
}
ostream& operator << (ostream &out, const Wielomian &w){
    out << "st."<< w.n << " w(x) = ";
    for (int i = 0; i <= w.n; i++){
        if(i == 0)
            out << w.arr[i] << "x" <<"^"<<i;
        else
            out <<" + " << w.arr[i] << "x" <<"^"<<i;
    }

    return out;
}

// operators
Wielomian operator + (const Wielomian &u, const Wielomian &v){
    int n = max(u.n, v.n);
    double array[n+1];
    int i = 0;

    for (; i <= min(u.n,v.n); i++)
        array[i] = u.arr[i] + v.arr[i];

    for (; i <= u.n; i++)
        array[i] = u.arr[i];

    for (; i <= v.n; i++)
        array[i] = v.arr[i];

    return {n, array};
}
Wielomian operator - (const Wielomian &u, const Wielomian &v){
    int n = max(u.n, v.n);
    double array[n+1];
    int i = 0;

    for (; i <= min(u.n,v.n); i++)
        array[i] = u.arr[i] - v.arr[i];

    for (; i <= u.n; i++)
        array[i] = u.arr[i];

    for (; i <= v.n; i++)
        array[i] = -v.arr[i];

    return {n, array};
}
Wielomian operator * (const Wielomian &u, const Wielomian &v){
    int n = u.n + v.n;
    double array[n+1];
    //initialization of array
    for (int i = 0; i <= n; i++)
        array[i] = 0;

    for (int i = 0; i <= u.n; i++)
        for (int j = 0; j <= v.n; j++)
            array[i+j] += u.arr[i] * v.arr[j];

    return {n, array};
}
Wielomian operator * (const Wielomian &u, double c) {
    int n = u.n;
    double array[n+1];

    for (int i = 0; i <= u.n; i++)
            array[i] = u.arr[i] * c;

    return {n, array};
}
Wielomian & Wielomian::operator+=(const Wielomian &v){
    *this = *this+v;
    return *this;
}

Wielomian & Wielomian::operator-= (const Wielomian &v){
    *this = *this-v;
    return *this;
}
Wielomian & Wielomian::operator*= (const Wielomian &v){
    *this = *this*v;
    return *this;
}

Wielomian & Wielomian::operator*= (double c){
    *this = *this*c;
    return *this;
}

double Wielomian::operator () (double x) const{
    double result = arr[0];

    for(int i=1;i<=n;i++)
        result = result*x + arr[i];

    return result;
}
double Wielomian::operator [] (int i) const{
    return arr[i];
}
double& Wielomian::operator [] (int i){
    return arr[i];
}
