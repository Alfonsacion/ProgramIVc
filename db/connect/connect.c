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

       if (f == NULL) {
    printf("Error al abrir el fichero\n");
    exit(1);
  }

  fprintf(f, "%s %s\n", username, password);

  fclose(f);
}
    
Usuario *nuevoUsuario(Usuario usuario){
    Usuario* u = (Usuario*)malloc(sizeof(Usuario));
    strcpy(u->nombreUsuario, usuario.nombreUsuario);
}

Usuario leeUsuario(char *usuario){
    Usuario u;
    FILE* f;
    f = fopen("DatosUsuarios.txt", "r");

    if (f == NULL) {
    printf("Error al abrir el archivo.\n");
    exit(1);
    }

    while (fscanf(f, "%s %s", u.nombreUsuario, u.contraseyna) == 2) {
    if (strcmp(usuario, u.nombreUsuario) == 0) {
      fclose(f);
      return u;
    }
  }

  fclose(f);
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


