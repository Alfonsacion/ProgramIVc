/*#include <sqlite3.h>
#include <sqlite3.c>

 void main (void) {
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

     char *sql = "CREATE TABLE usuario (nombreUsuario TEXT PRIMARY KEY, password TEXT);";
     baseDatos = sqlite3_exec(db, sql, NULL, 0, NULL);
     if (baseDatos != SQLITE_OK) {
     fprintf(stderr, "Error al crear la tabla: %s\n", sqlite3_errmsg(db));
     sqlite3_close(db);
     return 1;
     }

     sqlite3_close(db);
 }*/
