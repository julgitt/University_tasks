#include <iostream>
#include <limits>
using namespace std;
int main() {
    int ribbon,a,b,c;
    cin >> ribbon;
    cin >> a >> b >> c;

    int t [ribbon + 1];
    t[0] = 0;

    for (int i = 1; i <= ribbon; i++) {
        t[i] = -1;
    }

    for (int j = 0; j <= ribbon - c; j++){
        if (t[j] > -1) {
            if(t[j] + 1 > t[j + c]) {
                t[j + c]  = t[j] + 1;
            }
        }
    }

    for (int j = 0; j <= ribbon - b; j++){
        if (t[j] > -1) {
            if(t[j] + 1 > t[j + b]) {
                t[j + b]  = t[j] + 1;
            }
        }
    }

    for (int j = 0; j <= ribbon - a; j++){
        if (t[j] > -1) {
            if(t[j] + 1 > t[j + a]) {
                t[j + a]  = t[j] + 1;
            }
        }
    }
    cout << t[ribbon];
    return 0;
}
