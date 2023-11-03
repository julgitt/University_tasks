#include <iostream>
#include <algorithm>
using namespace std;

long long int countPrice(long long int id, long long int n, long long int*base){
    long long int costs[n+1];
    for (long long int i = 1; i <= n; i++)
        costs[i - 1] = base[i] + (i * id);

    sort(costs, costs + n);

    long long int result = 0;
    for (long long int i = 0; i < id; i++)
        result += costs[i];

    return result;
}

int main() {
    long long int n;
    cin >> n;
    long long int S;
    cin >> S;
    long long int base_costs[n+1];
    for (long long int i = 1; i <= n; i++){
        cin >> base_costs[i];
    }

    long long int l = 0;
    long long int r = n;
    long long int mid;

    long long int current_id = 0;

    while (l <= r){
        mid = (l + r) / 2;
        if (countPrice(mid, n, base_costs) <= S){
           current_id = mid;
           l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << current_id << " " << countPrice(current_id,n, base_costs);
    return 0;
}
