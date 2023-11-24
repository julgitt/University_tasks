#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main() {
    char s[300000];
    scanf("%s", s);
    // is the first character a number divisible by 4
    long long res = ((s[0] - '0') % 4 == 0);
    for (int i = 0; s[i + 1] != '\0'; i++){
        // is the i-th character a number divisible by 4
        if ((s[i + 1] - '0') % 4 == 0)
            res ++;
        // is the substring of i + 1 characters a number divisible by 4
        // substring is divisible by 4 if the two last characters are a number divisible by 4
        int suff = (s[i] - '0') * 10 + (s[i + 1] - '0');
        if(suff % 4 == 0)
            res += i + 1;
    }
    printf("%lld", res);
}
