#include <stdio.h>
#include <stdlib.h>

int main()
{
    int max_size = 10;
    int size = 0;
    char* tab;
    tab = (char*)malloc(max_size);
    int c;
    int i=0;
    while ((c = getchar())!= EOF)
    {
        tab[i] = c;
        size++;
        if (size == max_size)
        {
            max_size*=2;
            tab = realloc(tab, max_size);
            printf("Zwiekszono ilosc pamieci do %d.\n", max_size);
        }
        i++;
    }
    for (int j = 0; j < i; j++)
    {
        printf("%c", tab[j]);
    }
    free(tab);
    return 0;
}