#include <iostream>
using namespace std;

int main() {
    int num;
    cin >> num;
    int perm[num + 1];
    for (int i = 1; i <= num; i++){
        cin >> perm[i];
    }
    int id;
    int id2;
    int id3;
    for (int i = 1; i <= num; i++){
        id = perm[i];
        id2 = perm[id];
        id3 = perm[id2];
        if (id3 == i){
            printf("YES");
            return 0;
        }
    }
    printf("NO");
    return 0;
}
