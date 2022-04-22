#include "classes.h"

int main() {
    //first
    Wielomian w = Wielomian({3, 4, 5});
    cout << w <<endl;

    //second
    Wielomian u = Wielomian({4, 3, 5, 7});
    cout << u<<endl;

    //arithmetic
    Wielomian v = u + w;
    cout << v<<endl;
    cout << u - w<<endl;
    cout << u * w<<endl;
    cout << u * 2<<endl;

    //horner
    cout << u(1)<<endl;

    cout << u[1] <<endl;

    cin >> w;
    cout << w <<endl;
    return 0;
}
