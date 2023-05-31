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


int mainAdmin(void)
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
			cout<< "2. Anyadir cliente" << endl << endl;
            cout<< "3. Eliminar cliente" << endl << endl;
			cout<< "4. Cerrar sesion" << endl << endl;

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
                cout<< endl << endl << "///////////Indique los datos del cliente que quiere anyadir///////////" << endl << endl;

				char* nomUsuario;
				char* contrasenya;
				char* dni;
				char* correo;
				char* tlf;
				cout<<"Dime el nombre de usuario que quieres anyadir: "<<endl; cin>>nomUsuario;
				cout<<"Dime la contrasenya del usuario que quieres anyadir: "<<endl; cin>>contrasenya;
				cout<<"Dime el dni del usuario que quieres anyadir: "<<endl; cin>> dni;
				cout<<"Dime el correo del usuario que quieres anyadir: "<<endl; cin>>correo;
				cout<<"Dime el tlfn del usuario que quieres anyadir: "<<endl; cin>>tlf;

				agregarUsuario(nomUsuario, contrasenya, dni, correo, tlf, db);
				

                cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%d", &opcion);
				fflush(stdin);
				break;

            case 3:
				char* nomUsuario;
                cout<< endl << endl << "///////////¿Que cliente desea eliminar?///////////" << endl << endl;
				cout<<"Dime el nombre del usuario que quieres eliminar: "<<endl; cin>>nomUsuario;
				
				eliminarUsuario(nomUsuario, db);

                cout<< endl << endl << "Presiona cualquier tecla y enter para volver al menu: ";
                scanf("%d", &opcion);
				fflush(stdin);
				break;

			case 4:
				cout<< endl << endl << "///////////Has cerrado sesion, hasta pronto!///////////" << endl << endl;
				opcion = 6;
				break;
				
			default:
				cout<< endl << endl << "///////////La opcion seleccionada no es valida///////////" << endl << endl;
				fflush(stdin);
				break;
			}
		}
		return 0;
}
