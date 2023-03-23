#define _CONNECT_H_
#ifndef _CONNECT_H_
#include "../../struct.h"

    int gestionaError (sqlite3* db);
    void agregarUsuario(char* username, char* password, sqlite3* db);
 //   Usuario *nuevoUsuario(Usuario &usuario);
    Usuario leeUsuario(char* user, sqlite3* db);
    void iniciarSesion(char *usuario, char *password); 
#endif