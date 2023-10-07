#include <iostream>
#include <map>
int main() {
    int num_cubes = 0;
    scanf("%d", &num_cubes);
    int sides[num_cubes][6];
    int current;
    std::map <int,int> numbers;

    for (int i = 0; i < num_cubes; i++) {
        for (int j = 0; j < 6; j++) {
            scanf("%d", &sides[i][j]);
            numbers[sides[i][j]] = 1;
        }
    }

    for(int fst_cube = 0; fst_cube < num_cubes; fst_cube++){
        for (int snd_cube = fst_cube + 1; snd_cube < num_cubes; snd_cube++){
            for (int fst_side = 0; fst_side < 6; fst_side++) {
                for (int snd_side = 0; snd_side < 6; snd_side++){
                    current = sides[fst_cube][fst_side] * 10 + sides[snd_cube][snd_side];
                    numbers[current] = 1;
                    current = sides[snd_cube][fst_side] * 10 + sides[fst_cube][snd_side];
                    numbers[current] = 1;
                }
            }
        }
    }
    for (int i = 1; i < 99; i++){
        if (numbers[i] == 0) {
            printf("%d\n", i - 1);
            return 0;
        }
    }
    printf("%d\n", 98);
    return 0;
}
