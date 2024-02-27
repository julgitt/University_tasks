// task decription: https://codeforces.com/group/yGSr3ZYUig/contest/499392/problem/A
#include <iostream>
#include <cmath>
using namespace std;

int main() {
  int t;
  cin >> t;
  int x[3], y[3];

  for (int i = 0; i < t; i++){
      for (int j = 0; j < 3; j++) {
          cin >> x[j] >> y[j];
      }
      if (y[0] > y[2] && y[0] == y[1]){
          cout << abs(x[0] - x[1]) << endl;
      }
      else if (y[0] > y[1] && y[0] == y[2]) {
          cout << abs(x[0] - x[2]) << endl;
      }
      else if (y[1] > y[0] && y[1] == y[2]) {
          cout <<  abs(x[1] - x[2]) << endl;
      } else {
            cout << 0 << endl;
      }
  }
}
