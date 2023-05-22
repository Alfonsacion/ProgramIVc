#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "administrador/administrador.h"
#include "../db/connect/connect.h"
using namespace std;


int main(void)
{
    sqlite3 *db;
	char *error;

    char nombreUsuario[MAX_PASSWORD_LENGTH];
	char contraseyna[MAX_PASSWORD_LENGTH];
	char dniUsuario[MAX_PASSWORD_LENGTH];
	char correoUsuario[MAX_PASSWORD_LENGTH];
	char tlf[MAX_PASSWORD_LENGTH];

    char *a = new char((strlen(nombreUsuario) + 1) * sizeof(char));
	a = strcpy(a, nombreUsuario);
	a[strlen(a)] = '\0';

    Usuario u = login(a, contraseyna, dniUsuario, correoUsuario, tlf, db);

    int opcion = 1;
    UsuarioDatos ud;

		while (opcion <= 6 && opcion >= 0)
		{
			cout<< endl << endl << "///////////Menu de Administrador///////////" << endl << endl;

			cout<< "1. Visualizar tus datos" << endl << endl;
			cout<< "2. Visualizar datos de un cliente" << endl << endl;
			cout<< "3. Modificar un cliente" << endl << endl;
            cout<< "4. Eliminar un cliente" << endl << endl;
            cout<< "5. Anyadir pelicula" << endl << endl;
            cout<< "6. Eliminar pelicula" << endl << endl;
			cout<< "7. Cerrar sesion" << endl << endl;

			cout<< "Seleccione la opcion que desee: " << endl << endl;
			scanf("%1d", &opcion);
			switch (opcion)

			{

			case 1:
				cout<< endl << endl << "///////////Visualizacion de datos personales///////////" << endl << endl;

                ud = usuarioDatos(u.nombreUsuario, db);

				cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%1d", &opcion);
				fflush(stdin);
				break;


			case 2:
                cout<< endl << endl << "///////////Visualizacion de datos de los clientes///////////" << endl << endl;

                //metodo para visualizar datos de clientes

				cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%1d", &opcion);
				fflush(stdin);
				break;

			case 3:
                cout<< endl << endl << "///////////¿Que cliente desea modificar?///////////" << endl << endl;

                //metodo para modificar o eliminar clientes y sus datos

                cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%d", &opcion);
				fflush(stdin);
				break;

            case 4:
                cout<< endl << endl << "///////////¿Que cliente desea eliminar?///////////" << endl << endl;

                //metodo para modificar o eliminar clientes y sus datos

                cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%d", &opcion);
				fflush(stdin);
				break;

            case 5:
                cout<< endl << endl << "///////////¿Que pelicula deseas anyadir?///////////" << endl << endl;

                //metodo para añadir peliculas

                cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%d", &opcion);
				fflush(stdin);
				break;

            case 6:
                cout<< endl << endl << "///////////¿Que pelicula deseas eliminar?///////////" << endl << endl;

                //metodo para eliminar peliculas

                cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%d", &opcion);
				fflush(stdin);
				break;

			case 7:
				cout<< endl << endl << "///////////Has cerrado sesion, hasta pronto!///////////" << endl << endl;
				opcion = 9;
				break;
				
			default:
				cout<< endl << endl << "///////////La opcion seleccionada no es valida///////////" << endl << endl;
				fflush(stdin);
				break;
			}
		}
		return 0;
}
