#include <stdio.h>
#include <stdlib.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente\cliente.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void main(void)
{
	int opc = 0;
	do{
		system("cls");
		printf("BIENVENIDO A LA SALA DE CINE. ESCOJA UNA OPCIÓN \n\n");
		printf("1. Iniciar sesión como Administrador\n");
		printf("2. Iniciar sesión como Cliente\n");
		printf("3. Salir\n");
		printf("Opcion a escoger: ");
		scanf("%d", &opc);
		switch(opc){
			case 1;
				system("cls");
				printf("Bienvenido Administrador, ¿Qué desea gestionar?\n\n");
				printf("1. Reservas\n"); //Si selecciona 1 tendrá otro menú. 1.Visualizar reservas realizadas y canceladas. 2.Eliminar reservas canceladas.
				printf("2. Películas\n"); //Si selecciona 2 tendrá otro menú. 1.Añadir películas. 2.Eliminar películas
				printf("3. Modificaciones generales\n"); //Si selecciona 3 tendrá otro menú...
				printf("4. Salir\n");
			case 2;
				system("cls");
				printf("¡Bienvenido!\n\n")
				printf("1. Películas\n");
				printf("2. Fechas\n");
				printf("3. Salir");
			case 3;
				break;
			default;
				system("cls");
				printf("La opción seleccionada no es correcta");
				getch();
				break;
		}
	}while(opc != 3);
	return 0;
<<<<<<< HEAD
=======
=======
	/*FILE *f = fopen("DatosUsuarios.txt", "r");

////////////////////////////////////////////////BASE DE DATOS//////////////////////////////////////////////////////
	sqlite3 *db;
	char *error; //variable para almacenar los errores que srugen en la bd

    int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &baseDatos);

    if (baseDatos) {
        fprintf(stderr, "No se pusdo abrir la base de datos: %s\n", error);
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "La base de datos se ha abierto correctamente\n");
    }

    //CREACION DE LA TABLA PELICULA
    char *sql = "CREATE TABLE Pelicula (id_pel INT PRIMARY KEY NOT NULL, nom_pel TEXT NOT NULL, genero_pel TEXT, dir_pel TEXT NOT NULL, duracion_pel TEXT NOT NULL)";

    baseDatos = sqlite3_exec(db, sql, NULL, 0, &error);

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", error);
        sqlite3_free(error);
		sqlite3_close(db);
		return 1;
    } else {
        fprintf(stdout, "La tabla de Pelicula se ha creado correctamente\n");
    }

	//CREACION DE LA TABLA SALAS DE CINE
    char *sql = "CREATE TABLE SalasCine (id_sala INT PRIMARY KEY NOT NULL, num_sala INT NOT NULL, capacidad_sala INT NOT NULL)";

    baseDatos = sqlite3_exec(db, sql, NULL, 0, &error);

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", error);
        sqlite3_free(error);
		sqlite3_close(db);
		return 1;
    } else {
        fprintf(stdout, "La tabla de SalasCine se ha creado correctamente\n");
    }

	//CREACION DE LA TABLA HORARIOS
    char *sql = "CREATE TABLE Horario (id_horario INT PRIMARY KEY NOT NULL, FechaHoraInicio TEXT NOT NULL, FechaHoraFin TEXT NOT NULL, idPelicula INT NOT NULL, FOREIGN KEY (idPelicula) REFERENCES Pelicula(id_pel), idSala INT NOT NULL, FOREIGN KEY (idSala) REFERENCES SalasCine(id_sala))";

    baseDatos = sqlite3_exec(db, sql, NULL, 0, &error);

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", error);
        sqlite3_free(error);
		sqlite3_close(db);
		return 1;
    } else {
        fprintf(stdout, "La tabla de Horario se ha creado correctamente\n");
    }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
>>>>>>> 9002b5dc0b21b597ea980e88d2bb316abbad9b59

	int numEntradas = 3;
	int numEntradasSeleccionadas = 0;	

	AsientoElegido *arrayAsientosElegidos;
	arrayAsientosElegidos = malloc(numEntradas*sizeof(AsientoElegido));

	generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);

	for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++)
	{
		elegirAsiento(arrayAsientosElegidos,numEntradasSeleccionadas);
		generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);

		}

	Usuario *lista = NULL;
	Usuario usuario;

	if (sqlite3_open(baseDatos, &db) != SQLITE_OK){
		return gestionaError(db);
	}

	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo %s\n", f);
		 ferror(f);
	}

	while (!feof(f)){
		fscanf(f, "%s;%d");
	}*/
	
}
	



  






//testAlonso
//testDelPojo
//testTxingas
//testMarkos
