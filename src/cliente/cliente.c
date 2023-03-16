#include "cliente.h"
#include <stdio.h>
#include<stdlib.h>

void generarSalaA(int *filaElegida, char *letraAsientoElegido){

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

                if (i2 == (int) *letraAsientoElegido -65){
                    if (i == *filaElegida -1){
                        salaA[i][i2] = 87;

                    }else{
                            salaA[i][i2] = 88;
                    }

                }else{            
                        salaA[i][i2] = 88;
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

void elegirAsiento(int *filaElegida, char *letraAsientoElegido){

    printf("\n");
    printf("Introduce tu asiento: \n");
    scanf("%d %c", filaElegida, letraAsientoElegido);
    fflush(stdin);
    printf("\n      \n");
    printf("Has elegido el asiento: %d%c", *filaElegida, *letraAsientoElegido);

	printf("\n      \n");
	printf("\n    valor desde el cliente es:    %d       \n", *filaElegida);
	printf("\n    letra desde el cliente es:    %c       \n", *letraAsientoElegido);
	printf("\n      \n");

}