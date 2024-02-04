#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

vector<int64_t> rozklad(int64_t n) {
    vector<int64_t> v;
    int64_t x = abs(n);
    if (n == 0) v.push_back(0);
    if (n == 1) v.push_back(1);
    if (n < 0) v.push_back(-1);

    for (int64_t i = 2; i <= x; i++) {
        while (x % i == 0) {
            v.push_back(i);
            x /= i;
        }
    }
    return v;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cerr << "Nie podano ciagu liter, ktore maja byc rozlozone na czynniki pierwsze \n";
        exit(1);
    }
    vector<int64_t> czynniki;
    bool first;

    for (int i = 1; i < argc; i++) {
        try {
            czynniki = rozklad(stoll(argv[i]));
            cout << stoll(argv[i]) << " = ";
            first = true;

            for (int64_t x: czynniki) {
                if (first) {
                    cout << x;
                    first = false;
                } else
                    cout << " * " << x;
            }
            cout << " \n ";
        }
        catch (const invalid_argument &e) {
            cout << "Podano bledny argument dla funkcji " << e.what() << "\n";
        }
    }
    return 0;
}
