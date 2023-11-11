#include <iostream>
#include <math.h>
using namespace std;

const int SQRT_MAX = 1000001;
bool prime[SQRT_MAX];

void sito() {
    prime[0] = true;
    prime[1] = true;
    for (int i = 2; i*i<=SQRT_MAX; i++) {

        if(!prime[i])
            for (int j = i * i ; j <= SQRT_MAX; j += i)
                prime[j] = true;
    }
}

int main() {
    int n;
    cin >> n;
    long long current;
    long long sq;
    sito();

    for ( int i = 0; i < n; i++){
        cin >> current;
        sq = sqrt(current);
        if (sq * sq == current && !prime[sq])
            printf("YES\n");
        else
            printf("NO\n");
    }

    return 0;
}
