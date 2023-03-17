#include "../../sqlite3.h"
#include "connect.h"
#include <stdio.h>
#include "../../struct.h"

int gestionaError (sqlite3 *db){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}

void agregarUsuario(Usuario *lista, const Usuario *usuario){
  Usuario *x = lista;
    while (x->siguiente != NULL){
        x = x->siguiente;
    }
}

