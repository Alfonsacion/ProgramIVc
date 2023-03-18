#define _CONNECT_H_
#ifndef _CONNECT_H_
#include "../../struct.h"

    int gestionaError (sqlite3 *db);
    void agregarUsuario(char *username, char *password);
 //   Usuario *nuevoUsuario(Usuario &usuario);
    Usuario leeUsuario(char *usuario);
//    void iniciarSesion(char *usuario, char *password); 
#endif