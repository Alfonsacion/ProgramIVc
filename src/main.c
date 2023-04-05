#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente/cliente.h"
#include "../db/connect/connect.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

void main(void)
{
	sqlite3 *db;
	char* error;
////////////////////////////////////////////////BASE DE DATOS//////////////////////////////////////////////////////
	int baseDedatos = openDB(db);
    int pelicula = tablaPelicula(db, error);
    int horario = tablaHorario(db, error);
    int fecha = tablaFecha(db, error);
    int usuarioTest = tablaUsuario(db, error);
	
	char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];
	char dniUsuario[MAX_PASSWORD_LENGTH];
	char correoUsuario[MAX_PASSWORD_LENGTH];
	char tlf[MAX_PASSWORD_LENGTH];

	char nom_pel_fecha[MAX_PASSWORD_LENGTH];
    char nom_pel_horario[MAX_PASSWORD_LENGTH];
	char HoraInicio[MAX_PASSWORD_LENGTH];
	char HoraFin[MAX_PASSWORD_LENGTH];

	char* a = malloc((strlen(nombreUsuario)+1)*sizeof(char));
	a = strcpy(a,nombreUsuario);
	a[strlen(a)]='\0';

	printf("\n");
	printf("Bienvenido/a, ahora puedes iniciar sesion\n");
	printf("\n");

	Usuario	u = login(a, contraseyna, dniUsuario, correoUsuario, tlf, db);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////// METODO A LO TXINGAS //////////////////////////////////////////
//	usuarioDatos ud = usuarioDatos(nombreUsuario, dniUsuario, correoUsuario, tlf, db);
//	Pelicula p = verPeliculas(nom_pel_fecha, fecha, db);
//	Horario h = verHorarios(nom_pel_horario, HoraInicio, HoraFin, db);

////////////////////////////////////////// METODO A LA GAVIRIA //////////////////////////////////////////
//	usuarioDatos(db);
//	verPeliculas(db);
//	verHorarios(db);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


  free(a);

//////////////////////PARTE ALONSO, SELECCION DE ASIENTOS
	//////////VARIABLES DESDE BD////////////
	
	int numPeliculas = 5;
	char usuario[100] = "Iker";
	char dni[100] = "75485943L.";
	char correo[100] = "iker@gmail.com";
	char telefono[100] = "758 748 372";



	///////////////////////////////////////
	int seleccionPelicula = 0;
	int seleccionHorario = 0;
	int numEntradas = 0;
	int numEntradasSeleccionadas = 0;

	AsientoElegido *arrayAsientosElegidos;

	const char *arrayPeliculas[6];
	arrayPeliculas[1] = "Gato con botas";
	arrayPeliculas[2] = "Vengadores";
	arrayPeliculas[3] = "Narnia";
	arrayPeliculas[4] = "Star Wars";
	arrayPeliculas[5] = "Avatar";

	const char *arrayHorarios[4];
	arrayHorarios[1] = "17:00";
	arrayHorarios[2] = "16:00";
	arrayHorarios[3] = "18:00";




    int opcion =1 ;

	

	void menu(){

	
	while (opcion <= 5 && opcion >= 0){ 

			printf("\n\n///////////Menu Cineplex///////////\n\n");

            printf("1. Visualizar datos del usuario\n\n");
            printf("2. Efectuar una reserva \n\n");
            printf("3. Visualizar las peliculas disponibles \n\n");
            printf("4. Cerrar sesion\n\n");

            printf("Seleccione la opcion que desee: \n");
            scanf("%1d", &opcion);
            switch(opcion){

                case 1:

					datosUsuario ( usuario,  dni,  correo,  telefono);
					
					printf("\n\nPresiona cualquier tecla y enter para volver al menu: ");
					scanf("%1d", &opcion);
                    fflush(stdin);  
					menu();
                    //LLamar al menu de nuevo??¿¿¿¿??

                case 2:
                    printf("\n\n///////////Bienvenido al gestor de reservas///////////\n\n");

						seleccionPelicula = pantallaCartelera(arrayPeliculas, numPeliculas);
						seleccionHorario = seleccionHorarios(seleccionPelicula, arrayHorarios, arrayPeliculas);
						numEntradas = confirmacionTicket(seleccionPelicula, arrayPeliculas,arrayHorarios, seleccionHorario);
						arrayAsientosElegidos = malloc(numEntradas*sizeof(AsientoElegido));


						generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas, numEntradas);

						for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++){
							elegirAsiento(arrayAsientosElegidos,numEntradasSeleccionadas);
							generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas, numEntradas);
    						numEntradasSeleccionadas = confirmacionAsiento(numEntradasSeleccionadas);
						}

						exportarDatos(numEntradasSeleccionadas, seleccionPelicula, arrayPeliculas);


					printf("\n\nPresiona cualquier tecla y enter para volver al menu: ");
					scanf("%1d", &opcion);
                    fflush(stdin);
                  
				  	menu();
                    
                case 3:

					datosPeliculas(arrayPeliculas, numPeliculas);

					printf("\n\nPresiona cualquier tecla y enter para volver al menu: ");
					scanf("%1d", &opcion);
                    fflush(stdin); 					
                
                    menu();

                case 4:
				    printf("\n\n///////////Has cerrado sesion, hasta pronto!///////////\n\n");

					opcion =6 ;

                    menu();

                default:

                    printf("\n\n///////////La opcion seleccionada no es valida///////////\n\n");
                    fflush(stdin);  

                    menu();
			}
			
			/*while ((opcion = getchar()) != '\n'){
				if(opcion == 'v'){
					printf("Has seleccionado volver hacia atras.\n");
					menu();
					
					
				}*/
			
			}
			
	}

	menu();

			

////////////////////////////////////FIN PARTE ALONSO
	
}
 