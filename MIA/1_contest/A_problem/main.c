#include <stdio.h>

int main() {
    int num_tests = 0;
    scanf("%d", &num_tests);
    int result[num_tests];
    int m = 0, n = 0;
    int max;
    int current;
    for ( int i = 0; i < num_tests; i++ ){
        scanf("%d %d", &m, &n);
        int chessboard[m][n];
        max = 0;
        for (int row = 0; row < m; row++){
            for (int col = 0; col < n; col++) {
                scanf("%d", &chessboard[row][col]);
            }
        }

        for (int row = 0; row < m; row++){
            for (int col = 0; col < n; col++) {
                current = chessboard[row][col];
                int x = row;
                int y = col;
                while (x > 0 && y > 0) {
                    x--;
                    y--;
                    current += chessboard[x][y];
                }
                x = row;
                y = col;
                while (x < m - 1 && y > 0) {
                    x++;
                    y--;
                    current += chessboard[x][y];
                }
                x = row;
                y = col;
                while (x < m - 1 && y < n - 1) {
                    x++;
                    y++;
                    current += chessboard[x][y];
                }
                x = row;
                y = col;
                while (x > 0 && y < n - 1) {
                    x--;
                    y++;
                    current += chessboard[x][y];
                }
                if (current > max) {
                    max = current;
                }
            }
        }
        result[i] = max;
    }
    for (int i = 0; i < num_tests; i++) {
        printf("%d\n", result[i]);
    }
    return 0;
}
