#include "cliente.h"
#include <stdio.h>
#include<stdlib.h>


void generarSalaA(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas){

    	printf("\n");
        printf("Seleccione un asiento escribiendo su numero y letra: \n");
    	printf("Tenga en cuenta que los asientos marcados con 'X' no estan disponibles. \n ");
        printf("\n");

        int numFilas = 5; 
        int numAsientosXFila = 8;

        char **salaA;
        salaA = (char**)malloc(sizeof(char*)*numFilas);

        int i;
        int i2;
        int doble =0;

        for (i=0; i<5; i++) {
            salaA[i] = (char*)malloc(numAsientosXFila * (sizeof(char)*3));
            *salaA[i] = i + 49;
            printf("%c     ", *salaA[i]);

            for (i2=0; i2<numAsientosXFila; i2++){

               for (int i3 = 0; i3 < numEntradasSeleccionadas+1; i3++){

                    if (i2 == (int) arrayAsientosElegidos[i3].letraAsientoElegido -65){
                    if (i == arrayAsientosElegidos[i3].filaElegida -1){
                    salaA[i][i2] = 88;
                    printf("  [ %c ]  ", salaA[i][i2]);
                    doble = 1;
                    break;

                    }else{
                            salaA[i][i2] = 45;
                            doble = 0;
                    }

                }else{            
                        salaA[i][i2] = 45;
                        doble = 0;
                    }
             }

             if(doble == 0){

              printf("  [ %c ]  ", salaA[i][i2]);

             }


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

    int asientoValido =0;

    while(asientoValido == 0){

            printf("\n");
            printf("\n");
            printf("Introduce un asiento del esquema de la sala: \n");

            scanf("%1d %1c", &arrayAsientosElegidos[numEntradasSeleccionadas].filaElegida, &arrayAsientosElegidos[numEntradasSeleccionadas].letraAsientoElegido);

                    int arrLen = sizeof arrayAsientosElegidos / sizeof arrayAsientosElegidos[0];
                    int presenteEnArray = 0; 

                    for (int i = 0; i < numEntradasSeleccionadas; i++) {
                        if (arrayAsientosElegidos[i].filaElegida == arrayAsientosElegidos[numEntradasSeleccionadas].filaElegida) { 
                                                    if (arrayAsientosElegidos[i].letraAsientoElegido == arrayAsientosElegidos[numEntradasSeleccionadas].letraAsientoElegido) { 
                            presenteEnArray = 1; 
                            break;
                             }
                        }
                    }






                 if (arrayAsientosElegidos[numEntradasSeleccionadas].filaElegida <= 5 && arrayAsientosElegidos[numEntradasSeleccionadas].filaElegida >= 1 && arrayAsientosElegidos[numEntradasSeleccionadas].letraAsientoElegido <= 72 && arrayAsientosElegidos[numEntradasSeleccionadas].letraAsientoElegido >= 65 ){
                                    if (presenteEnArray ==0){ 
                    fflush(stdin);
                    printf("\n");
                    asientoValido=1;

                    //printf("Has elegido el asiento: %d%c \n", arrayAsientosElegidos[0].filaElegida, arrayAsientosElegidos[0].letraAsientoElegido);

                }else{
                    fflush(stdin);
                    printf("\n");
                    printf("\n");
                    printf("////////////////// Ese asiento ya esta elegido! Por favor selecione uno disponible del esquema de la sala. //////////////////");
                    printf("\n");
                    printf("\n");

                                       

                 }
                }else{
                    fflush(stdin);
                    printf("\n");
                    printf("\n");
                    printf("////////////////// Ese asiento no existe! Por favor selecione una fila y letra visible del esquema de la sala. //////////////////");
                    printf("\n");
                    printf("\n"); 

                    } 
                
         }
}

int confirmacionAsiento(int numEntradasSeleccionadas){

    char confirmacion;

    printf("\n");
    printf("\n");
    printf("Compruebe el nuevo esquema, es el asiento elegido correcto? (S-> Si, N-> No)");
    printf("\n");
    printf("\n");    

    scanf("%c", &confirmacion);

    if (confirmacion == 'S'){
    printf("\n");
    printf("\n");
      printf("Genial, has elegido tu entrada %d.", numEntradasSeleccionadas+1);
          printf("\n");

    }else{
    printf("\n");
    printf("\n");
      printf("Tu seleccion ha sido borrada, vuelve a elegir el asiento.");
          printf("\n");

      numEntradasSeleccionadas = numEntradasSeleccionadas-1;
    }

    return numEntradasSeleccionadas;
}


