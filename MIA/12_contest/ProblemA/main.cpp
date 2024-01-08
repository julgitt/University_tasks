#include <iostream>
#include <cmath>

using namespace std;

int main() {
  int t;
  cin >> t;
  int a, b, c; 

  for (int i = 0; i < t; i++){
    cin >> a >> b >> c;
    if (c % 2 == 0) {
      cout << ((a > b) ? "First\n" : "Second\n");
    } else {
      cout << ((a >= b) ? "First\n" : "Second\n");
    }
  }

} 