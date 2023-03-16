#ifndef _CLIENTE_H_
#define _CLIENTE_H_

typedef struct{
		int filaElegida;
		char letraAsientoElegido;
	} AsientoElegido;

void generarSalaA(AsientoElegido *arrayAsientosElegidos);
void elegirAsiento(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas);



#endif