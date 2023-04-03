#include "../../sqlite3.h"
#include "connect.h"
#include <stdio.h>
#include "../../struct.h"
#include <string.h>
#include <stdlib.h>

int openDB(sqlite3 *db){

	  char *error = NULL;

    int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &db);

    if (baseDatos) {
        fprintf(stderr, "No se pudo abrir la base de datos: %s\n", error);
        sqlite3_close(db);
        return 1;
    } 

    fprintf(stdout, "La base de datos se ha abierto correctamente\n");
     sqlite3_close(db);
    return 0;
}

int tablaPelicula(sqlite3* db, char* error){

 int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
  char *sql = "CREATE TABLE IF NOT EXISTS Pelicula (id_pel INT PRIMARY KEY NOT NULL, nom_pel TEXT NOT NULL, genero_pel TEXT, dir_pel TEXT NOT NULL, duracion_pel TEXT NOT NULL, precio INT NOT NULL)";
  result = sqlite3_exec(db, sql, 0, 0, &error);
  
  if (result != SQLITE_OK) {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
    sqlite3_free(error);
    return 1;
  } else {
    fprintf(stdout, "La tabla Pelicula se ha creado correctamente\n");
  }

  sqlite3_close(db);
  return 0;
}

int tablaHorario(sqlite3* db, char* error){

  int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
  char *sql = "CREATE TABLE IF NOT EXISTS Horario (id_horario INT PRIMARY KEY NOT NULL, HoraInicio TEXT NOT NULL, HoraFin TEXT NOT NULL, idPelicula TEXT NOT NULL, FOREIGN KEY (idPelicula) REFERENCES Pelicula(id_pel), fechaHorario INT NOT NULL, FOREIGN KEY (fechaHorario) REFERENCES Fecha(id_fecha))";
  result = sqlite3_exec(db, sql, 0, 0, &error);
  
  if (result != SQLITE_OK) {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
    sqlite3_free(error);
    return 1;
  } else {
    fprintf(stdout, "La tabla Horario se ha creado correctamente\n");
  }

  sqlite3_close(db);
  return 0;
}

int tablaFecha(sqlite3* db, char* error){
  
  int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
  char *sql = "CREATE TABLE IF NOT EXISTS Fecha (fecha TEXT PRIMARY KEY NOT NULL, numPeliculas INT NOT NULL, idPeliculaFecha INT NOT NULL, FOREIGN KEY (idPeliculaFecha) REFERENCES Pelicula(id_pel))";
  result = sqlite3_exec(db, sql, 0, 0, &error);
  
  if (result != SQLITE_OK) {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
    sqlite3_free(error);
    return 1;
  } else {
    fprintf(stdout, "La tabla Fecha se ha creado correctamente\n");
  }

  sqlite3_close(db);
  return 0;
}

int tablaUsuario(sqlite3* db, char* error){

    int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
    FILE* f = fopen("DatosUsuarios.txt", "r");

    char* sql2 = "CREATE TABLE IF NOT EXISTS usuario (nombreUsuario TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL)";
    result = sqlite3_exec(db, sql2, 0, 0, &error);  

	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo %s\n", f);
	 	ferror(f);
	}

  if (result != SQLITE_OK) {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
		sqlite3_free(error);
   	sqlite3_close(db);
    return 1;
  }else {
    fprintf(stdout, "La tabla Usuario se ha creado correctamente\n");
  }

  fclose(f);
  sqlite3_close(db);
  return 0;
}

void agregarUsuario(char *username, char *password, char *dni, char *correo, char *tlf, sqlite3* db){

      FILE* f;
      f = fopen("DatosUsuarios.txt", "a");
      int rc = sqlite3_open("baseDeDatosCine.sqlite", &db);
      sqlite3_stmt *stmt;

       if (f == NULL) {
    printf("Error al abrir el fichero\n");
  }

  printf("Elije tu nombre de usuario: ");
  scanf("%s", username);
  printf("Elige cual va ser tu contrasena: ");
  scanf("%s", password);
  printf("Ingresa tu dni: ");
  scanf("%s", dni);
  printf("Ingresa tu correo: ");
  scanf("%s", correo);
  printf("Ingresa tu numero de tlf: ");
  scanf("%s", tlf);

  fprintf(f, "%s %s\n", username, password);

  char sql[] = "insert into usuario (nombreUsuario, password) values (?, ?)";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

  if(result != SQLITE_OK){
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC );

  if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

  result = sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);

  if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error al insertar los datos\n");
	}

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error al cerrar la consulta\n");
		printf("%s\n", sqlite3_errmsg(db));
	}

  fclose(f);
  sqlite3_close(db);

}

Usuario leeUsuario(char* user, char* password, sqlite3* db){
    Usuario u;
    FILE* f;
    int rc = sqlite3_open("baseDeDatosCine.sqlite", &db);
    f = fopen("DatosUsuarios.txt", "r");
    sqlite3_stmt* stmt;

    if (f == NULL) {
    printf("Error al abrir el archivo.\n");
    }
  printf("User:%s, Pass:%s\n",user,password);
   int lectura = fgetc(f);
   char sql[] = ("SELECT * FROM usuario WHERE nombreUsuario = ? AND password = ?");

	 int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

  result = sqlite3_bind_text(stmt, 1, user, strlen(user), SQLITE_STATIC);
  result = sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);
  if(result != SQLITE_OK){
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  do {
		result = sqlite3_step(stmt) ;

		if (result == SQLITE_ROW) {
      password=malloc(sizeof(char)*(strlen( sqlite3_column_text(stmt, 1)+1)));
			strcpy(password,(char *) sqlite3_column_text(stmt, 1));
      user=malloc(sizeof(char)*(strlen( sqlite3_column_text(stmt, 0)+1)));
			strcpy(user, (char *) sqlite3_column_text(stmt, 0));
		}
	} while (result == SQLITE_ROW);
   
       while (fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) !=EOF) {
        
          if (strcmp(user, u.nombreUsuario) == 0) { 
            printf("Usuario encontrado\n");
            return u;
         }
      }

  fclose(f);
  result = sqlite3_finalize(stmt);

  if(result != SQLITE_OK){
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  return u;
}


  Usuario login(char *usuario, char *password, char *dni, char *correo, char *tlf, sqlite3* db){

  Usuario u;

  printf("Introduce tu nombre de usuario, si no tienes escribe 'n': ");
  scanf("%s", usuario);

  if(strcmp(usuario, "n") == 0){

		agregarUsuario(usuario, password, dni, correo, tlf, db);
		printf("Usuario registrado, felicidades, ya puedes iniciar sesion con ese usuario\n");
    printf("Introduce tu nombre de usuario: ");
    scanf("%s", usuario);
    printf("Ingresa tu contraseña: ");
    scanf("%s", password);

  }else{

    printf("Ingresa tu contraseña: ");
    scanf("%s", password);
 }
  
  u = leeUsuario(usuario, password, db);
  if (strcmp(usuario, u.nombreUsuario) && strcmp(password, u.contraseyna) != 0) {
    printf("Usuario o contraseña incorrectos\n");
    exit(0);
      } 

    printf("Sesion iniciada\n");

 return u;

}