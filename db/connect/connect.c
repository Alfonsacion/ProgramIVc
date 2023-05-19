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

void agregarUsuario(char *username, char *password, char *dni, char *correo, char* tlf, sqlite3 *db)
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

Usuario login(char *usuario, char *password, char *dni, char *correo, char* tlf, sqlite3 *db)
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

  const char *sql1 = "SELECT nombreUsuario, dni, correo, telefono FROM usuario WHERE nombreUsuario = ?";
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
    ud.tlf = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt1, 3))+1));
    strcpy(ud.tlf, (char *)sqlite3_column_text(stmt1, 3));
  }
    }while (result == SQLITE_ROW);

  if (result == SQLITE_ERROR)
  {
    printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_finalize(stmt1);
  printf(" [Nombre: %s]\n [DNI: %s]\n [Correo: %s]\n [Telefono: %s]\n\n", ud.nombreUsuario, ud.dni, ud.correo, ud.tlf);

  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  return ud;
}

Pelicula verPeliculas(sqlite3 *db)
{
  Pelicula p;

  int rc2 = sqlite3_open("baseDeDatosCine.sqlite", &db);
  sqlite3_stmt *stmt2;

  const char *sql2 = "SELECT id_pel, nom_pel, genero_pel, duracion_pel FROM pelicula";
  int result = sqlite3_prepare_v2(db, sql2, -1, &stmt2, NULL);

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

    p.id = sqlite3_column_int(stmt2, 0); 
    p.nom_pel = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt2, 1))+1));
    strcpy(p.nom_pel, (char *)sqlite3_column_text(stmt2, 1));

    p.genero_pel = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt2, 2))+1));
    strcpy(p.genero_pel, (char *)sqlite3_column_text(stmt2, 2));

    p.duracion = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt2, 3))+1));
    strcpy(p.duracion, (char *)sqlite3_column_text(stmt2, 3));
    printf(" %d [Pelicula: %s] [Genero: %s] [Duracion: %s]\n", p.id, p.nom_pel, p.genero_pel, p.duracion);
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

Pelicula obtenerPeliculaPorId(int id, sqlite3 *db)
{
  Pelicula p;
  sqlite3_stmt *stmt;
  const char *sql = "SELECT nom_pel, genero_pel, duracion_pel FROM pelicula WHERE id_pel = ?";
  
  int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, id);

  if (result != SQLITE_OK)
  {
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
    return p;
  }

  result = sqlite3_step(stmt);

  if (result == SQLITE_ROW)
  {
    p.id = id;

    if(p.nom_pel != NULL){
      free(p.nom_pel);
      p.nom_pel = NULL;
    }
    p.nom_pel = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt, 0)) + 1));
    strcpy(p.nom_pel, (char *)sqlite3_column_text(stmt, 0));

    if(p.genero_pel != NULL){
      free(p.genero_pel);
      p.genero_pel = NULL;
    }
    p.genero_pel = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt, 1)) + 1));
    strcpy(p.genero_pel, (char *)sqlite3_column_text(stmt, 1));

    if(p.duracion != NULL){
      free(p.duracion);
      p.duracion = NULL;
    }
    p.duracion = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt, 2)) + 1));
    strcpy(p.duracion, (char *)sqlite3_column_text(stmt, 2));
  }

  result = sqlite3_finalize(stmt);

  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  return p;
}


Horario verHorarios(char *nom_pel_horario, sqlite3 *db)
{
  Horario h;

  int rc3 = sqlite3_open("baseDeDatosCine.sqlite", &db);
  sqlite3_stmt *stmt3;

  const char *sql3 = "SELECT id_horario, HoraInicio, HoraFin, nom_pel_horario FROM Horario WHERE nom_pel_horario = ?";
  int result = sqlite3_prepare_v2(db, sql3, -1, &stmt3, NULL);
  result = sqlite3_bind_text(stmt3, 1, nom_pel_horario, strlen(nom_pel_horario), SQLITE_STATIC);

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

      h.id = sqlite3_column_int(stmt3, 0);

      h.nom_pel_horario = malloc(sizeof(char) * (strlen(sqlite3_column_text(stmt3, 3))+1));
      strcpy(h.nom_pel_horario, (char *)sqlite3_column_text(stmt3, 3));

      h.HoraFin=malloc(sizeof(char)*(strlen( sqlite3_column_text(stmt3, 2))+1));
      strcpy(h.HoraFin, (char *) sqlite3_column_text(stmt3, 2));

      h.HoraInicio=malloc(sizeof(char)*(strlen( sqlite3_column_text(stmt3, 1))+1));
      strcpy(h.HoraInicio, (char *) sqlite3_column_text(stmt3, 1));

      printf("%d [Hora de inicio: %s]\n [Hora de finalizacion: %s]\n\n", h.id, h.HoraInicio, h.HoraFin);
    }
  }

  while (result == SQLITE_ROW);

  if (result == SQLITE_ERROR)
  {
    printf("Error al ejecutar la consulta: %s\n", sqlite3_errmsg(db));
  }

  result = sqlite3_finalize(stmt3);


  if (result != SQLITE_OK)
  {
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  sqlite3_close(db);
  return h;
}

