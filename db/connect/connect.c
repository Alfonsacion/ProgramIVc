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

  char *sql = sqlite3_mprintf("INSERT INTO usuarios (nombre, contrasena) VALUES ('%d', '%u');", username, password);

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

   char *sql = "SELECT * FROM usuarios WHERE nombre = '%d'", usuario;

    int count = 0;
    while (fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) == 2 && sqlite3_step(stmt) == SQLITE_ROW) {
      count++;
    if (strcmp(usuario, u.nombreUsuario) == 0 && count > 0) { 
      printf("Usuario encontrado\n");
      fclose(f);
      sqlite3_close(db);
      return u;
    } else {
    printf("Usuario no encontrado\n");
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


