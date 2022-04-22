#include <stdio.h>
#include <math.h>
#include "figures.h"

Figure new_square(float x, float y, float a) { //<>>|
    if (0 >= a) {
        printf("Side length must be positive. Given value will be changed to |a|\n");
        a = (float) fabs((double) a);
    }
    Figure new;
    new.figure_type = square;
    new.x = x;
    new.y = y;
    new.a = a;
    new.b = 0.0f;
    new.c = 0.0f;
    return new;
}

Figure new_circle(float x, float y, float r) {
    if (0 >= r) {
        printf("Side length must be positive. Given value will be changed to |r|\n");
        r = (float) fabs((double) r);
    }
    Figure new;
    new.figure_type = circle;
    new.x = x;
    new.y = y;
    new.a = r;
    new.b = 0.0f;
    new.c = 0.0f;
    return new;
}

Figure new_triangle(float x, float y, float a, float b, float c) {
    if (0 >= a || 0 >= b || 0 >= c) {
        printf("Side length must be positive. Given value num will be changed to |num|\n");
        a = (float) fabs((double) a);
        b = (float) fabs((double) b);
        c = (float) fabs((double) c);
    }

    Figure new;
    new.figure_type = triangle;
    new.x = x;
    new.y = y;
    new.a = a;
    new.b = b;
    new.c = c;

    if (a >= b + c || b >= a + c || c >= a + b) {
        printf("The sum of the two sides of the triangle must be greater than the other side\n");
        a = 0.0f;
        b = 0.0f;
        c = 0.0f;
    }
    return new;
}

float area(Figure f) {
    if (f.figure_type == circle) {
        return f.a * f.a * (float) M_PI;
    } else if (f.figure_type == square) {
        return f.a * f.a;
    } else if (f.figure_type == triangle) {
        float p = (f.a + f.b + f.c) / 2.0f;
        return (float) sqrt((double) p * (p - f.a) * (p - f.b) * (p - f.c));
    }
    /*else if (f.figure_type == trapeze) */
    return 0;
}

void move(Figure f, float x, float y) {
    f.x += x;
    f.y += y;
}

void show(Figure f) {
    char *figure_name;
    switch (f.figure_type) {
        case 0:
            figure_name = "circle";
            break;
        case 1:
            figure_name = "triangle";
            break;
        case 2:
            figure_name = "square";
            break;
            /*
            case 3:
             */


    }
    printf("figure type: %s\n coordinates: %f %f \n", figure_name, f.x, f->y);
}

float sum_of_areas(Figure f[], int size) {
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += area(f[i]);
    }
    return sum;
}
