#include <stdio.h>
#include <stdlib.h>
#include "head.h"

Matrixinfo* Loadlist(int sizex, int sizey, int arreglo[][sizex]){
    
    //"Loadlist" se encarga de cargar el arreglo de números en la lista
    //de listas
    
    //first y firstindex son "flags"
    //first verifica si el nodo es el primer elemento de esa fila
    //firstindex verifica si el índice a crear es el primero
    
    int j = 0, check = 0, first = 1, firstindex = 1;
    Columns* Columna;
    Columns* aux;
    
    Matrixinfo* Matriz;

    Indice* columnallave;
    Indice* auxindex;

    Matriz = ((Matrixinfo*)malloc(sizeof(Matrixinfo))); 

    Matriz->wide = sizex;
    Matriz->height = sizey;
    Matriz->nxtindex = NULL;

    while(j < sizey){
        int i = sizex-1;
        
        //Se recorre el arreglo, introduciendo en la lista de listas aquellos
        //elementos que sean distintos de 0
        
        while(i >= 0){
            if(arreglo[j][i] != 0){
                Columna = ((Columns*)malloc(sizeof(Columns)));
                Columna->pos = i;
                Columna->value = arreglo[j][i];
                Columna->nxt = NULL;
                check = 1;
                
                //Si la columna a crear no es la primera, se tiene que hacer
                //que apunte a las creadas anteriormente, que se van guardando
                //en "aux"
                
                if(!first){
                    Columna->nxt = aux;
                }
                aux = Columna;
                first = 0;
            }
            i--;
        }
        
        //"check" verifica si se creo al menos una columna; si no se crea
        //ninguna, es porque en esa fila, la matriz está llena de 0
        
        //solo se creará un nuevo índice si se creo al menos una columna

        if(check){
            columnallave = ((Indice*)malloc(sizeof(Indice)));
            columnallave->index = j;
            columnallave->nxtcolumn = aux;
            
            //si no es el primer índice que se está creando, se tiene que hacer
            //que los creados anteriormente le apunnten
            
            if(!firstindex){
                auxindex->nextindex = columnallave;
            }
            
            //si es el primer índice que se está creando, se tiene que hacer
            //que la matriz le apunte mismo
            
            if(firstindex){
                Matriz->nxtindex = columnallave;
                firstindex = 0;
            }
            check = 0;
            auxindex = columnallave;
        }
        j++;
        first = 1;
    }
    return Matriz;
}

int obtenerelemento(int i, int j, Matrixinfo* m){

    Indice* indice = m->nxtindex;
    Columns* columna;
    int aux = 0, k=0;

    if(indice){ //si hay elementos
        while(k <= i){
            columna = indice->nxtcolumn; //ubicarse en la primera columna
            if(indice->index == i){ //si el indice i es el buscado
                while(columna->pos <= j){
                    if(columna->pos == j){  //si el indice j es el buscado
                        aux = columna->value;  //tomar el valor
                        break;
                    }
                    columna = columna->nxt;
                    if(columna == NULL) break;
                }
            }
            if(indice->nextindex == NULL) break;
            indice = indice->nextindex;
            k++;
        }
    }
    return aux;
}

void printmatrix(Matrixinfo* matri){
    
    //"printmatrix" imprime la lista de listas por pantalla

    int i = 0, j = 0;
    int zeroescounter;
    
    //"p" y "q" son punteros auxiliares para recorrer la lista de listas
    
    Indice* p = matri->nxtindex;
    Columns* q;
    
    int x = matri->wide;
    x--;
    int y = matri->height;
    y--;
    
    //se recorre la lista de listas, imprimiendo el valor de los nodos
    //existentes

    while(j <= y){
        
        q = p->nxtcolumn;
        
        //si "j" es igual al índice actual, imprimimos esa fila. Si hay
        //discrepancias entre "j" y el índice actual, quiere decir que la fila
        //correspondiente al índice "j" estaba llena de ceros, por lo que no se
        //creó un índice para guardar la misma
        
        //si "j" es distinto del índice actual, se imprime una fila de 0s
        
        if(j == p->index){
            zeroescounter = 0;
            while(i <= x){
                
                //de igual manera, si "i" es menor a la ubicación de la columna 
                //actual, es porque en la columna "i" había un cero
                
                //se imprimiran ceros hasta estar posicionados en el próximo
                //nodo que tenga un valor
                
                if(i < q->pos){
                    printf("0\t");
                }
                
                //si el la posición de la columna actual coincide con "i",
                //se imprime el valor contenido en el nodo actual
                
                else{
                    printf("%i\t", q->value);
                    
                    //además, si el puntero a la siguiente columna es nulo, y
                    //no estamos en la última columna, es porque el resto de la
                    //fila está llena de 0s
                    
                    //se imprime igual ceros a la diferencia entre "i" y la
                    //posición de la columna actual
                    
                    if((q->nxt == NULL) && (q->pos != x)){
                        while(zeroescounter < x-i){
                            printf("0\t");
                            zeroescounter++;
                        }
                        break;
                    }
                    q = q->nxt;
                }
                i++;
            }
            p = p->nextindex;
            printf("\n");
            j++;
            i = 0;
        }
        else {
            for(int k = 0; k <= x; k++){
                printf("0\t");
            }
            printf("\n");
            j++;
        }
    }
}

Matrixinfo* insertelement(int i, int j, int z, Matrixinfo* M){
    
    //"insertelement" insertará un elemento de valor "z" en la lista de listas,
    //en la posición ("i"; "j")
    
    Columns* Columna;
    Indice* Columnallave;
    
    register int x, y;
    
    //se tiene que tomar en consideración si el valor de "z" es 0; si lo es,
    //y la posición en la que se quiere insertar contiene un valor, se tiene
    //que eliminar ese nodo; la lista de listas no guarda 0s
    
    //si la posición en la que se quiere insertar no existe o no se encontro,
    //es porque en esa posición había un 0, y no se creo un nodo; se sale de 
    //la función sin alterar realmente la lista de listas
    
    if(z == 0){
        Indice* auxindex = M->nxtindex;
        Columns* auxcolumn;
        
        for(y = 0; y <= j; y++){
            if(y == j){
                if((auxindex->nxtcolumn)->pos == i){
                    Columns* todelete = auxindex->nxtcolumn;
                    auxindex->nxtcolumn = (auxindex->nxtcolumn)->nxt;
                    free(todelete);
                    
                    return M;
                }
                
                auxcolumn = auxindex->nxtcolumn;
                for(x = 0; x <= i; x++){
                    if(((auxcolumn->nxt != NULL) && (auxcolumn->nxt)->pos == i)){
                        if((auxcolumn->nxt)->nxt == NULL){
                            free(auxcolumn->nxt);
                            auxcolumn->nxt = NULL;
                            
                            return M;
                        }
                        
                        Columns* todelete = auxindex->nxtcolumn;
                        auxcolumn->nxt = (auxcolumn->nxt)->nxt;
                        free(todelete);
                        
                        return M;
                    }
                    
                    auxcolumn = auxcolumn->nxt;
                    
                }
                
                if(auxcolumn->nxt == NULL){
                    return M;
                }
            }
            
            if(auxindex->nextindex == NULL){
                return M;
            }
            
            auxindex = auxindex->nextindex;
        }
    }
    
    //si el valor a insertar no es 0, si se tiene que crear un nodo
    //en el caso de que no exista uno en la posición a insertar
    
    //la lista de listas está vacía; se creará el único nodo que contendrá, se
    //enlaza al único índice que tendrá la lista de listas, y el mismo se
    //enlaza con la lista
    
    if(M->nxtindex == NULL){
        Columna = ((Columns*)malloc(sizeof(Columns)));
        Columna->pos = i;
        Columna->value = z;
        Columna->nxt = NULL;
        
        Columnallave = ((Indice*)malloc(sizeof(Indice)));
        Columnallave->index = j;
        Columnallave->nxtcolumn = Columna;
        
        M->nxtindex = Columnallave;
        
        return M;
    }
    
    //el primer índice de la lista de listas es mayor a la fila en la que se
    //quiere insertar; se crea un primer índice, al que apuntará la lista de
    //listas, que apuntará al resto de índices
    
    if((M->nxtindex)->index > j){
        Columna = ((Columns*)malloc(sizeof(Columns)));
        Columna->pos = i;
        Columna->value = z;
        Columna->nxt = NULL;
        
        Indice* newindex;
        newindex = ((Indice*)malloc(sizeof(Indice)));
        newindex->index = j;
        newindex->nxtcolumn = Columna;
        newindex->nextindex = M->nxtindex;
        
        M->nxtindex = newindex;
        
        return M;
    }
    
    Indice* auxindex = M->nxtindex;
    
    //se recorren los índices, buscando la fila en la que se quiere insertar
    
    for(y = 0; y <= j; y++){
        
        //se llegó al último índice sin encontrar la fila en la que insertar;
        //se crea dicha fila, apuntado a una nueva columna, donde se insertará
        //el elemento. La nueva fila se posiciona como la última
        
        if((auxindex->index < j) && (auxindex->nextindex == NULL)){
            Columna = ((Columns*)malloc(sizeof(Columns)));
            Columna->pos = i;
            Columna->value = z;
            Columna->nxt = NULL;
            
            Indice* newindex;
            newindex = ((Indice*)malloc(sizeof(Indice)));
            newindex->index = j;
            newindex->nxtcolumn = Columna;
            newindex->nextindex = NULL;
            auxindex->nextindex = newindex;
            
            return M;
        }
        
        //se encontró la fila en la que se quiere insertar;
        //ahora se recorren las columnas de esa fila, buscando la columna en
        //la que se quiere insertar
        
        if(auxindex->index == j){
            
            //la posición de la primera columna es mayor a la columna donde se
            //quiere insertar el elemento; se crea dicha columna, apuntando a
            //las siguientes columnas, a la que apunta el índice
            
            if((auxindex->nxtcolumn)->pos > i){
                Columns* newcolumn;
                newcolumn = ((Columns*)malloc(sizeof(Columns)));
                newcolumn->pos = i;
                newcolumn->value = z;
                
                newcolumn->nxt = auxindex->nxtcolumn;
                auxindex->nxtcolumn = newcolumn;
                
                return M;
            }
            
            Columns* auxcolumn = auxindex->nxtcolumn;
            
            for(x = 0; x <= i; x++){
                
                //se encontró la columna en la que se quiere insertar, en la fila
                //en la que se quiere insertar; se reemplaza el valor que está
                //en ese nodo por el valor a insertar                
                
                if(auxcolumn->pos == i){
                    auxcolumn->value = z;
                    
                    return M;
                }
                
                //la columna siguiente tiene posición mayor a la de la columna
                //en la que se quiere insertar; se crea la nueva columna,
                //apuntado a las columnas siguiente, a la que apuntarán
                //las columnas anteriores
                
                if((auxcolumn->nxt != NULL) && ((auxcolumn->nxt)->pos > i)){
                    Columns* newcolumn;
                    newcolumn = ((Columns*)malloc(sizeof(Columns)));
                    newcolumn->pos = i;
                    newcolumn->value = z;
                    newcolumn->nxt = auxcolumn->nxt;
                    auxcolumn->nxt = newcolumn;
                    
                    return M;
                }
                
                //se recorrieron las columnas sin encontrar la columna en la que
                //se quiere insertar; se creará una nueva columa al final de la
                //fila, a la que apunten las anteriores
                
                if(auxcolumn->nxt == NULL){
                    Columns* newcolumn;
                    newcolumn = ((Columns*)malloc(sizeof(Columns)));
                    newcolumn->pos = i;
                    newcolumn->value = z;
                    newcolumn->nxt = NULL;
                    auxcolumn->nxt = newcolumn;
                    
                    return M;
                }
                
                auxcolumn = auxcolumn->nxt;
            }
            
        }
        
        //el índice de la siguiente fila es mayor al de la fila en la que se
        //quiere insertar; se una fila nueva, que apuntará a una nueva columna
        //con el elemento a insertar
        
        if((auxindex->nextindex)->index > j){
            Columns* newcolumn;
            newcolumn = ((Columns*)malloc(sizeof(Columns)));
            newcolumn->pos = i;
            newcolumn->value = z;
            newcolumn->nxt = NULL;
            
            Indice* newindex;
            newindex = ((Indice*)malloc(sizeof(Indice)));
            newindex->index = j;
            newindex->nxtcolumn = newcolumn;
            newindex->nextindex = auxindex->nextindex;
            auxindex->nextindex = newindex;
            
            return M;
        }    
        auxindex = auxindex->nextindex;
    }
}

Matrixinfo* ProductoPorEscalar(int e, Matrixinfo* mat){
    register int i = 0, j = 0;

    Matrixinfo* m = mat;
    Indice* p = m->nxtindex;
    Columns* q;

    int x = m->wide;
    x--;
    int y = m->height;
    y--;

    if(p){ //si existe el primer indice (si la matriz tiene elemento(s))
        while(j <= y){
            q = p->nxtcolumn; //ubicarse en la primera columna
                while(i <= x){
                    if(q){  //si la columna existe
                        q->value *= e;
                        if((q->nxt == NULL)) break;  //si la siguiente columna no existe, salir
                        q = q->nxt; //siguiente columna
                    } else break; //si no hay columnas, salir
                    i++;
                }
            p = p->nextindex;  //siguiente fila (indice)
            j++;
            i = 0;
        }
    }
    return m; //retorna la nueva matriz
}

Matrixinfo* transposition(Matrixinfo* M){
    
    //"transposition" devuelva la transpuesta de una Matriz
    
    Matrixinfo* transposedmatrix;
    transposedmatrix = ((Matrixinfo*)malloc(sizeof(Matrixinfo)));
    transposedmatrix->nxtindex = NULL;
    
    register int i, j = 0;
    
    Indice* auxindex;
    Columns* auxcolumns;
    
    register int x, y;
    
    //se recorrerá la lista de listas
    
    //valiéndonos de "insertelement", iremos insertando cada elemento de la
    //lista de listas; el índice de la fila en la que insertaremos el elemento
    //será igual al la posición de la columna en la que se encuentra, y la 
    //columna en la que lo insertaremos será igual al índice de la fila
    //en la que se encuentra
    
    for(auxindex = M->nxtindex; auxindex != NULL; auxindex = auxindex->nextindex){
        auxcolumns = auxindex->nxtcolumn;
        for(auxcolumns = auxindex->nxtcolumn; auxcolumns != NULL; auxcolumns = auxcolumns->nxt){
            transposedmatrix = insertelement(auxindex->index, auxcolumns->pos, auxcolumns->value, transposedmatrix);
            if(auxcolumns->nxt == NULL){
                continue;
            }
        }
        
        if(auxindex->nextindex == NULL){
            continue;
        }
    }
    
    //se invierten las dimensiones de la matriz antes de retornarla
    
    transposedmatrix->height = M->wide;
    transposedmatrix->wide = M->height;
    
    return transposedmatrix;
}

Matrixinfo* multiply(Matrixinfo* M1, Matrixinfo* M2){
    
    //"multiply" nos devolverá el producto de multiplicar una matriz por otra
    
    //la cantidad de columnas de la matriz 1 ha de ser igual a la cantidad de
    //filas de la matriz 2
    
    if((M1->wide) != (M2->height)){
        printf("Dimesiones invalidas");
        return M1;
    }
    
    Matrixinfo* resultmatrix;
    resultmatrix = ((Matrixinfo*)malloc(sizeof(Matrixinfo)));
    resultmatrix->nxtindex = NULL;
    resultmatrix->height = M1->height;
    resultmatrix->wide = M2->wide;
    
    //si alguna de las 2 matrices es nula, se devolverá "resultmatrix"
    //apuntando a nulo, ya que el producto de una matriz por una matriz llena
    //de 0s es, también, una matriz llena de 0, que no se guardan en la listas
    //de listas
    
    if((M1->nxtindex == NULL) || (M2->nxtindex == NULL)){
        return resultmatrix;
    }
    
    register int i, j, k, acum = 0;
    
    //se transpone una de las dos matrices, con la intención de facilitar el
    //acceso a las columnnas, que ahora serán las filas
    
    M2 = transposition(M2);
    
    Indice* auxp1;
    Columns* auxq1;
    Indice* auxp2;
    Columns* auxq2;
    
    //se recorrerá cada fila de la matriz 1
    
    for(auxp1 = M1->nxtindex; auxp1 != NULL; auxp1 = auxp1->nextindex){
        
        //por cada fila de la matriz 1, se recorrerán las filas de la matriz 2
        
        for(auxp2 = M2->nxtindex; auxp2 != NULL; auxp2 = auxp2->nextindex){
            
            auxq1 = auxp1->nxtcolumn;
            auxq2 = auxp2->nxtcolumn;
            
            //por cada fila de la matriz 2, se recorrerán las columnas de
            //ambas matrices
            
            for(i = 0; i <= M2->wide; i++){
                
                //si las posiciones de las columnas a las que estemos apuntando
                //coinciden, le sumaremos el producto de los valores que
                //contienen los nodos actuales a "acum"
                
                if(auxq1->pos == auxq2->pos){
                    acum = acum + auxq1->value*auxq2->value;
                }
                
                //si ya se recorrió la totalidad de las columnas de la fila
                //el valor contenido en "acum" se insertará en la matriz 
                //resultado
                
                if((auxq2->nxt == NULL) && (auxq1->nxt == NULL)){
                    if(acum != 0){
                        resultmatrix = insertelement(auxp2->index, auxp1->index, acum, resultmatrix);
                    }
                    break;
                }
                
                //si la posición de la columna actual coincide con "i", se
                //avanzará a la siguiente columna, siempre y cuando el siguiente
                //nodo no sea nulo
                
                if((auxq1->pos == i) && (auxq1->nxt != NULL)){
                    auxq1 = auxq1->nxt;
                }
                
                if((auxq2->pos == i) && (auxq2->nxt != NULL)){
                    auxq2 = auxq2->nxt;
                }
            }
            acum = 0;
            
            if(auxp2->nextindex == NULL){
                break;
            }
        }
        
        if(auxp1->nextindex == NULL){
            break;
        }
    }
    return resultmatrix;
}