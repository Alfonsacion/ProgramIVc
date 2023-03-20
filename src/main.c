#include <stdio.h>
#include <stdlib.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente\cliente.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void main(void)
{
	int opc = 0;
	do{
		system("cls");
		printf("BIENVENIDO A LA SALA DE CINE. ESCOJA UNA OPCIÓN \n\n");
		printf("1. Iniciar sesión como Administrador\n");
		printf("2. Iniciar sesión como Cliente\n");
		printf("3. Salir\n");
		printf("Opcion a escoger: ");
		scanf("%d", &opc);
		switch(opc){
			case 1;
				system("cls");
				printf("Bienvenido Administrador, ¿Qué desea gestionar?\n\n");
				printf("1. Reservas\n"); //Si selecciona 1 tendrá otro menú. 1.Visualizar reservas realizadas y canceladas. 2.Eliminar reservas canceladas.
				printf("2. Películas\n"); //Si selecciona 2 tendrá otro menú. 1.Añadir películas. 2.Eliminar películas
				printf("3. Modificaciones generales\n"); //Si selecciona 3 tendrá otro menú...
				printf("4. Salir\n");
			case 2;
				system("cls");
				printf("¡Bienvenido!\n\n")
				printf("1. Películas\n");
				printf("2. Fechas\n");
				printf("3. Salir");

				
		}
	}while();

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

	Usuario *lista = NULL;
	Usuario usuario;

	if (sqlite3_open(baseDatos, &db) != SQLITE_OK){
		gestionaError(db);
	}

	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo %s\n", f);
		 ferror(f);
	}

	while (!feof(f)){
		fscanf(f, "%s;%d");
	}
	
}
	



  






//testAlonso
//testDelPojo
//testTxingas
//testMarkos
