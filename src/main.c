#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente/cliente.h"
#include "../db/connect/connect.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20




int main(void)
{


	sqlite3 *db;
	char *error;
	////////////////////////////////////////////////BASE DE DATOS//////////////////////////////////////////////////////
	int baseDedatos = openDB(db);
	int pelicula = tablaPelicula(db, error);
	int horario = tablaHorario(db, error);
	int fecha = tablaFecha(db, error);
	int usuarioTest = tablaUsuario(db, error);

	char nombreUsuario[MAX_PASSWORD_LENGTH];
	char contraseyna[MAX_PASSWORD_LENGTH];
	char dniUsuario[MAX_PASSWORD_LENGTH];
	char correoUsuario[MAX_PASSWORD_LENGTH];
	char tlf[MAX_PASSWORD_LENGTH];

	char nom_pel_fecha[MAX_PASSWORD_LENGTH];
	char fecha_peli[MAX_PASSWORD_LENGTH];
	char nom_pel_horario[MAX_PASSWORD_LENGTH];
	char HoraInicio[MAX_PASSWORD_LENGTH];
	char HoraFin[MAX_PASSWORD_LENGTH];

	char *a = malloc((strlen(nombreUsuario) + 1) * sizeof(char));
	a = strcpy(a, nombreUsuario);
	a[strlen(a)] = '\0';


	printf("\n");
	printf("Bienvenido/a, ahora puedes iniciar sesion\n");
	printf("\n");

	Usuario u = login(a, contraseyna, dniUsuario, correoUsuario, tlf, db);

	free(a);

	///////////////////////////////////////
	int seleccionPelicula = 0;
	int seleccionHorario = 0;
	int numEntradas = 0;
	int numEntradasSeleccionadas = 0;
	int numPeliculas = 0;
	const char *arrayPeliculas[6];
	const char *arrayHorarios[4];




	AsientoElegido *arrayAsientosElegidos;



	int opcion = 1;
	Pelicula p;
	UsuarioDatos ud;
	Horario h;
	Seleccion s;

		while (opcion <= 5 && opcion >= 0)
		{
			printf("\n\n///////////Menu Cineplex///////////\n\n");

			printf("1. Visualizar datos del usuario\n\n");
			printf("2. Efectuar una reserva \n\n");
			printf("3. Visualizar las peliculas disponibles \n\n");
			printf("4. Cerrar sesion\n\n");

			printf("Seleccione la opcion que desee: \n");
			scanf("%1d", &opcion);
			switch (opcion)

			{

			case 1:
				
				ud = usuarioDatos(u.nombreUsuario, db);

				printf("\n\nPresiona cualquier tecla y enter para volver al menu: ");
				scanf("%1d", &opcion);
				fflush(stdin);
				break;


			case 2:
				printf("\n\n///////////Bienvenido al gestor de reservas///////////\n\n");

				seleccionPelicula = pantallaCartelera(arrayPeliculas, numPeliculas, db);
				seleccionHorario = seleccionHorarios(seleccionPelicula, s.dia, arrayHorarios, arrayPeliculas);
				numEntradas = confirmacionTicket(seleccionPelicula, arrayPeliculas, arrayHorarios, seleccionHorario);
				arrayAsientosElegidos = malloc(numEntradas * sizeof(AsientoElegido));

				generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas, numEntradas);

				for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++)
				{
					elegirAsiento(arrayAsientosElegidos, numEntradasSeleccionadas);
					generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas, numEntradas);
					numEntradasSeleccionadas = confirmacionAsiento(numEntradasSeleccionadas);
				}

				exportarDatos(numEntradasSeleccionadas, seleccionPelicula, arrayPeliculas);
				// confirmacionDefinitiva(seleccionPelicula, arrayPeliculas, seleccionHorario, arrayHorarios, numEntradas, arrayAsientosElegidos, numEntradasSeleccionadas);

				printf("\n\nPresiona cualquier tecla y enter para volver al menu: ");
				scanf("%1d", &opcion);
				fflush(stdin);
				break;

			case 3:

				p = verPeliculas(db);
				printf("\n\nPresiona cualquier tecla y enter para volver al menu: ");
				scanf("%d", &opcion);
				fflush(stdin);
				break;

			case 4:
				printf("\n\n///////////Has cerrado sesion, hasta pronto!///////////\n\n");

				opcion = 6;
				break;
				
			default:

				printf("\n\n///////////La opcion seleccionada no es valida///////////\n\n");
				fflush(stdin);
				break;

			}
		}
		return 0;
}
