#include <stdio.h>
#include <stdlib.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente\cliente.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void main(void)
{
	char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];

	printf("Nombre de usuario: ");
  	scanf("%s", nombreUsuario);
 	printf("Contrasena: ");
  	scanf("%s", contraseyna);

	Usuario u = leeUsuario(nombreUsuario); //CREO QUE EL ERROR ES POR COMO ESTÁ DEFINIDA LA ESTRUCTURA PERO NO LO ENTIENDO
	 if (strcmp(u.nombreUsuario, "") == 0) {
    agregaUsuario(nombreUsuario, contraseyna);
    printf("Usuario registrado\n");
	 } else {
    if (strcmp(contraseyna, u.contraseyna) == 0) {
      printf("Sesion iniciada\n");
    } else {
      printf("Contraseña incorrecta\n");
    }
  }

	int numEntradas = 3;
	int numEntradasSeleccionadas = 0;	

	AsientoElegido *arrayAsientosElegidos;
	arrayAsientosElegidos = malloc(numEntradas*sizeof(AsientoElegido));

	generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);

	for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++)
	{
		elegirAsiento(arrayAsientosElegidos,numEntradasSeleccionadas);
		generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas);

		int loop;

   			for(loop = 0; loop < numEntradasSeleccionadas+1; loop++){

     		 printf(" ARRAY %d ", arrayAsientosElegidos[loop].filaElegida);
			 printf("ARRAY %c ", arrayAsientosElegidos[loop].letraAsientoElegido);

			 }
		}

	sqlite3 *db = NULL;
	const char *filename = ""; //Ruta de la bd cuando la hagamos 
	Usuario *lista = NULL;
	FILE *f = fopen("DatosUsuarios.txt", "r");
	Usuario usuario;

	if (sqlite3_open(filename, &db) != SQLITE_OK){
		return gestionaError(db);
	}

	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo %s\n", f);
		//return ferror;
	}

	while (!feof(f)){
		fscanf(f, "%s;%d");
	}
	
}
	



  






//testAlonso
//testDelPojo
//testTxingas
//testMarkos
