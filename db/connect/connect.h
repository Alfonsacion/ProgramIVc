#ifndef _CONNECT_H_
#define _CONNECT_H_
#include "../../struct.h"

    void agregarUsuario(char* username, char* password, char *dni, char *correo, char *tlf, sqlite3* db);
    Usuario leeUsuario(char* user, char* password, sqlite3* db);
    Usuario login(char *usuario, char *password, char *dni, char *correo, char *tlf, sqlite3* db); 
    UsuarioDatos verListausuarios(sqlite3* db);
    char* verPeliculas(sqlite3* db);
    Pelicula verPeliculasCliente(sqlite3* db);
    Pelicula obtenerPeliculaPorId(int id, sqlite3 * db);
    Pelicula obtenerPrecioPorId(int id, sqlite3 *db);
    Horario obtenerHorarioPorId(int id, sqlite3 *db);
    Horario verHorarios(char *nom_pel_horario, sqlite3* db);   
    UsuarioDatos usuarioDatos(char *nombreUsuario,  sqlite3* db);
    void eliminarUsuario(char* username, sqlite3* db);
    int tablaPelicula(sqlite3* db, char* error);
    int tablaHorario(sqlite3* db, char* error);
    int tablaFecha(sqlite3* db, char* error);
    int tablaUsuario(sqlite3* db, char* error);
    int openDB(sqlite3 *db);

#endif