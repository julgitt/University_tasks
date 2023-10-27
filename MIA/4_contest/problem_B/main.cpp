#include <iostream>
using namespace std;
int main() {
    int hairlines, requests, fav_num;

    cin >> hairlines >> requests >> fav_num;

    int h_lengths[hairlines + 1];
    int blocks = 0;
    for (int i = 1; i <= hairlines; i++) {
        cin >> h_lengths[i];
        if (h_lengths[i] > fav_num) {
            if (i == 1 || (i > 1 && h_lengths[i - 1] <= fav_num)) {
                blocks++;
            }
        }
    }

    int type, p, d;
    int prev_len, next_len;
    for (int i = 0; i < requests; i++) {
        cin >> type;
        if (type == 1) {
            cin >> p;
            cin >> d;
            // wczesniej pasmo włosów było większe - nic się nie zmieni
            if (h_lengths[p] > fav_num) {
                continue;
            }
            h_lengths[p] += d;
            // tu może się coś zmienić
            if (h_lengths[p] > fav_num) {
                next_len = 0;
                prev_len = 0;
                if (p + 1 <= hairlines)
                    next_len = h_lengths[p + 1];
                if (p - 1 >= 1)
                    prev_len = h_lengths[p - 1];

                // na poczatku i nastepny wlos mniejszy od ulubionego
                if (p == 1 && next_len <= fav_num){
                    blocks++;
                }
                // na koncu i poprzedni mniejszy
                else if (p == hairlines && prev_len <= fav_num) {
                    blocks++;
                }
                // poprzedni i nastepny mniejszy
                else if (p > 1 && prev_len <= fav_num && p <= hairlines && next_len <= fav_num) {
                    blocks++;
                } // poprzedni i nastepny wiekszy
                else if (p > 1 && prev_len > fav_num && p < hairlines && next_len > fav_num) {
                    blocks--;
                }
            }
        } else {
            cout << blocks << endl;
        }

    }

    return 0;
}
