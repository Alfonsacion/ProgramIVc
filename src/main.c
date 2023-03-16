#include <stdio.h>
#include <stdlib.h>

#include "cliente\cliente.h"

void main(void)
{

	typedef struct{
		int filaElegida;
		char letraAsientoElegido;
	} AsientoElegido;

	AsientoElegido *arrayAsientosElegidos;
	arrayAsientosElegidos = malloc(5*sizeof(AsientoElegido));
	arrayAsientosElegidos[1].filaElegida = 1;
    arrayAsientosElegidos[1].letraAsientoElegido = 'A';

	printf("El valor del array es %d%c", arrayAsientosElegidos[1].filaElegida, arrayAsientosElegidos[1].letraAsientoElegido);

	int *filaElegida;
	filaElegida=malloc(sizeof(int));
	*filaElegida = 1;

    char *letraAsientoElegido;
	letraAsientoElegido=malloc(sizeof(char));
	*letraAsientoElegido ='A';

	printf("\n      \n");
	printf("\n    valor desde el main es:    %d       \n", arrayAsientosElegidos[1].filaElegida);
	printf("\n    letra desde el main es:    %c     \n", arrayAsientosElegidos[1].letraAsientoElegido);
	printf("\n      \n");
	

	generarSalaA(filaElegida, letraAsientoElegido);
	elegirAsiento(filaElegida, letraAsientoElegido);
	generarSalaA(filaElegida, letraAsientoElegido);



  


}



//testAlonso
//testDelPojo
//testTxingas
//testMarkos
