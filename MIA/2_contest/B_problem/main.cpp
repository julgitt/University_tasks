#include <iostream>
using namespace std;

int main() {
    int n;
    long long rev_cost, inv_cost;
    cin >> n >> rev_cost >> inv_cost;
    int number_of_zeros_blocks = 0;
    char first_block = '0';
    char current;
    
    int prev = 1;
    
    n--;
    cin >> first_block;
    if (first_block == '0'){
        prev = 0;
        number_of_zeros_blocks++;
    }
    while (n > 0) {
        cin >> current;
        n--;
        if (current == '0' && prev == 1) {
            number_of_zeros_blocks++;
            prev = 0;
        } else if (current == '1') {
            prev = 1;
        }
    }
    
    if (number_of_zeros_blocks == 0){
        cout << 0;
        return 0;
    }
    if (number_of_zeros_blocks == 1){
        cout << inv_cost;
        return 0;
    }

    int rev_num = 0;
    while (number_of_zeros_blocks > 1 &&
            inv_cost * number_of_zeros_blocks + rev_cost * rev_num >
            (number_of_zeros_blocks - 1) * inv_cost + rev_cost * (rev_num + 1)) {
        number_of_zeros_blocks --;
        rev_num++;
    }
    cout << inv_cost * number_of_zeros_blocks + rev_cost * rev_num;
    return 0;
}
