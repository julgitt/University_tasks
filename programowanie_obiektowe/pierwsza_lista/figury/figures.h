
#ifndef OBIEKTOWE_FIGURES_H
#define OBIEKTOWE_FIGURES_H
enum type {
    circle, triangle, square /*trapeze*/};

typedef struct Figure {
    enum type figure_type;
    //coordinates
    float x;
    float y;
    //sides
    float a;
    float b;
    float c;
    //float d;
} Figure;

Figure new_square(float x, float y, float a);

/*Figure new_trapeze(float x, float y, float a, float b, float c, float d);*/

Figure new_circle(float x, float y, float r);

Figure new_triangle(float x, float y, float a, float b, float c);

float area(Figure f);

void move(Figure f, float x, float y);

void show(Figure f);

float sum_of_areas(Figure f[], int size);

#endif //OBIEKTOWE_FIGURES_H

