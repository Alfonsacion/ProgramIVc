#include <sqlite3.h>
#include <sqlite3.c>

void main (void) {
    sqlite3 *db;
    int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &baseDatos);

    if (baseDatos) {
        fprintf(stderr, "No se pusdo abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    } else {
        fprintf(stdout, "La base de datos se ha abierto correctamente\n");
    }

    //creacion de tablas para la base de datos: acordar cuales todavia
    char *sql = "CREATE TABLE pelicula (id_pel INT PRIMARY KEY NOT NULL, nom_pel TEXT NOT NULL, duracion INT NOT NULL)";

    baseDatos = sqlite3_exec(db, sql, NULL, 0, &errmsg);

    if (baseDatos != SQLITE_OK) {
        fprintf(stderr, "Error en la creacion de la tabla: %s\n", errmsg);
        sqlite3_free(errmsg);
    } else {
        fprintf(stdout, "La tabla se ha creado correctamente\n");
    }

    sqlite3_close(db);
}
