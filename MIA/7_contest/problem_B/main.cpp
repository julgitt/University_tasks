#include <iostream>
using namespace std;
int main() {
    long long n;
    cin >> n;
    int benches = 5;
    long long current_possibilities;
    current_possibilities = n;
    benches--;

    while (benches > 0 and  n > 1) {
        n--;
        current_possibilities *= n;
        benches--;
    }
    current_possibilities /= 120;
    current_possibilities *= current_possibilities;
    cout << current_possibilities * 120;

    return 0;
}
