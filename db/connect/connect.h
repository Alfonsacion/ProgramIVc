#ifndef _CONNECT_H_
#define _CONNECT_H_
#include "../../struct.h"

    void agregarUsuario(char* username, char* password, char *dni, char *correo, char *tlf, sqlite3* db);
    Usuario leeUsuario(char* user, char* password, sqlite3* db);
    Usuario login(char *usuario, char *password, char *dni, char *correo, char *tlf, sqlite3* db); 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// METODO A LO TXINGAS //////////////////////////////////////////
    UsuarioDatos usuarioDatos(char *nombreUsuario,  sqlite3* db);
    // UsuarioDatos* usuarioDatos(char *nombreUsuario, char *dni, char *correo, sqlite3* db);
    Pelicula verPeliculas(sqlite3* db);
    Horario verHorarios(char *nom_pel_horario, sqlite3* db);

////////////////////////////////////////// METODO A LA GAVIRIA //////////////////////////////////////////
//    int usuarioDatos (sqlite3* db);
//    int verPeliculas (sqlite3* db);
//    int verHorarios (sqlite3* db);

///////////////////////////////////////////////// METODO CHATGTP /////////////////////////////////////////////////
//	  int verPeliculas(db);
//	  int verHorarios(db);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    int tablaPelicula(sqlite3* db, char* error);
    int tablaHorario(sqlite3* db, char* error);
    int tablaFecha(sqlite3* db, char* error);
    int tablaUsuario(sqlite3* db, char* error);
    int openDB(sqlite3 *db);

#endif