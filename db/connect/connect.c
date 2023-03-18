#include "../../sqlite3.h"
#include "connect.h"
#include <stdio.h>
#include "../../struct.h"
#include <string.h>

int gestionaError (sqlite3 *db){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}

void agregarUsuario(char *username, char *password){
      FILE* f;
      f = fopen("DatosUsuarios.txt", "a");
      sqlite3 *db;
      sqlite3_stmt *stmt;
      int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &baseDatos);

       if (f == NULL) {
    printf("Error al abrir el fichero\n");
    exit(1);
  }

  fprintf(f, "%s %s\n", username, password);

  baseDatos = sqlite3_prepare_v2(db, "INSERT INTO usuario (nombreUsuario, password) VALUES (?, ?)", -1, &stmt, NULL);

  fclose(f);
  sqlite3_close(db);

}
    
//Usuario *nuevoUsuario(Usuario usuario){
//    Usuario* u = (Usuario*)malloc(sizeof(Usuario));
//   strcpy(u->nombreUsuario, usuario.nombreUsuario);
//}

Usuario leeUsuario(char *usuario){
    Usuario u;
    FILE* f;
    f = fopen("DatosUsuarios.txt", "r");
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int baseDatos = sqlite3_open("baseDeDatosCine.sqlite", &baseDatos);

    if (f == NULL) {
    printf("Error al abrir el archivo.\n");
    exit(1);
    }

    baseDatos = sqlite3_prepare_v2(db, "SELECT * FROM usuario WHERE nombreUsuario = ?", -1, &stmt, NULL);

    while (fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) == 2) {
    if (strcmp(usuario, u.nombreUsuario) == 0 && strcmp(usuario, baseDatos) == 0) { //No estoy nada seguro de la segunda paerte del if
      fclose(f);
      sqlite3_close(db);
      return u;
    }
  }

  fclose(f);
  strcpy(u.nombreUsuario, "");
  strcpy(u.contraseyna, "");
  return u;
}

// void iniciarSesion(char *usuario, char *password){
//  printf("Introduce tu nombre de usuario: ");
// scanf("%s", usuario);
//  printf("Ingresa tu contraseña: ");
//  scanf("%s", password);
// }


