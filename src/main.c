#include <stdio.h>
#include <stdlib.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente\cliente.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void main(void)
{
	FILE *f = fopen("DatosUsuarios.txt", "r");
	 sqlite3 *db;
    int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &baseDatos);

    if (baseDatos) {
        fprintf(stderr, "No se pusdo abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "La base de datos se ha abierto correctamente\n");
    }

    //creacion de tablas para la base de datos: acordar cuales todavia
    char *sql = "CREATE TABLE pelicula (id_pel INT PRIMARY KEY NOT NULL, nom_pel TEXT NOT NULL, duracion INT NOT NULL)";

    baseDatos = sqlite3_exec(db, sql, NULL, 0, sqlite3_errmsg(db)); //errmsg es como estaba con fallo

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", sqlite3_errmsg(db)); //errmsg
        sqlite3_free(sqlite3_errmsg(db)); //errmsg
    } else {
        fprintf(stdout, "La tabla se ha creado correctamente\n");
    }

    char *sql = "CREATE TABLE usuario (nombreUsuario TEXT PRIMARY KEY, password TEXT);";
    baseDatos = sqlite3_exec(db, sql, NULL, 0, NULL);
    if (baseDatos != SQLITE_OK) {
    fprintf(stderr, "Error al crear la tabla: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    return 1;
    }
	
	char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];

	printf("Nombre de usuario: ");
  	scanf("%s", nombreUsuario);
 	printf("Contrasena: ");
  	scanf("%s", contraseyna);

	Usuario u = leeUsuario(nombreUsuario); //CREO QUE EL ERROR ES POR COMO ESTÁ DEFINIDA LA ESTRUCTURA PERO NO LO ENTIENDO
	 if (strcmp(u.nombreUsuario, "") == 0) {
    agregarUsuario(nombreUsuario, contraseyna);
    printf("Usuario registrado\n");
	 } else {
    if (strcmp(contraseyna, u.contraseyna) == 0) {
      printf("Sesion iniciada\n");
    } else {
      printf("Contraseña incorrecta\n");
    }
  }

	int numEntradas = 3;
	int numEntradasSeleccionadas = 0;	

	AsientoElegido *arrayAsientosElegidos;
	arrayAsientosElegidos = malloc(numEntradas*sizeof(AsientoElegido));

	generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);

	for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++)
	{
		elegirAsiento(arrayAsientosElegidos,numEntradasSeleccionadas);
		generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);

		int loop;

   			for(loop = 0; loop < numEntradasSeleccionadas+1; loop++){

     		 printf(" ARRAY %d ", arrayAsientosElegidos[loop].filaElegida);
			 printf("ARRAY %c ", arrayAsientosElegidos[loop].letraAsientoElegido);

			 }
		}

	Usuario *lista = NULL;
	Usuario usuario;

	if (sqlite3_open(baseDatos, &db) != SQLITE_OK){
		gestionaError(db);
	}

	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo %s\n", f);
		 ferror(f);
	}

	while (!feof(f)){
		fscanf(f, "%s;%d");
	}
	
}
	



  






//testAlonso
//testDelPojo
//testTxingas
//testMarkos
