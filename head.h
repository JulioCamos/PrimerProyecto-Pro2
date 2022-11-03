#ifndef HEAD_H_
#define HEAD_H_

typedef struct node{
    int pos, value;
    struct node* nxt;
}Columns;

typedef struct nodeX{
    int index;
    Columns* nxtcolumn; 
    struct nodeX* nextindex; 
}Indice;

typedef struct nodeY{
    int height, wide;
    struct nodeX* nxtindex;
}Matrixinfo;


Matrixinfo* Loadlist(int sizex, int sizey, int arreglo[][sizey]);
//tomar un arreglo y pasarlo a la lista de listas

int obtenerelemento(int i, int j, Matrixinfo* m);
//obtener el valor del elemento en la posición (i; j)

void printmatrix(Matrixinfo* matri);
//imprimir la lista de listas

Matrixinfo* insertelement(int i, int j, int z, Matrixinfo* M);
//insertar un elemento en la lista de listas, en la posición dada

Matrixinfo* SumarMatrices(Matrixinfo* M1, Matrixinfo* M2);
//suma las dos matrices dadas

Matrixinfo* ProductoPorEscalar(int e, Matrixinfo* mat);
//multiplicar la matriz por un escalar

Matrixinfo* transposition(Matrixinfo* M);
//transponer la matriz

Matrixinfo* multiply(Matrixinfo* M1, Matrixinfo* M2);
//multiplicar una matriz por otra

#endif