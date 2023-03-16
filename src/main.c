#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

#include "cliente\cliente.h"

void main(void)
{
	int numEntradas = 3;
	int numEntradasSeleccionadas = 0;	

	AsientoElegido *arrayAsientosElegidos;
	arrayAsientosElegidos = malloc(numEntradas*sizeof(AsientoElegido));

	generarSalaA(arrayAsientosElegidos);

	for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++)
	{
		elegirAsiento(arrayAsientosElegidos,numEntradasSeleccionadas);
		generarSalaA(arrayAsientosElegidos);

		int loop;

   			for(loop = 0; loop < numEntradasSeleccionadas+1; loop++){

     		 printf(" ARRAY %d ", arrayAsientosElegidos[loop].filaElegida);
			 printf("ARRAY %c ", arrayAsientosElegidos[loop].letraAsientoElegido);

			 }
		}

	sqlite3 *db = NULL;
	const char *filename = ;//Ruta de la bd cuando la hagamos 

	if (sqlite3_open(filename, &db) != SQLITE_OK){
		return gestionaError(db);
	}
		
}
	



  






//testAlonso
//testDelPojo
//testTxingas
//testMarkos
