#include <stdio.h>
#include <stdlib.h>
#include "head.h"

int main(){
    
        int opcion;

    const int tamxarray1 = 4;
    const int tamyarray1 = 2;

    int array1[4][2] = {
        {1, 2},
        {3, 4},
        {0, 0},
        {9, 5}
    };

    const int tamxarray2 = 2;
    const int tamyarray2 = 4;

    int array2[2][4] = {
        {1, 2, 7, 5},
        {3, 0, 0, 2}
    };

    Matrixinfo* M1;
    M1 = Loadlist(tamxarray1, tamyarray1, array1);

    Matrixinfo* M2;
    M2 = Loadlist(tamxarray2, tamyarray2, array2);

    Matrixinfo* Mresultado;

    int fila, columna, elemento;
    int escalar;

    printf("1. Imprimir las matrices cargadas\n2. Obtener un elemento de la matriz\n");
    printf("3. Insertar un elemento en la matriz\n4. Sumar las matrices cargadas\n");
    printf("5. Multiplicar la matriz por un escalar\n6. Transponer la matriz\n7. Multiplicar las matrices cargadas\n\n");

    scanf("%i", &opcion);
    printf("\n");

    switch(opcion)
    {
        case 1:
          printmatrix(M1);
          printf("\n");
          printmatrix(M2);
        break;

        case 2:        
          printf("fila del elemento a buscar:\n");
          scanf("%i", &fila);
          printf("columna del elemento a buscar\n");
          scanf("%i", &columna);
          printf("\n");
          elemento = obtenerelemento(fila, columna, M1);
          printf("%i", elemento);
        break;

        case 3:
          printmatrix(M1);
          printf("\n");
          printf("fila en la que insertar el elemento: ");
          scanf("%i", &fila);
          printf("columna del elemento a insertar: ");
          scanf("%i", &columna);
          printf("valor del elemento a insertar: ");
          scanf("%i", &elemento);
          Mresultado = insertelement(columna, fila, elemento, M1);
          printf("\n");
          printmatrix(Mresultado);
        break;

        case 4:
          printmatrix(M1);
          printf("\n");
          printmatrix(M2);
          printf("\n - - - - - - - - - - - - - \n\n");
          Mresultado = SumarMatrices(M1, M2);
          printmatrix(Mresultado);
        break;

        case 5:
          printf("escalar por el que multiplicar la matriz: ");
          scanf("%i", &escalar);
          Mresultado = ProductoPorEscalar(escalar, M1);
          printf("\n");
          printmatrix(Mresultado);
        break;

        case 6:
          printmatrix(M1);
          Mresultado = transposition(M1);
          printf("\n - - - - - - - - - - - - - \n\n");
          printmatrix(Mresultado);
        break;

        case 7:
          printmatrix(M1);
          printf("\n");
          printmatrix(M2);
          printf("\n - - - - - - - - - - - - - \n\n");
          Mresultado = multiply(M1, M2);
          printmatrix(Mresultado);
        break;
    }

    getchar();
    
    return 0;
}