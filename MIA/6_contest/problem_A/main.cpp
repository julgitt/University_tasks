#include <iostream>
#include<string>
using namespace std;

int main() {
    int n;
    cin >> n;
    string current;
    int three_sum;
    int zero;
    int four;
    int sum;
    for (int i = 0; i < n; i++) {
        cin >> current;
        zero = 0;
        three_sum = 0;
        four = 0;
        for (int j = 0; j < current.size(); j++) {
            if (current[j] == '0')
                zero = 1;
            three_sum += (int)current[j];
            if((int)current[j] % 2 == 0 ) {
                four ++;
            }
        }
        if (zero == 1 && three_sum % 3 == 0 && four >= 2)
            printf("red\n");
        else
            printf("cyan\n");
    }
    return 0;
}
