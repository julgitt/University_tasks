#include <iostream>
#include <algorithm>
using namespace std;

int binsearch(int *a, int n, int el) {
    int left = 0;
    int right = n - 1;
    int mid = 0;

    while (left <= right) {
        mid = left + (right - left) / 2;

        if (a[mid] <= el) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return a[mid] <= el? mid : mid - 1;
}

int main() {
    int n, m;
    cin >> n >> m;

    int a[n];
    int b[m];

    for (int i = 0; i < n; i++){
        cin >> a[i];
    }

    for (int i = 0; i < m; i++){
        cin >> b[i];
    }

    sort(a,a + n);

    for (int i = 0; i < m; i++) {
        cout << binsearch(a, n, b[i]) + 1 << " ";
    }
    return 0;
}
