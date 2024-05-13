
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*
Lenguajes de Programación
Tarea del lenguaje C: 2048 en Stop Motion
Profesor: Kirstein Gätjens S.
Estudiante: Dayana Xie Li
Carnet: 2022097967
Grupo: 2

-------------------------------------------------------------------
Manual de usuario

El programa se hizo y probó en visual studio code.
Comandos para probarlo:
gcc 2048-Stop-Motion-Xie-Dayana.c -o 2048-Stop-Motion-Xie-Dayana 
.\2048-Stop-Motion-Xie-Dayana G x.2048


De parametros recibe la direccion que se desea mover, ya sea N, O, S, E y seguido el nombre del archivo .2048
También recibe una G de parametro si se quiere crear una nueva partida

Por cada instruccion se va a mover el tablero hacia ea direccion y a su vez se va a aparecer un dos aleatorio en el tablero

Si luego de un movimiento ya no hay mas ceros, es decir no puede aparecer otro dos aleatorio, entonces pierde la partida
Si luego de un movimiento hay un 2048 entonces gana la partida

-------------------------------------------------------------------

Analisis de resultados
Lectura y creacion del archivo para guardar el tablero A
Movimiento del tablero implementado A
Actualizacion del archivo con los movimientos A
El algoritmo de random E, se utilizo el algoritmo de random que ya tiene c por lo que no se implemento un algoritmo de random bueno


*/

// algoritmo que sube hasta arriba los elementos del tablero
void norte(int matrizTablero[4][4]){
    // para ir subiendo hasta arriba
    int row = 0;
    for(int fila = 1; fila < 4; fila++){
        for(int colum = 0; colum < 4; colum ++){
            //printf("nuevo row \n");
            row = fila;
            while(row > 0){
                // si es cero el que esta arriba entonces subo el numero y el numero actual es diferente a cero
                if((!matrizTablero[row-1][colum])  && matrizTablero[row][colum]){
                    matrizTablero[row-1][colum] = matrizTablero[row][colum];
                    matrizTablero[row][colum] = 0;
                }
                // si son iguales y no es cero entonces lo sumo
                if((matrizTablero[row-1][colum] == matrizTablero[row][colum]) && matrizTablero[row][colum]){
                    matrizTablero[row-1][colum] += matrizTablero[row][colum];
                    matrizTablero[row][colum] = 0;
                }
                row -= 1;
            }
            
        }
    }

}

// algoritmo que baja hasta abajo los elementos del tablero
void sur(int matrizTablero[4][4]){
    // para ir bajando  hasta abajo
    int row = 0;
    for(int fila = 2; fila >= 0 ; fila--){
        for(int colum = 0; colum < 4; colum ++){
            //printf("nuevo row \n");
            row = fila;
            while(row < 3){
                // si es cero el que esta abajo entonces bajo el numero y el numero actual es diferente a cero
                if((!matrizTablero[row+1][colum])  && matrizTablero[row][colum]){
                    matrizTablero[row+1][colum] = matrizTablero[row][colum];
                    matrizTablero[row][colum] = 0;
                }
                // si son iguales y no es cero entonces lo sumo
                if((matrizTablero[row+1][colum] == matrizTablero[row][colum]) && matrizTablero[row][colum]){
                    matrizTablero[row+1][colum] += matrizTablero[row][colum];
                    matrizTablero[row][colum] = 0; 
                }
                row += 1;
            }
            
        }
    }

}

// algoritmo que mueve hasta la derecha los elementos del tablero
void este(int matrizTablero[4][4]){
    // para ir hasta la derecha
    int col = 0;
    for(int fila = 0; fila < 4; fila++){
        for(int colum = 0; colum < 3; colum ++){
            col = colum;
            while(col < 3){
                // si es cero el que esta a la derecha entonces muevo  el numero y el numero actual es diferente a cero
                if((!matrizTablero[fila][col+1]) && matrizTablero[fila][col]){
                    matrizTablero[fila][col+1] = matrizTablero[fila][col];
                    matrizTablero[fila][col] = 0;
                }
                // si son iguales y no es cero entonces lo sumo
                if((matrizTablero[fila][col+1] == matrizTablero[fila][col]) && matrizTablero[fila][col]){
                    matrizTablero[fila][col+1] += matrizTablero[fila][col];
                    matrizTablero[fila][col] = 0;
                }
                col += 1;
            }
            
        }
    }

}

// algoritmo que mueve hasta la izquierda los elementos del tablero
void oeste(int matrizTablero[4][4]){
    // para ir hasta la izquierda
    int col = 0;
    for(int fila = 0; fila < 4; fila++){
        for(int colum = 3; colum >= 0; colum--){
            col = colum;
            while(col > 0){
                // si es cero el que esta a la izquierda entonces muevo  el numero y el numero actual es diferente a cero
                if((!matrizTablero[fila][col-1]) && matrizTablero[fila][col]){
                    matrizTablero[fila][col-1] = matrizTablero[fila][col];
                    matrizTablero[fila][col] = 0;
                }
                // si son iguales y no es cero entonces lo sumo
                if((matrizTablero[fila][col-1] == matrizTablero[fila][col]) && matrizTablero[fila][col]){
                    matrizTablero[fila][col-1] += matrizTablero[fila][col];
                    matrizTablero[fila][col] = 0;
                }
                col -= 1;
            }
            
        }
    }

}

// funcion que devuelve un numero random del 0 al 3
int randomProvisional(){
    int num = rand();
    // numero entre 0 y 3
    num %= 4;
    return num;
}

//funcion que mete un dos aleatorio en donde no haya un numero ya
void dosAleatorio(int matrizTablero[4][4]){
    // si es cero entonces pongo el numero sino que siga generando el random
    int fila = randomProvisional();
    int colum = randomProvisional();
    if(!matrizTablero[fila][colum]){
        matrizTablero[fila][colum] = 2;
    }else{
        dosAleatorio(matrizTablero);
    }
}


// funcion que pasa una matriz de numeros a un string 
void pasarAChar(int matrizTablero[4][4], char *tablero){
    for(int fila = 0; fila < 4; fila++){
        for(int colum = 0; colum < 4; colum++){
            char numAct[50];
            sprintf(numAct, "%d", matrizTablero[fila][colum]);
            strcat(tablero, numAct);
            strcat(tablero, " ");
        }
        // en la ultima linea no se necesita el cambio de linea
        if(fila < 3){
            strcat(tablero, "\n");
        }
    }
}


// funcion que pasa un string que contiene numeros a una matriz con numeros
int *pasarAMatriz(char *strTablero, int matrizTablero[4][4]){
    //printf("llega aqui \n");
    //printf("%d", strlen(strTablero));
    int iStr = 0; // para recorrer todo el string
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            int num = 0;
            int eqv = 0;
            // si el numero tiene mas de un digito se va formando hasta que no haya un cambio de linea o espacio o el final
            while (strTablero[iStr] != '\n' && strTablero[iStr] != ' ' && strTablero[iStr] != '\0' ) {
                // para obtener el numero equivalente del char
                eqv = strTablero[iStr] - '0';
                num = num * 10 + eqv;
                iStr++;
            }
            // saltar el cambio de linea o espacio o el final
            iStr++; 
            matrizTablero[i][j] = num;
        }
        iStr++; 
    }
}

// funcion que actualiza el archivo con el nuevo tablero
void actualizarArchivo(char *tablero, char* ruta){
    FILE *partida;
    partida = fopen(ruta, "w+");
    fputs(tablero, partida);
    fclose(partida);

}

// funcion que obtiene el tablero del archivo 
void obtenerTablero(char *ruta, int matrizTablero[4][4]){
    FILE *partida;
    partida = fopen(ruta, "r");
    char tablero[50] = "";
    char linea[50];
    // leer todo el contenido del archivo para obtener todo el tablero
    while(fgets(linea, 100, partida)){
        strcat(tablero, linea);
    }
    //printf("%c\n", tablero[0]);
    //printf("%c\n", tablero[1]);
    
    //printf("%d", strlen(tablero));
    pasarAMatriz(tablero, matrizTablero);
    fclose(partida);

}

// funcion que revisa si el jugador ya logro formar un 2048 y asi ganar la partida
void revisarGanar(int matriz[4][4]){
    int gano;
    for(int fila = 0; fila < 4; fila++){
        for(int colum = 0; colum < 4; colum++){
            if(matriz[fila][colum] == 2048){
                // si hay un 2048 gano
                gano = 1;

            }
        }
    }
    if(gano){
        printf("----------------------------------------------------\n");
        printf("------------------GANO LA PARTIDA :)----------------\n");
        printf("----------------------------------------------------\n");
    }

}

// funcion que revisa si el tablero ya no se le puede agregar mas numeros, entonces pierde
void revisarPerder(int matriz[4][4]){
    int cero;
    for(int fila = 0; fila < 4; fila++){
        for(int colum = 0; colum < 4; colum++){
            // si ya no hay ceros entonces perdio porque no se puede hacer mas movimientos y agregar mas dos
            if(!matriz[fila][colum]){
                // si no hay cero entonces false
                cero = 0;

            }
        }
    }
    if(cero){
        printf("----------------------------------------------------\n");
        printf("----------------PERDIO LA PARTIDA :(----------------\n");
        printf("----------------------------------------------------\n");
    }
}

// funcion que tiene el procedimiento de agregar los dos y actualizar el arcchivo
// para que no haya codigo duplicado
void final(char *ruta, int matriz[4][4]){
    // luego de realizar el movimiento se revisa si perdio
    revisarPerder(matriz);
    revisarGanar(matriz);
    dosAleatorio(matriz);
    char tablero[50] = "";
    pasarAChar(matriz, tablero);
    actualizarArchivo(tablero, ruta);   
}

// funcion que llama a las funciones correspondientes segun el momvimiento indicado
void revisarParam(char L, char *ruta){
    if(L == 'G'){
        FILE *partida;
        partida = fopen(ruta, "w");
        char vacio[] = "0 0 0 0\n0 0 0 0\n0 0 0 0\n0 0 0 0";    // creo el tablero vacio
        fputs(vacio, partida);
        
        fclose(partida);
        int matriz[4][4];
        obtenerTablero(ruta, matriz);
        // le agrego dos veces el dos en un lugar donde haya cero
        dosAleatorio(matriz);
        final(ruta, matriz);
        printf("Archivo generado con exito");
    }
    int matriz[4][4];
    obtenerTablero(ruta, matriz);
    if(L == 'N'){
        norte(matriz);
        printf("Movimiento realizado con exito\n");
        final(ruta, matriz);
    }if(L == 'S'){
        sur(matriz);
        printf("Movimiento realizado con exito\n");
        final(ruta, matriz);
    }if(L == 'E'){
        este(matriz);
        printf("Movimiento realizado con exito\n");
        final(ruta, matriz);
    }if(L == 'O'){
        oeste(matriz);
        printf("Movimiento realizado con exito\n");
        final(ruta, matriz);
    }    
};

// N norte, S sur, E este, O oeste, G nueva partida
// el primer argumento es la letra y el segundo es el archivo
int main(int argc, char *argv[]){
    srand(time(NULL));
    char ruta[50];          // espacio para guardar la ruta
    strcpy(ruta, argv[2]);  // copiar la ruta
    revisarParam(*argv[1], ruta);
    return 1;
};

