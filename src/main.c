#include <stdio.h>
#include <stdlib.h>

#include "cliente\cliente.h"

void main(void)
{

	AsientoElegido *arrayAsientosElegidos;
	arrayAsientosElegidos = malloc(5*sizeof(AsientoElegido));
	arrayAsientosElegidos[0].filaElegida = 3;
    arrayAsientosElegidos[0].letraAsientoElegido = 'C';

	printf("El valor del array es %d%c", arrayAsientosElegidos[1].filaElegida, arrayAsientosElegidos[1].letraAsientoElegido);

	printf("\n      \n");
	printf("\n    valor desde el main es:    %d       \n", arrayAsientosElegidos[1].filaElegida);
	printf("\n    letra desde el main es:    %c     \n", arrayAsientosElegidos[1].letraAsientoElegido);
	printf("\n      \n");
	

	generarSalaA(arrayAsientosElegidos);
	elegirAsiento(arrayAsientosElegidos);
	generarSalaA(arrayAsientosElegidos);



  


}



//testAlonso
//testDelPojo
//testTxingas
//testMarkos
