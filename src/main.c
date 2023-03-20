#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "struct.h"
#include "cliente\cliente.h"

void main(void)
{
	int opc = 0;
	do{
		system("cls");
		printf("BIENVENIDO A LA SALA DE CINE. ESCOJA UNA OPCIÓN \n\n")
		printf("1. Iniciar sesión como Administrador\n");
		printf("2. Iniciar sesión como Cliente\n");
		printf("3. Salir\n\n");
		printf("Opcion a escoger: ");
		scanf("%d", &opc);
		switch(opc){
			case 1;
				system("cls");
				
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

	sqlite3 *db = NULL;
//	const char *filename = ; //Ruta de la bd cuando la hagamos 
//	Usuario *lista = NULL;
	FILE *f = fopen("DatosUsuarios.txt", "r");
//	Usuario usuario;

//	if (sqlite3_open(filename, &db) != SQLITE_OK){
//		return gestionaError(db);
//	}

	if(f == NULL){
		fprintf(stderr, "Error al abrir el archivo %s\n", f);
		return ferror;
	}

	while (!feof(f)){
		fscanf(f, "%s;%d");
	}


		
}
	



  






//testAlonso
//testDelPojo
//testTxingas
//testMarkos
