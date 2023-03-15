#include <stdio.h>
#include <stdlib.h>

#include "cliente\cliente.h"

void main(void)
{
	int *filaElegida;
	filaElegida=malloc(sizeof(int));
	*filaElegida = 1;

    char *letraAsientoElegido;
	letraAsientoElegido=malloc(sizeof(char));
	*letraAsientoElegido ='A';

	printf("\n      \n");
	printf("\n    valor desde el main es:    %d       \n", *filaElegida);
	printf("\n    letra desde el main es:    %c     \n", *letraAsientoElegido);
	printf("\n      \n");
	

	generarSalaA(filaElegida, letraAsientoElegido);
	elegirAsiento(filaElegida, letraAsientoElegido);
	generarSalaA(filaElegida, letraAsientoElegido);



  


}



//testAlonso
//testDelPojo
//testTxingas
//testMarkos
