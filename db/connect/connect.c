#include "sqlite3.h"
#include "connect.h"
#include <stdio.h>

int gestionaError (sqlite3 *db){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}

