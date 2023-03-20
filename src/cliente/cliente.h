#ifndef _CLIENTE_H_
#define _CLIENTE_H_

typedef struct{
		int filaElegida;
		char letraAsientoElegido;
	} AsientoElegido;

void generarSalaA(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas);
void elegirAsiento(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas);
int confirmacionAsiento(int numEntradasSeleccionadas);
void iniciarSesion();



#endif