#ifndef _CONNECT_H_
#define _CONNECT_H_
#include "../../struct.h"

    void agregarUsuario(char* username, char* password, sqlite3* db);
    Usuario leeUsuario(char* user, char* password, sqlite3* db);
    Usuario login(char *usuario, char *password, sqlite3* db); 
    int tablaPelicula(sqlite3* db, char* error);
    int tablaHorario(sqlite3* db, char* error);
    int tablaFecha(sqlite3* db, char* error);
    int tablaUsuario(sqlite3* db, char* error);
    int openDB(sqlite3 *db);

#endif