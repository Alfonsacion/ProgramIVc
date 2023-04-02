#ifndef _CLIENTE_H_
#define _CLIENTE_H_

typedef struct{
		int filaElegida;
		char letraAsientoElegido;
	} AsientoElegido;

void generarSalaA(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas, int numEntradas);
void elegirAsiento(AsientoElegido *arrayAsientosElegidos, int numEntradasSeleccionadas);
int confirmacionAsiento(int numEntradasSeleccionadas);
int pantallaCartelera(const char **arrayPeliculas, int numPeliculas);
int seleccionHorarios(int seleccionPelicula, const char **arrayHorarios, const char **arrayPeliculas);
int confirmacionTicket(int seleccionPelicula, const char **arrayPeliculas, const char **arrayHorarios, int seleccionHorario);
void confirmacionDefinitiva(int seleccionPelicula, const char **arrayPeliculas, int seleccionHorario, const char **arrayHorarios, int numEntradas); //AsientoElegido **arrayAsientosElegidos, int numEntradasSeleccionadas
void exportarDatos(int numEntradasSeleccionadas, int seleccionPelicula, const char **arrayPeliculas);
void datosUsuario (char usuario[100], char dni[100], char correo[100], char telefono[100]);
void datosPeliculas(const char **arrayPeliculas, int numPeliculas);



#endif