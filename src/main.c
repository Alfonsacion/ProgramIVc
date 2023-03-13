#include <stdio.h>
#include <stdlib.h>

#include "cliente/cliente.h"

void main(void)
{

	int *filaElegida;
    char *letraAsientoElegido;

	elegirAsiento(filaElegida, letraAsientoElegido);

	printf("\n    desde el main es:    %d       \n", &filaElegida);
	printf("\n    desde el main es:    %d       \n", filaElegida);

	
	//printf("\n    desde el main es:    %d       \n", *filaElegida);
	

	generarSalaA(filaElegida, letraAsientoElegido);
	elegirAsiento(filaElegida, letraAsientoElegido);


  


}



//testAlonso
//testDelPojo
//testTxingas
//testMarkos
