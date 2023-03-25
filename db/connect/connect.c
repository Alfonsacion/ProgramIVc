#include "../../sqlite3.h"
#include "connect.h"
#include <stdio.h>
#include "../../struct.h"
#include <string.h>
#include <stdlib.h>

int openDB(sqlite3 *db){

	  char *error; //variable para almacenar los errores que srugen en la bd

    int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &baseDatos);

    if (baseDatos) {
        fprintf(stderr, "No se pudo abrir la base de datos: %s\n", error);
        sqlite3_close(db);
        return 1;
    } 

    fprintf(stdout, "La base de datos se ha abierto correctamente\n");
	  sqlite3_close(db);
    return 0;
}

int gestionaError (sqlite3 *db){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}

int tablaPelicula(sqlite3* db, char* error){

  int baseDatos;
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

  sqlite3_close(db);
  return 0;

}

int tablaHorario(sqlite3* db, char* error){

  int baseDatos;
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

  sqlite3_close(db);
  return 0;

}

int tablaFecha(sqlite3* db, char* error){
  
   int baseDatos;
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

  sqlite3_close(db);
  return 0;

}
int tablaUsuario(sqlite3* db, char* error){

    int baseDatos;
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

  sqlite3_close(db);
  return 0;
}

void agregarUsuario(char *username, char *password, sqlite3* db){
      FILE* f;
      f = fopen("DatosUsuarios.txt", "a");
      sqlite3_stmt *stmt;
      char *sql;

       if (f == NULL) {
    printf("Error al abrir el fichero\n");
  }

  fprintf(f, "%s;%s\n", username, password);

  sql = sqlite3_mprintf("INSERT INTO usuarios (nombre, contrasena) VALUES ('%q', %d)", username, password);
  int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if(result != SQLITE_OK){
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

   result = sqlite3_finalize(stmt);

  if(result != SQLITE_OK){
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  fclose(f);
  sqlite3_close(db);

}

Usuario leeUsuario(char* user, sqlite3* db){
    Usuario u;
    FILE* f;
    f = fopen("DatosUsuarios.txt", "r");
    sqlite3_stmt* stmt;
    char* sql;

    if (f == NULL) {
    printf("Error al abrir el archivo.\n");
    }

   int fgetc(f);
   sql = sqlite3_mprintf("SELECT * FROM usuarios WHERE nombre = '%s'", user);
   int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if(result != SQLITE_OK){
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }
   

    int count = 0;

    do{
       if (fscanf(f, "%s;%s", u.nombreUsuario, u.contraseyna) == 2 && result == SQLITE_ROW) {
         count++;
       if (strcmp(user, u.nombreUsuario) == 0 && count > 0) { 
         printf("Usuario encontrado\n");
         fclose(f);
         sqlite3_close(db);
         return u;
      } else {
         printf("Usuario no encontrado\n");
      }
    }
   } while(fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) == 2 && result == SQLITE_ROW);

  fclose(f);
  result = sqlite3_finalize(stmt);

  if(result != SQLITE_OK){
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_finalize(stmt);
  strcpy(u.nombreUsuario, "");
  strcpy(u.contraseyna, "");
  return u;
}

 void iniciarSesion(char *usuario, char *password){
  printf("Introduce tu nombre de usuario: ");
 scanf("%s", usuario);
  printf("Ingresa tu contraseña: ");
  scanf("%s", password);
 }


