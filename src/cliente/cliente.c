#include "cliente.h"

void generarSalaA(int *filaElegida, char *letraAsientoElegido){

    	printf("Seleccione un asiento escribiendo su numero y letra: \n");
        printf("\n        %d       \n", &filaElegida);
    	printf("Tenga en cuenta que los asientos marcados con 'X' no estan disponibles. \n ");
        printf("\n");

        /* int **salaA;
        salaA = (int**)malloc(sizeof(int*)*5);

        int i;
        int i2;
        for (i=0; i<5; i++) {
            salaA[i] = (int*)malloc(3 * sizeof(int));
            *salaA[i] = i +1;
            printf(" La fila es: %i \n", *salaA[i]);

            for (i2=0; i2<3; i2++){
                salaA[i][i2] = i2 +1;
                printf(" El numero es : %i \n", salaA[i][i2]);

            }
        printf("\n"); */




        int numFilas = 5; 
        int numAsientosXFila = 8;
        //int filaElegida =1;
        //char letraAsientoElegido ='a';

        /*printf("Introduce tu asiento: \n");
        scanf("%d %c", &filaElegida, &letraAsientoElegido);
        printf("Your number is: %d", filaElegida);
        printf("Your number is: %c", letraAsientoElegido);*/

        char **salaA;
        salaA = (char**)malloc(sizeof(char*)*numFilas);

        int i;
        int i2;
        for (i=0; i<5; i++) {
            salaA[i] = (char*)malloc(numAsientosXFila * (sizeof(char)*3));
            *salaA[i] = i + 49;
            printf("%c     ", *salaA[i]);

            for (i2=0; i2<numAsientosXFila; i2++){

                salaA[i][i2] = 88;
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

    //int filaElegida;
    //char letraAsientoElegido;

    printf("\n");
    printf("Introduce tu asiento: \n");
    scanf("%d %c", &filaElegida+6, &letraAsientoElegido);
    printf("Has elegido el asiento: %d%c", filaElegida, letraAsientoElegido);

    printf("\n    desde el clt es:    %d       \n", &filaElegida+6);
	printf("\n    desde el clt es:    %d       \n", filaElegida);
	//printf("\n    desde el clt es:    %d       \n", *filaElegida);


    



}