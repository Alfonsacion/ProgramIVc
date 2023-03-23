#include "../../sqlite3.h"
#include "connect.h"
#include <stdio.h>
#include "../../struct.h"
#include <string.h>
#include <stdlib.h>

int gestionaError (sqlite3 *db){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    return sqlite3_errcode(db);
}

void agregarUsuario(char *username, char *password, sqlite3* db){
      FILE* f;
      f = fopen("DatosUsuarios.txt", "a");
      sqlite3_stmt *stmt;
      char *sql;

       if (f == NULL) {
    printf("Error al abrir el fichero\n");
  }

  fprintf(f, "%s %s\n", username, password);

  sql = sqlite3_mprintf("INSERT INTO usuarios (nombre, contrasena) VALUES ('%q', %d)", username, password);
  int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if(result != SQLITE_OK){
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

   result = sqlite3_finalize(stmt);

  if(result != SQLITE_OK){
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  fclose(f);
  sqlite3_close(db);

}
    
//Usuario *nuevoUsuario(Usuario usuario){
//    Usuario* u = (Usuario*)malloc(sizeof(Usuario));
//   strcpy(u->nombreUsuario, usuario.nombreUsuario);
//}

Usuario leeUsuario(char* user, sqlite3* db){
    Usuario u;
    FILE* f;
    f = fopen("DatosUsuarios.txt", "r");
    sqlite3_stmt* stmt;
    char* sql;

    if (f == NULL) {
    printf("Error al abrir el archivo.\n");
    }

   sql = sqlite3_mprintf("SELECT * FROM usuarios WHERE nombre = '%s'", user);
   int result = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

  if(result != SQLITE_OK){
    printf("Error al preparar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }
   

    int count = 0;

    do{
       if (fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) == 2 && result == SQLITE_ROW) {
         count++;
       if (strcmp(user, u.nombreUsuario) == 0 && count > 0) { 
         printf("Usuario encontrado\n");
         fclose(f);
         sqlite3_close(db);
         return u;
      } else {
         printf("Usuario no encontrado\n");
      }
    }
   } while(fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) == 2 && result == SQLITE_ROW);

  fclose(f);
  result = sqlite3_finalize(stmt);

  if(result != SQLITE_OK){
    printf("Error al cerrar la consulta\n");
    printf("%s\n", sqlite3_errmsg(db));
  }

  strcpy(u.nombreUsuario, "");
  strcpy(u.contraseyna, "");
  return u;
}

 void iniciarSesion(char *usuario, char *password){
  printf("Introduce tu nombre de usuario: ");
 scanf("%s", usuario);
  printf("Ingresa tu contraseña: ");
  scanf("%s", password);
 }


