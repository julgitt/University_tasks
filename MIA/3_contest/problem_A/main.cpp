#include <iostream>
using namespace std;
int main() {
    int tests, n, m;
    char current;
    cin >> tests;

    for (int i = 0; i < tests; i++){
        cin >> n;
        cin >> m;
        int arr [4][m] ;
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                arr[k][j] = 0;
            }
        }

        for(int j = 0; j < n; j++){
            for(int k = 0; k < m; k++){
                cin >> current;
                if (current == 'v') {
                    arr[0][k] = 1;
                } else if (current == 'i') {
                    arr[1][k] = 1;
                } else if (current == 'k') {
                    arr[2][k] = 1;
                } else if (current == 'a') {
                    arr[3][k] = 1;
                }
            }
        }
        int col = 0;
        int cur = 0;
        while (col < m) {
            if (cur == 4) break;
            if (arr[cur][col] == 1){
                cur++;
            }
            col++;
        }
        if (cur == 4) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
