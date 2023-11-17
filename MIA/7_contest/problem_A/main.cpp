#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int test_num;
    cin >> test_num;
    long long count;
    for (int i = 0; i < test_num; i++){
        string s, t;
        cin >> s;
        cin >> t;
        count = pow(2, s.size());

        for (int j = 0; j < t.size(); j++){
            if (t[j] == 'a' and t.size() > 1) {
                count = -1;
                break;
            } else if (t[j] == 'a') {
                count = 1;
            }
        }
        cout << count << "\n";
    }
    return 0;
}
