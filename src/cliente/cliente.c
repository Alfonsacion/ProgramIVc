#include "cliente.h"
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include "../../struct.h"
#include "../../db/connect/connect.h"
#include "../../sqlite3.h"

void generarSalaA(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas, int numEntradas){

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

        for (i=0; i<numFilas; i++) {
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
    printf("////////////////////////////////////////////////////////////////////////////\n");
    printf("Compruebe el nuevo esquema, es el asiento elegido correcto? (S-> Si, N-> No)\n");
    printf("////////////////////////////////////////////////////////////////////////////");
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


Seleccion pantallaCartelera(const char **arrayPeliculas, int numPeliculas, sqlite3 *db){

    int cambiarDias = 1;
    int diaActual = 0;
    Seleccion s;


    while (cambiarDias == 1){

    char arrDias[7][10] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};


    printf("\n");
    printf("\n");
    printf("/////////// Estas visualizando las peliculas para el %s ///////////////////", arrDias[diaActual]);
    printf("\n");
    printf("\n");
    printf("Para visualizar el siguiente dia, escriba 1 y presione Enter");
    printf("\n");
    printf("\n");
    printf("Para visualizar el dia anterior, escriba 0 y presione Enter");
    printf("\n");
    printf("\n");    
    printf("Para elegir una pelicula, escriba su numero y presione Enter");
    printf("\n");
    printf("\n");  

    Pelicula p = verPeliculas(db);

    printf("\n");
    printf("\n");
    
    
    printf("Escriba aqui su seleccion mediante el numero correspondiente: "); 
    scanf("%1d", s.seleccion);

    if (s.seleccion == 0){
        if (diaActual == 0){
            diaActual =6;
        }else
        {
            --diaActual;
        }
        

    }else if (s.seleccion == 1){
         if (diaActual == 6){
            diaActual =0;
        }else
        {
            ++diaActual;
        }

    }else{
        cambiarDias = 0;
    }
        }
    
    return s;
}


int seleccionHorarios(int seleccionPelicula, char* dia, const char **arrayHorarios, const char **arrayPeliculas){
    
    int seleccionHorario;
    int numHorarios = 4;
    Pelicula p;
    Horario h;
    sqlite3 *db;
    
    printf("\n");
    printf("\n");
    printf("///////////Seleccione un horario///////////");
    printf("\n");
    printf("\n");
    int rc = sqlite3_open("baseDeDatosCine.sqlite", &db);
    if (rc != SQLITE_OK) {
        printf("Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return -1; 
    }

    p = obtenerPeliculaPorId(seleccionPelicula, db);
    printf("Los horarios disponibles para %s son: ", p.nom_pel);
    printf("\n");
    printf("\n");

    h = verHorarios(p.nom_pel, dia, db);

    printf("\n\n Indique el numero del horario que desee: ");
    scanf("%1d", &seleccionHorario);
    printf("\n\nEscriba 'v' y presione Enter para volver a la cartelera de peliculas.\n\n");

    printf("\n \n El horario seleccionada es %s  \n \n", arrayHorarios[seleccionHorario]);

    return seleccionHorario;
}   

int confirmacionTicket(int seleccionPelicula, const char **arrayPeliculas, const char **arrayHorarios, int seleccionHorario){    

    int numEntradas;
    int precio = 5;
    
    printf("\n \n ///////////Confirmacion de tickets///////////");
    printf("\n \n Usted ha seleccionado: %s", arrayPeliculas[seleccionPelicula] );
    printf("\n \n Usted ha seleccionado el horario:  %s", arrayHorarios[seleccionHorario]);
    printf("\n\n El precio de la entrada para esta pelicula es de %d euros", precio);
    printf("\n\n Indique el número de entradas que desea comprar: ");
    scanf("%1d", &numEntradas);
    printf("\n\n Has seleccionado reservar &d entradas.", numEntradas);
    printf("\n\n Escriba 'v' y presione Enter para volver a la selección del horario");

    return numEntradas;

}

void confirmacionDefinitiva(int seleccionPelicula, const char **arrayPeliculas, int seleccionHorario, const char **arrayHorarios, int numEntradas, AsientoElegido **arrayAsientosElegidos, int numEntradasSeleccionadas){
    
    printf("\n\n ///////////Confirmacion de tickets///////////");
    printf("\n\n Has seleccionado: \n\n La pelicula: %s", arrayPeliculas[seleccionPelicula]);
    printf("\n El horario: %s", arrayHorarios[seleccionHorario]);
    printf("\n Numero de entradas: %s", numEntradas);
    //printf("\n Los asientos seleccionados: %1d %1c", arrayAsientosElegidos[numEntradasSeleccionadas].filaElegida, arrayAsientosElegidos[numEntradasSeleccionadas].letraAsientoElegido);
    
    

}


void exportarDatos(int numEntradasSeleccionadas, int seleccionPelicula, const char **arrayPeliculas){

    FILE *historial;

    const char *usuario = "Iker Gonzalez";
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

        printf("\n\n Preparando \n\n");


    historial = fopen("../historial/historialCompras.txt", "a");

    fprintf(historial, "\n El usuario %s reservo %d entradas para %s el %d-%02d-%02d", usuario, numEntradasSeleccionadas, arrayPeliculas[seleccionPelicula], tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    fclose(historial);

        printf("\n\n Listo \n\n");



}

void datosUsuario (char usuario[100], char dni[100], char correo[100], char telefono[100]){
        printf("\n\n///////////Esta visualizando sus datos///////////\n\n");
        printf("Usuario: %s", usuario);
        printf("\n\nDNI: %s", dni);
        printf("\n\nCorreo: %s", correo);
        printf("\n\nTelefono de contacto: %s", telefono);
}

void datosPeliculas(const char **arrayPeliculas, int numPeliculas){
        printf("\n\n///////////Esta visualizando todas las peliculas disponibles actualmente///////////\n\n");
        for (int i = 1; i <= numPeliculas; i++) {

            printf("%d %s \n", i, arrayPeliculas[i]);
        }



}








