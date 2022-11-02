#include <stdio.h>
#include <stdlib.h>
#include "head.h"

void main(){

    const int tamxarray1 = 3;
    const int tamyarray1 = 3;

    int array1[3][3] = {
        {9, 1, 5},
        {2, 3, 0},
        {1, 5, 7}
    };

    const int tamxarray2 = 3;
    const int tamyarray2 = 3;

    int array2[3][3] = {
        {1, 0, 76}, 
        {0, 0, 4},
        {4, 7, 0}
    };

    Matrixinfo* Matriz1 = loadlist(tamxarray1, tamyarray1, array1);
    printmatrix(Matriz1);

    printf("\n");

    Matrixinfo* Matriz2 = loadlist(tamxarray1, tamyarray2, array2);
    printmatrix(Matriz2);

    printf("\n");

    Matriz1 = multiply(Matriz1, Matriz2);
    printmatrix(Matriz1);
}