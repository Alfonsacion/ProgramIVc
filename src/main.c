#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente/cliente.h"
#include "../db/connect/connect.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

int main(void)
{

////////////////////////////////////////////////BASE DE DATOS//////////////////////////////////////////////////////
	sqlite3 *db;
	char *error; //variable para almacenar los errores que srugen en la bd

    int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &baseDatos);

    if (baseDatos) {
        fprintf(stderr, "No se pudo abrir la base de datos: %s\n", error);
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "La base de datos se ha abierto correctamente\n");
	}

//CREACION DE LA TABLA PELICULA
    char *sqla = "CREATE TABLE Pelicula (id_pel INT PRIMARY KEY NOT NULL, nom_pel TEXT NOT NULL, genero_pel TEXT, dir_pel TEXT NOT NULL, duracion_pel TEXT NOT NULL, precio INT NOT NULL)";

    baseDatos = sqlite3_exec(db, sqlite3_reset_auto_extension, NULL, 0, &error);

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", error);
        sqlite3_free(error);
		sqlite3_close(db);
		return 1;
    } else {
        fprintf(stdout, "La tabla de Pelicula se ha creado correctamente\n");
    }

	//CREACION DE LA TABLA HORARIO
    char *sqlb = "CREATE TABLE Horario (id_horario INT PRIMARY KEY NOT NULL, HoraInicio TEXT NOT NULL, HoraFin TEXT NOT NULL, idPelicula TEXT NOT NULL, FOREIGN KEY (idPelicula) REFERENCES Pelicula(id_pel), fechaHorario INT NOT NULL, FOREIGN KEY (fechaHorario) REFERENCES Fecha(id_sala))";

    baseDatos = sqlite3_exec(db, sqlb, NULL, 0, &error);

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", error);
        sqlite3_free(error);
		sqlite3_close(db);
		return 1;
    } else {
        fprintf(stdout, "La tabla de Horario se ha creado correctamente\n");
    }

	//CREACION DE LA TABLA FECHA
    char *sqlc = "CREATE TABLE Fecha (fecha TEXT PRIMARY KEY NOT NULL, numPeliculas INT NOT NULL, idPeliculaFecha INT NOT NULL, FOREIGN KEY (idPeliculaFecha) REFERENCES Pelicula(id_pel))";

    baseDatos = sqlite3_exec(db, sqlc, NULL, 0, &error);

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", error);
        sqlite3_free(error);
		sqlite3_close(db);
		return 1;
    } else {
        fprintf(stdout, "La tabla de Fecha se ha creado correctamente\n");
    }
/////////////////////////////////////////Parte Gon//////////////////////////////////////////////////////////////////////////

	FILE* f = fopen("DatosUsuarios.txt", "r");
    char* sql2 = "CREATE TABLE usuario (nombreUsuario TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL);";
    baseDatos = sqlite3_exec(db, sql2, NULL, 0, NULL);

	if (sqlite3_open(baseDatos, &db) != SQLITE_OK){
		return gestionaError(db);
	}

	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo %s\n", f);
	 	ferror(f);
	}

	while (!feof(f)){
		fscanf(f, "%s;%d");
	}

    if (baseDatos != SQLITE_OK) {
    	fprintf(stderr, "Error al crear la tabla: %s\n", error);
		sqlite3_free(error);
   	    sqlite3_close(db);
        return 1;

    }else {
        fprintf(stdout, "La tabla Usuario se ha creado correctamente\n");
    }

	char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];

	iniciarSesion(nombreUsuario, contraseyna);

	char* a = malloc((strlen(nombreUsuario)+1)*sizeof(char));
	a= strcpy(a,nombreUsuario);
	a[strlen(a)]='\0';
	Usuario u = leeUsuario(a, db); 

	 if (strcmp(u.nombreUsuario, "") == 0) {
    agregarUsuario(nombreUsuario, contraseyna, db);
    printf("Usuario registrado\n");
	 } else {
    if (strcmp(contraseyna, u.contraseyna) == 0) {
      printf("Sesion iniciada\n");
    } else {
      printf("Contraseña incorrecta\n");
    }
  }

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
