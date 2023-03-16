#include "cliente.h"
#include <stdio.h>
#include<stdlib.h>


void generarSalaA(AsientoElegido *arrayAsientosElegidos){

    	printf("///////////////Seleccione un asiento escribiendo su numero y letra: \n");
    	printf("Tenga en cuenta que los asientos marcados con 'X' no estan disponibles. \n ");
        printf("\n");

        int numFilas = 5; 
        int numAsientosXFila = 8;

        char **salaA;
        salaA = (char**)malloc(sizeof(char*)*numFilas);

        int i;
        int i2;
        for (i=0; i<5; i++) {
            salaA[i] = (char*)malloc(numAsientosXFila * (sizeof(char)*3));
            *salaA[i] = i + 49;
            printf("%c     ", *salaA[i]);

            for (i2=0; i2<numAsientosXFila; i2++){

                if (i2 == (int) arrayAsientosElegidos[0].letraAsientoElegido -65){
                    if (i == arrayAsientosElegidos[0].filaElegida -1){
                        salaA[i][i2] = 88;

                    }else{
                            salaA[i][i2] = 45;
                    }

                }else{            
                        salaA[i][i2] = 45;
                    }
                

                printf("  [ %c ]  ", salaA[i][i2]);

            }
        
        printf("\n");


        }
        printf("       ");
        for (i2=0; i2<numAsientosXFila; i2++){
                printf("   %c     ", i2 + 65 );

                if (i2 == 3){

                    


                }

            }

        //Alonso - falta liberar los mallocs al final y los valores del asiento elegido (creo)




}

void elegirAsiento(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas){

    printf("\n");
    printf("Introduce tu asiento: \n");

    scanf("%d %c", &arrayAsientosElegidos[numEntradasSeleccionadas].filaElegida, &arrayAsientosElegidos[numEntradasSeleccionadas].letraAsientoElegido);

    fflush(stdin);
    printf("\n      \n");

    printf("Has elegido el asiento: %d%c", arrayAsientosElegidos[0].filaElegida, arrayAsientosElegidos[0].letraAsientoElegido);

}