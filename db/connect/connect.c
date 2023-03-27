#include "../../sqlite3.h"
#include "connect.h"
#include <stdio.h>
#include "../../struct.h"
#include <string.h>
#include <stdlib.h>

int openDB(sqlite3 *db){

	  char *error = NULL; //variable para almacenar los errores que srugen en la bd

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

//    char* sql = "INSERT INTO usuario (nombreUsuario, password) VALUES ('Iker', 456);";
//    result = sqlite3_exec(db, sql, 0, 0, &error);

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

void agregarUsuario(char *username, char *password, sqlite3* db){
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

  fprintf(f, "%s;%s\n", username, password);

  char sql[] = "insert into usuario (nombreUsuario, password) values (?, ?)";
	int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

  //sql = sqlite3_mprintf("INSERT INTO usuario (nombreUsuario, password) VALUES ('%s', %d)", username, password);
  //int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

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

// Usuario *leerDeBase(char *username, char *password) {
//     sqlite3 *db;
//     if (sqlite3_open("baseDeDatosCine.sqlite", &db) != SQLITE_OK) {
//         return NULL;
//     }

//     char *sql = "SELECT nombreUsuario, password FROM usuario WHERE username = ? AND password = ?";
//     sqlite3_stmt *stmt;
//     if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
//         sqlite3_close(db);
//         return NULL;
//     }

//     sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
//     if (sqlite3_step(stmt) != SQLITE_ROW) {
//         sqlite3_finalize(stmt);
//         sqlite3_close(db);
//         return NULL;
//     }

//     sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

//     *password = strdup((char*)sqlite3_column_text(stmt, 0));
//     Usuario *user = malloc(sizeof(Usuario));
//     user->nombreUsuario = username;
//     user->contraseyna = password;
//     sqlite3_finalize(stmt);
//     sqlite3_close(db);
//     return user;
// }

Usuario leeUsuario(char* user, char* password, sqlite3* db){
    Usuario u;
    FILE* f;
    int rc = sqlite3_open("baseDeDatosCine.sqlite", &db);
    f = fopen("DatosUsuarios.txt", "r");
    sqlite3_stmt* stmt;

    if (f == NULL) {
    printf("Error al abrir el archivo.\n");
    }

   int lectura = fgetc(f);
   char sql[] = ("SELECT * FROM usuario WHERE nombreUsuario = '?' AND password = ?");
	 int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) ;

  if(result != SQLITE_OK){
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			*password = sqlite3_column_int(stmt, 0);
			strcpy(user, (char *) sqlite3_column_text(stmt, 1));
			printf("Usuario: %s Contrasena: %d\n", user, password);
		}
	} while (result == SQLITE_ROW);
   

    int count = 0;

       while (fscanf(f, "%s;%s", u.nombreUsuario, u.contraseyna) == 2 && result == SQLITE_ROW) {
         count++;
        if (strcmp(user, u.nombreUsuario) == 0 && count > 0) { 
         printf("Usuario encontrado\n");
         return u;
       } else {
         printf("Usuario no encontrado\n");
        }
      }

  fclose(f);
  result = sqlite3_finalize(stmt);

  if(result != SQLITE_OK){
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  strcpy(u.nombreUsuario, "");
  strcpy(u.contraseyna, "");
  return u;
}

// Usuario* leerDeFichero (char* user, char* password){
//    FILE* f = fopen("DatosUsuarios.txt", "r");
//     if (f == NULL) {
//       printf("Error al abrir el archivo.\n");
//     }

//     char line[100];
//     while (fgets(line, sizeof(line), f)) {
//         char *token = strtok(line, ",");
//         if (strcmp(token, user) == 0) {
//             *password = strtok(NULL, ",");
//             Usuario *u = malloc(sizeof(Usuario));
//             u->nombreUsuario = user;
//             u->contraseyna = password;
//             fclose(f);
//             return (Usuario*)user;
//         }
//     }

//     fclose(f);
//     return NULL;
// }


  Usuario login(char *usuario, char *password, sqlite3* db){

    Usuario u = leeUsuario(usuario, password, db);
 // Usuario* ub = leerDeBase(usuario, password);
 // Usuario* uf = leerDeFichero(usuario, password);

  printf("Introduce tu nombre de usuario, si no tienes escribe 'n': ");
  scanf("%s", usuario);

  if(strcmp(usuario, "n") == 0){
		agregarUsuario(usuario, password, db);
		printf("Usuario registrado, felicidades, se te iniciara la sesion automaticamente\n");

  }else{

    printf("Ingresa tu contraseña: ");
    scanf("%s", password);
 }

  if (strcmp(usuario, u.nombreUsuario) && strcmp(password, u.contraseyna) != 0) {
    printf("Usuario o contraseña incorrectos\n");
    exit(0);
      } 

    printf("Sesion iniciada\n");

 return u;

}