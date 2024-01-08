#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int n;
  cin >> n;
  int current; 
  int current_max = -1000000;
  bool flag = false;

  for (int i = 0; i < n; i++){
    cin >> current;
    flag = false;
    if (current > current_max) {
        for (int j = 0; j <= sqrt(current); j++) {
            if (pow(j,2) == current) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            current_max = current;
        }
    }
  }
  cout << current_max;
} 