#include <iostream>
using namespace std;

int main() {
    int n, a, b;
    int result = 0;

    cin >> n >> a >> b;

    char seat;
    int is_next_to = -1;

    while (n > 0 && a > 0 && b > 0){
        cin >> seat;
        n--;
        if (seat == '*'){
            is_next_to = -1;
            continue;
        }

        if (is_next_to == 1) {
            b--;
            is_next_to = 0;
        } else if (is_next_to == 0) {
            a--;
            is_next_to = 1;
        } else {
            if (a >= b) {
                is_next_to = 1;
                a--;
            } else {
                is_next_to = 0;
                b--;
            }
        }
        result++;
    }

    while (n > 0 && a > 0){
        cin >> seat;
        if (seat == '*' || is_next_to == 1) {
            n--;
            is_next_to = 0;
            continue;
        }
        result++;
        cin >> seat;
        n -= 2;
        a--;
    }

    while (n > 0 && b > 0){
        cin >> seat;
        if (seat == '*' || is_next_to == 0) {
            n--;
            is_next_to = 1;
            continue;
        }
        result++;
        b--;
        cin >> seat;
        n -= 2;
    }
    cout << result;
    return 0;
}