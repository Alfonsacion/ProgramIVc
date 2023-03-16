#define _CONNECT_H_
#ifndef _CONNECT_H_
#include "struct.h"

    int gestionaError (sqlite3 *db);
    void agregarUsuario(Usuario *lista, const Usuario *usuario);

#endif