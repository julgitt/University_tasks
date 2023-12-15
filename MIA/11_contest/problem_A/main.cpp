#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    int snack_size = 0;
    int counter = n;
    priority_queue<int> queue;

    for (int i = 1; i <= n; i++) {
        cin >> snack_size;
        queue.push(snack_size);
        while (queue.size() != 0 && queue.top() >= counter) {
            cout << queue.top() << " ";
            queue.pop();
            counter--;
        }
        cout << endl;
    }

    return 0;
}