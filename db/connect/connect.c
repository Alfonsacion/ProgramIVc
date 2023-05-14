#include "../../sqlite3.h"
#include "connect.h"
#include <stdio.h>
#include "../../struct.h"
#include <string.h>
#include <stdlib.h>

int openDB(sqlite3 *db)
{

  char *error = NULL;

  int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &db);

  if (baseDatos)
  {
    fprintf(stderr, "No se pudo abrir la base de datos: %s\n", error);
    sqlite3_close(db);
    return 1;
  }

  fprintf(stdout, "La base de datos se ha abierto correctamente\n");
  sqlite3_close(db);
  return 0;
}

int tablaPelicula(sqlite3 *db, char *error)
{

  int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
  char *sql = "CREATE TABLE IF NOT EXISTS Pelicula (id_pel INT PRIMARY KEY NOT NULL, nom_pel TEXT NOT NULL, genero_pel TEXT, dir_pel TEXT NOT NULL, duracion_pel TEXT NOT NULL, precio INT NOT NULL)";
  result = sqlite3_exec(db, sql, 0, 0, &error);

  if (result != SQLITE_OK)
  {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
    sqlite3_free(error);
    return 1;
  }
  else
  {
    fprintf(stdout, "La tabla Pelicula se ha creado correctamente\n");
  }

  sqlite3_close(db);
  return 0;
}

int tablaHorario(sqlite3 *db, char *error)
{

  int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
  char *sql = "CREATE TABLE IF NOT EXISTS Horario (id_horario INT PRIMARY KEY NOT NULL, HoraInicio TEXT NOT NULL, HoraFin TEXT NOT NULL, nom_pel_horario TEXT NOT NULL, fechaHorario TEXT NOT NULL, FOREIGN KEY (nom_pel_horario) REFERENCES Pelicula(nom_pel), FOREIGN KEY (fechaHorario) REFERENCES Fecha(fecha))";
  result = sqlite3_exec(db, sql, 0, 0, &error);

  if (result != SQLITE_OK)
  {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
    sqlite3_free(error);
    return 1;
  }
  else
  {
    fprintf(stdout, "La tabla Horario se ha creado correctamente\n");
  }

  sqlite3_close(db);
  return 0;
}

int tablaFecha(sqlite3 *db, char *error)
{

  int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
  char *sql = "CREATE TABLE IF NOT EXISTS Fecha (fecha TEXT PRIMARY KEY NOT NULL, numPeliculas INT NOT NULL, nom_pel_fecha INT NOT NULL, FOREIGN KEY (nom_pel_fecha) REFERENCES Pelicula(nom_pel))";
  result = sqlite3_exec(db, sql, 0, 0, &error);

  if (result != SQLITE_OK)
  {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
    sqlite3_free(error);
    return 1;
  }
  else
  {
    fprintf(stdout, "La tabla Fecha se ha creado correctamente\n");
  }

  sqlite3_close(db);
  return 0;
}

int tablaUsuario(sqlite3 *db, char *error)
{

  int result = sqlite3_open("baseDeDatosCine.sqlite", &db);
  FILE *f = fopen("DatosUsuarios.txt", "r");

  char *sql2 = "CREATE TABLE IF NOT EXISTS usuario (nombreUsuario TEXT PRIMARY KEY NOT NULL, password TEXT NOT NULL, dni TEXT NOT NULL, correo TEXT NOT NULL, telefono INT NOT NULL)";
  result = sqlite3_exec(db, sql2, 0, 0, &error);

  if (f == NULL)
  {
    fprintf(stderr, "Error al abrir el archivo %s\n", f);
    ferror(f);
  }

  if (result != SQLITE_OK)
  {
    fprintf(stderr, "Error al crear la tabla: %s\n", error);
    sqlite3_free(error);
    sqlite3_close(db);
    return 1;
  }
  else
  {
    fprintf(stdout, "La tabla Usuario se ha creado correctamente\n");
  }

  fclose(f);
  sqlite3_close(db);
  return 0;
}

void agregarUsuario(char *username, char *password, char *dni, char *correo, char *tlf, sqlite3 *db)
{

  FILE *f;
  f = fopen("DatosUsuarios.txt", "a");
  int rc = sqlite3_open("baseDeDatosCine.sqlite", &db);
  sqlite3_stmt *stmt;

  if (f == NULL)
  {
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

  char sql[] = "insert into usuario (nombreUsuario, password, dni, correo, telefono) values (?, ?, ?, ?, ?)";
  int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if (result != SQLITE_OK)
  {
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_bind_text(stmt, 1, username, strlen(username), SQLITE_STATIC);

  if (result != SQLITE_OK)
  {
    printf("Error binding parameters\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);

  if (result != SQLITE_OK)
  {
    printf("Error binding parameters\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_bind_text(stmt, 3, dni, 20, SQLITE_STATIC);

  if (result != SQLITE_OK)
  {
    printf("Error binding parameters\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_bind_text(stmt, 4, correo, 20, SQLITE_STATIC);

  if (result != SQLITE_OK)
  {
    printf("Error binding parameters\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_bind_text(stmt, 5, tlf, 20, SQLITE_STATIC);

  result = sqlite3_step(stmt);
  if (result != SQLITE_DONE)
  {
    printf("Error al insertar los datos\n");
  }

  result = sqlite3_finalize(stmt);
  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  fclose(f);
  sqlite3_close(db);
}

Usuario leeUsuario(char *user, char *password, sqlite3 *db)
{
  Usuario u;
  FILE *f;
  int rc = sqlite3_open("baseDeDatosCine.sqlite", &db);
  f = fopen("DatosUsuarios.txt", "r");
  sqlite3_stmt *stmt;

  if (f == NULL)
  {
    printf("Error al abrir el archivo.\n");
  }
  printf("User:%s, Pass:%s\n", user, password);
  int lectura = fgetc(f);
  char sql[] = ("SELECT * FROM usuario WHERE nombreUsuario = ? AND password = ?");

  int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  result = sqlite3_bind_text(stmt, 1, user, strlen(user), SQLITE_STATIC);
  result = sqlite3_bind_text(stmt, 2, password, strlen(password), SQLITE_STATIC);
  if (result != SQLITE_OK)
  {
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  do
  {
    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW)
    {
      password = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt, 1) + 1)));
      strcpy(password, (char *)sqlite3_column_text(stmt, 1));
      user = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt, 0) + 1)));
      strcpy(user, (char *)sqlite3_column_text(stmt, 0));
    }
  } while (result == SQLITE_ROW);

  while (fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) != EOF)
  {

    if (strcmp(user, u.nombreUsuario) == 0)
    {
      printf("Usuario encontrado\n");
      return u;
    }
  }

  fclose(f);
  result = sqlite3_finalize(stmt);

  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  return u;
}

Usuario login(char *usuario, char *password, char *dni, char *correo, char *tlf, sqlite3 *db)
{

  int usuarioValido = 0;
  Usuario u;


  while (usuarioValido == 0){

  printf("\nIntroduce tu nombre de usuario, si no tienes escribe 'n': ");
  scanf("%s", usuario);

  if (strcmp(usuario, "n") == 0)
  {

    agregarUsuario(usuario, password, dni, correo, tlf, db);
    printf("Usuario registrado, felicidades, ya puedes iniciar sesion con ese usuario\n");
  
  }
  else
  {

    printf("Ingresa tu contraseña: ");
    scanf("%s", password);
  }

  u = leeUsuario(usuario, password, db);
  if (strcmp(usuario, u.nombreUsuario) && strcmp(password, u.contraseyna) != 0)
  {
    printf("Usuario o contraseña incorrectos\n");
  }else{
    usuarioValido = 1;
  }
  }

  printf("Sesion iniciada\n");

  return u;
}

//////////////////////////////////////////// INTENTO DE SELECTS ////////////////////////////////////////////

////////////////////////////////////////// METODO A LO TXINGAS //////////////////////////////////////////
UsuarioDatos usuarioDatos(char *nombreUsuario, sqlite3 *db)
{
  UsuarioDatos ud;

  printf("\n\n///////////Esta visualizando sus datos///////////\n\n");

  int rc1 = sqlite3_open("baseDeDatosCine.sqlite", &db);
  sqlite3_stmt *stmt1;

  const char *sql1 = "SELECT nombreUsuario, dni, correo FROM usuario WHERE nombreUsuario = ?";
  int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL);
  result = sqlite3_bind_text(stmt1, 1, nombreUsuario, strlen(nombreUsuario), SQLITE_STATIC);

  if (result != SQLITE_OK)
  {
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  do{

  result = sqlite3_step(stmt1);

  if (result == SQLITE_ROW)
  {
    ud.nombreUsuario = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt1, 0))+1));
    strcpy(ud.nombreUsuario, (char *)sqlite3_column_text(stmt1, 0));
    ud.dni = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt1, 1))+1));
    strcpy(ud.dni, (char *)sqlite3_column_text(stmt1, 1));
    ud.correo = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt1, 2))+1));
    strcpy(ud.correo, (char *)sqlite3_column_text(stmt1, 2));
  }
    }while (result == SQLITE_ROW);

  if (result == SQLITE_ERROR)
  {
    printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_finalize(stmt1);
  printf(" [Nombre: %s]\n [DNI: %s]\n [Correo: %s]\n\n", ud.nombreUsuario, ud.dni, ud.correo);

  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  return ud;
}

Pelicula verPeliculas(char *nom_pel_fecha, char *fecha, sqlite3 *db)
{
  Pelicula p;

  int rc2 = sqlite3_open("baseDeDatosCine.sqlite", &db);
  sqlite3_stmt *stmt2;
  printf("%s", nom_pel_fecha);

  const char *sql2 = "SELECT idPeliculaFecha FROM fecha WHERE fecha = ?";
  int result = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL);
  //	result = sqlite3_bind_text(stmt2, 1, nom_pel_fecha, strlen(nom_pel_fecha), SQLITE_STATIC);
  result = sqlite3_bind_text(stmt2, 1, fecha, strlen(fecha), SQLITE_STATIC);

  if (result != SQLITE_OK)
  {
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  do
  {
    result = sqlite3_step(stmt2);

    if (result == SQLITE_ROW)
    {
      //			nom_pel_fecha=malloc(sizeof(char)*(strlen( sqlite3_column_text(stmt2, 2)+1)));
      //			strcpy(nom_pel_fecha, (char *) sqlite3_column_text(stmt2, 2));

      fecha = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt2, 0) + 1)));
      strcpy(fecha, (char *)sqlite3_column_text(stmt2, 0));
    }
  } while (result == SQLITE_ROW);

  result = sqlite3_finalize(stmt2);

  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  return p;
}

Horario verHorarios(char *nom_pel_horario, char *HoraInicio, char *HoraFin, sqlite3 *db)
{
  Horario h;

  int rc3 = sqlite3_open("baseDeDatosCine.sqlite", &db);
  sqlite3_stmt *stmt3;
  printf("%s - %s\n", HoraInicio, HoraFin);

  const char sql3[] = "SELECT HoraInicio, HoraFin FROM Horario WHERE nom_pel_horario = ?";
  int result = sqlite3_prepare_v2(db, sql3, -1, &stmt3, NULL);
  result = sqlite3_bind_text(stmt3, 1, nom_pel_horario, strlen(nom_pel_horario), SQLITE_STATIC);
  // result = sqlite3_bind_text(stmt3, 2, HoraInicio, strlen(HoraInicio), SQLITE_STATIC);
  // result = sqlite3_bind_text(stmt3, 3, HoraFin, strlen(HoraFin), SQLITE_STATIC);

  if (result != SQLITE_OK)
  {
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  do
  {
    result = sqlite3_step(stmt3);

    if (result == SQLITE_ROW)
    {
      nom_pel_horario = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt3, 3) + 1)));
      strcpy(nom_pel_horario, (char *)sqlite3_column_text(stmt3, 3));

      // HoraFin=malloc(sizeof(char)*(strlen( sqlite3_column_text(stmt3, 2)+1)));
      // strcpy(HoraFin, (char *) sqlite3_column_text(stmt3, 2));

      // HoraInicio=malloc(sizeof(char)*(strlen( sqlite3_column_text(stmt3, 1)+1)));
      // strcpy(HoraInicio, (char *) sqlite3_column_text(stmt3, 1));
    }
  }

  while (result == SQLITE_ROW);
  result = sqlite3_finalize(stmt3);

  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  return h;
}

////////////////////////////////////////// METODO A LA GAVIRIA //////////////////////////////////////////
/*
int usuariosDatos(sqlite3 *db) {
  sqlite3_stmt *stmt1;
  char sql1[] = "select nombreUsaurio, dni, correo, telefono from usuario";

  int result = sqlite3_prepare_v2(db, sql1, -1, &stmt1, NULL) ;
  if (result != SQLITE_OK) {
    printf("Error preparing statement (SELECT)\n");
    printf("%s\n", sqlite3_errmsg(db));
    return result;
  }

  printf("SQL query prepared (SELECT)\n");
  char nombreUsuario[100];
  char dni[100];
  char correo[100];
  int telefono;
  printf("Showing names:\n");
  do {
    result = sqlite3_step(stmt1) ;
    if (result == SQLITE_ROW) {
      strcpy(nombreUsuario, (char *) sqlite3_column_text(stmt1, 0));
      strcpy(dni, (char *) sqlite3_column_text(stmt1, 2));
      strcpy(correo, (char *) sqlite3_column_text(stmt1, 3));
      telefono = sqlite3_column_int(stmt1, 4);
      printf("[Nombre: %s]\n [DNI: %s]\n [Correo: %s]\n [Telefono: %i]\n", nombreUsuario, dni, correo, telefono);
    }
  } while (result == SQLITE_ROW);

  result = sqlite3_finalize(stmt1);
  if (result != SQLITE_OK) {
    printf("Error finalizing statement (SELECT)\n");
    printf("%s\n", sqlite3_errmsg(db));
    return result;
  }

  printf("Prepared statement finalized (SELECT)\n");
  return SQLITE_OK;
}


int verPeliculas(sqlite3 *db) {
  sqlite3_stmt *stmt2;
  char sql2[] = "select nom_pel_fecha from Fecha";

  int result = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL) ;
  if (result != SQLITE_OK) {
    printf("Error preparing statement (SELECT)\n");
    printf("%s\n", sqlite3_errmsg(db));
    return result;
  }

  printf("SQL query prepared (SELECT)\n");
  char nom_pel_fecha[100];
  printf("Showing names:\n");
  do {
    result = sqlite3_step(stmt2) ;
    if (result == SQLITE_ROW) {
      strcpy(nom_pel_fecha, (char *) sqlite3_column_text(stmt2, 2));
      printf("Pelicula: %d\n", nom_pel_fecha);
    }
  } while (result == SQLITE_ROW);

  result = sqlite3_finalize(stmt2);
  if (result != SQLITE_OK) {
    printf("Error finalizing statement (SELECT)\n");
    printf("%s\n", sqlite3_errmsg(db));
    return result;
  }

  printf("Prepared statement finalized (SELECT)\n");
  return SQLITE_OK;
}


int verHorarios(sqlite3 *db) {
  sqlite3_stmt *stmt3;
  char sql3[] = "select HoraInicio, HoraFin from Horario";

  int result = sqlite3_prepare_v2(db, sql3, -1, &stmt3, NULL) ;
  if (result != SQLITE_OK) {
    printf("Error preparing statement (SELECT)\n");
    printf("%s\n", sqlite3_errmsg(db));
    return result;
  }

  printf("SQL query prepared (SELECT)\n");
  char HoraInicio[100];
  char HoraFin[100];
  printf("Showing names:\n");
  do {
    result = sqlite3_step(stmt3) ;
    if (result == SQLITE_ROW) {
      strcpy(HoraInicio, (char *) sqlite3_column_text(stmt3, 1));
      strcpy(HoraFin, (char *) sqlite3_column_text(stmt3, 2));
      printf("%s - %s\n", HoraInicio, HoraFin);
    }
  } while (result == SQLITE_ROW);

  result = sqlite3_finalize(stmt3);
  if (result != SQLITE_OK) {
    printf("Error finalizing statement (SELECT)\n");
    printf("%s\n", sqlite3_errmsg(db));
    return result;
  }

  printf("Prepared statement finalized (SELECT)\n");
  return SQLITE_OK;
}
*/

///////////////////////////////////////////////// METODO CHATGTP /////////////////////////////////////////////////
/*
int verPeliculas(sqlite3 *db) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *query = "SELECT nom_pel FROM Pelicula";
    char results[MAX_ROWS][MAX_COLS][100]; // Arreglo para almacenar los resultados
    int row_count = 0;

    if (sqlite3_open("baseDeDatosCine.db", &db) != SQLITE_OK) {
        printf("Error opening database\n");
        return 1;
    }

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparing statement\n");
        return 1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && row_count < MAX_ROWS) {
        int column_count = sqlite3_column_count(stmt);
        for (int i = 0; i < column_count && i < MAX_COLS; i++) {
            const unsigned char *value = sqlite3_column_text(stmt, i);
            if (value != NULL) {
                snprintf(results[row_count][i], sizeof(results[row_count][i]), "%s", value);
            } else {
                snprintf(results[row_count][i], sizeof(results[row_count][i]), "%s", "");
            }
        }
        row_count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Imprimir los resultados
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%s\t", results[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int verHorarios(sqlite3 *db) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *query = "SELECT HoraInicio FROM Horario";
    char results[MAX_ROWS][MAX_COLS][100]; // Arreglo para almacenar los resultados
    int row_count = 0;

    if (sqlite3_open("baseDeDatosCine.db", &db) != SQLITE_OK) {
        printf("Error opening database\n");
        return 1;
    }

    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error preparing statement\n");
        return 1;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW && row_count < MAX_ROWS) {
        int column_count = sqlite3_column_count(stmt);
        for (int i = 0; i < column_count && i < MAX_COLS; i++) {
            const unsigned char *value = sqlite3_column_text(stmt, i);
            if (value != NULL) {
                snprintf(results[row_count][i], sizeof(results[row_count][i]), "%s", value);
            } else {
                snprintf(results[row_count][i], sizeof(results[row_count][i]), "%s", "");
            }
        }
        row_count++;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Imprimir los resultados
    for (int i = 0; i < row_count; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%s\t", results[i][j]);
        }
        printf("\n");
    }

    return 0;
}
*/