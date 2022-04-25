#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include"queue.h"

struct data{
    char name[20];
    char secondName[20];
    int age;
};

int main(){
    int n;
    printf("Podaj dlugosc listy:");
    scanf("%d", &n);
    struct data *person = malloc(sizeof(struct data)*n); //contains data of all persons
    struct heap *data_id = malloc(sizeof(struct heap)*n); //contains priority and key
    int i = 0;
    FILE *plik;
    plik = fopen ("baza.txt", "r");
    if (plik){
        while((i<n)&&(fscanf(plik,"%s %s %d\n", (person[i].name),(person[i].secondName), &(person[i].age)) != EOF)){
            push(data_id, person[i].age);
            i++;
        }
    }
    else{
        printf("Blad wczytywania pliku");
        return 0;
    }
    fclose(plik);

    i--;
    int index;
    while (i>=0){
        index = top(data_id);
        printf("%s %s %d\n", (person[index].name),(person[index].secondName), (person[index].age));
        pop(data_id);
        i--;
    }

    //SECOND PART
    int k, num;
    len = 0;
    printf("\nIlosc cyfr:");
    scanf("%d", &k);
    struct heap *numbers = malloc(sizeof(*numbers)*k);
    srand((unsigned int)time(NULL));

    while (k>0){
        num = (int)rand();
        push(numbers , num);
        k--;
    }
    dequeue(numbers);
}