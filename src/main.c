#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente/cliente.h"
#include "../db/connect/connect.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void main(void)
{
	sqlite3 *db;
	char* error;
////////////////////////////////////////////////BASE DE DATOS//////////////////////////////////////////////////////
	int baseDedatos = openDB(db);
    int pelicula = tablaPelicula(db, error);
    int horario = tablaHorario(db, error);
    int fecha = tablaFecha(db, error);
    int usuario = tablaUsuario(db, error);
	
	char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];

	char* a = malloc((strlen(nombreUsuario)+1)*sizeof(char));
	a = strcpy(a,nombreUsuario);
	a[strlen(a)]='\0';

//	Usuario u = leeUsuario(a, db); 

	printf("\n");
	printf("Bienvenido/a, ahora puedes iniciar sesion\n");
	printf("\n");

	Usuario	u = login(a, contraseyna, db);

	// if (strcmp(nombreUsuario, u.nombreUsuario) && strcmp(contraseyna, u.contraseyna) == 0) {
    //   printf("Sesion iniciada\n");
    //  } else {
    //    printf("Usuario o contraseña incorrectos\n");
    //  }


// 	 if (strcmp(u.nombreUsuario, nombreUsuario) == 0) {
//     agregarUsuario(nombreUsuario, contraseyna, db);
//     printf("Usuario registrado\n");
// 	 } else {
//     if (strcmp(nombreUsuario, u.nombreUsuario) && strcmp(contraseyna, u.contraseyna) == 0) {
//       printf("Sesion iniciada\n");
//     } else {
//       printf("Usuario o contraseña incorrectos\n");
//     }
//   }

  free(a);

//////////////////////PARTE ALONSO, SELECCION DE ASIENTOS
	int numEntradas = 3;
	int numEntradasSeleccionadas = 0;	

	AsientoElegido *arrayAsientosElegidos;
	arrayAsientosElegidos = malloc(numEntradas*sizeof(AsientoElegido));

	generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);


	for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++)
	{

		elegirAsiento(arrayAsientosElegidos,numEntradasSeleccionadas);
		generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);
    	numEntradasSeleccionadas = confirmacionAsiento(numEntradasSeleccionadas);

		}

////////////////////////////////////FIN PARTE ALONSO
	
}
	

//testAlonso
//testDelPojo
//testTxingas
//testMarkos
