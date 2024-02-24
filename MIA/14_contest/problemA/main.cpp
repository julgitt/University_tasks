#include <iostream>
#include <string>
using namespace std;

int main() {
    string sent, received;
    cin >> sent >> received;

    int position_diff= 0;
    int undefined = 0;

    for (int i = 0; i < sent.length(); i++){
        undefined += (received[i] == '?')? 1 : 0;
        position_diff += (sent[i] == '+')? 1 : -1;

        position_diff -= (received[i] == '+')? 1 : 0;
        position_diff += (received[i] == '-')? 1 : 0;
    }
    int res = 0;
    int combinations = (1 << undefined);
    for (int i = 0; i < combinations; i++)
    {
        int copy = position_diff, k = i;
        for (int j = 1; j <= undefined; j++)
        {
            copy += (k & 1) ? 1 : -1;
            k /= 2;
        }
        res += (copy == 0) ? 1 : 0;
    }


    cout.precision(12);
    cout << fixed << float(res) / float(combinations) << endl;
    return 0;
}
