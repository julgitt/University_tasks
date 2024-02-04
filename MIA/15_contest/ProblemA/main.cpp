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
    	if (y[1] > y[3] && y[1] == y[2]){
    		cout << abs(x[1] - x[2]);
    	}
    	else if (y[1] > y[2] && y[1] == y[3]) {
    		cout << abs(x[1] - x[3]);
    	}
    	else if (y[2] > y[1] && y[2] == y[3]) {
    		cout <<  abs(x[2] - x[3]);	
    	} else {
    		cout << 0;	
    	}
   
  }
} 
