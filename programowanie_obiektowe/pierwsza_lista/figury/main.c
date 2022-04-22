#include <stdio.h>
#include "figures.h"

int main() {
    Figure square = new_square(1.0f, 2.0f, 4.0f);
    Figure circle = new_circle(1.0f, 2.0f, 4.0f);
    Figure triangle = new_triangle(1.0f, 2.0f, 4.0f, 3.0f, 5.0f);
    Figure array[] = {square, circle, triangle};
    printf("%f", sum_of_areas(array, 3));
    return 0;
}
//<<>>|