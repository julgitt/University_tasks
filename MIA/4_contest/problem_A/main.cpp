#include <iostream>
using namespace std;
int main() {
    int queues, kids_num;
    cin >> queues;

    for (int q = 0; q < queues; q++) {
        cin >> kids_num;
        int kids_perm[kids_num + 1];
        int days[kids_num + 1];

        for (int i = 1; i <= kids_num; i++) {
            cin >> kids_perm[i];
            days[i] = 1;
        }
        int current;
        int owner;
        for (int i = 1; i <= kids_num; i++){
            owner = kids_perm[i];
            current = kids_perm[owner];
            while (owner != current) {
                current = kids_perm[current];
                days[owner]++;
            }
        }
        cout << endl;
        for (int i = 1; i <= kids_num; i++){
            cout << days[i] << " ";
        }
    }


    return 0;
}
