#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501


#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
using namespace std;






extern "C"
{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../sqlite3.h"
#include "../../struct.h"
#include "../cliente/cliente.h"
#include "../../db/connect/connect.h"

//#include "../../sqlite3.h"
//#include "../../struct.h"
//#include "../cliente/cliente.h"
//#include "../../db/connect/connect.h"

}







// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1"

int __cdecl main(void) 
{

    //////////////////SOCKETS ESENCIAL//////////////////////

    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvUsur[DEFAULT_BUFLEN];
    char recvContra[DEFAULT_BUFLEN];
    char recvBuf[DEFAULT_BUFLEN];

    int recvbuflen = DEFAULT_BUFLEN;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 ) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    ///////////////FINAL SOCKET ESENCIAL////////////////////////


    std::cout << "Servidor preparado para cliente";


    ///////////////////CCCCCCCCCCCCCCC/////////////////////
    sqlite3 *db;
	char *error;
    FILE *f;
    f = fopen("DatosUsuarios.txt", "a");
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

	char *a = new char((strlen(nombreUsuario) + 1) * sizeof(char));
	a = strcpy(a, nombreUsuario);
	a[strlen(a)] = '\0';


	std::cout << endl;
    std::cout << "Bienvenido/a, ahora puedes iniciar sesión\n" << endl;
    std::cout << endl;

////////////////////////////////////////////

    std::cout << "Introduce tu nombre de usuario, si no tienes escribe 'n': " << endl;
    std::cin >> a;
    if (strcmp(a, "n") == 0)
  {

    std:: cout << "Elige tu nombre de usuario: " << endl;
    std:: cin >> a;
    iResult = send(ListenSocket, a, strlen(a)+1, 0);
    std:: cout << "Elige cual va ser tu contrasena: " << endl ;
    std:: cin >> contraseyna;
    iResult = send(ListenSocket, contraseyna, strlen(contraseyna)+1, 0);
    std:: cout << "Ingresa tu dni: " << endl;
    std::cin >> dniUsuario;
    iResult = send(ListenSocket, dniUsuario, strlen(dniUsuario)+1, 0);
    std:: cout << "Ingresa tu correo: " << endl;
    std::cin >> correoUsuario;
    iResult = send(ListenSocket, correoUsuario, strlen(correoUsuario)+1, 0);
    std:: cout << "Ingresa tu numero de tlf: " << endl;
    std::cin >> tlf;
    iResult = send(ListenSocket, tlf, strlen(tlf)+1, 0);
    agregarUsuario(a, contraseyna, dniUsuario, correoUsuario, tlf, db);
    fprintf(f, "%s %s\n", a, contraseyna);
    std::cout << "Usuario registrado, felicidades, ya puedes iniciar sesion con ese usuario" << endl;
    fclose(f);
  
  }else{
    iResult = send(ListenSocket, a, strlen(a)+1, 0);
    std::cout << "Ingresa tu contraseña: ";
    std::cin >> contraseyna;
    iResult = send(ListenSocket, contraseyna, strlen(contraseyna)+1, 0);
    Usuario u = leeUsuario(a, contraseyna, db);
    fclose(f);

  }
    
    memset(recvUsur, 0, sizeof(recvUsur));


//////////////////////////////////////////////


	Usuario u = login(a, contraseyna, dniUsuario, correoUsuario, tlf, db);

	delete(a);


	///////////////////////////////////////
	int seleccionPelicula = 0;
	int seleccionHorario = 0;
	int numEntradas = 0;
	int numEntradasSeleccionadas = 0;
	int numPeliculas = 0;
	const char *arrayPeliculas[6];
	const char *arrayHorarios[4];
    ///////////////////////////////////////



	AsientoElegido *arrayAsientosElegidos;



	int opcion = 1;
	Pelicula p;
	UsuarioDatos ud;
	Horario h;
	Seleccion s;

		while (opcion <= 5 && opcion >= 0)
		{
			std::cout << "\n\n///////////Menu Cineplex///////////\n\n";
            std::cout << "1. Visualizar datos del usuario\n\n";
            std::cout << "2. Efectuar una reserva \n\n";
            std::cout << "3. Visualizar las peliculas disponibles \n\n";
            std::cout << "4. Cerrar sesión\n\n";
            std::cout << "Seleccione la opción que desee: \n";

			/////////////OPCION MENU/////////////

            iResult = recv(ClientSocket, recvBuf, recvbuflen, 0);

            int opcion = stoi(recvBuf);

			    switch (opcion)

			{

			case 1:
				
				ud = usuarioDatos(u.nombreUsuario, db);

				std::cout << "\n\nPresiona cualquier tecla y enter para volver al menú: ";

				iResult = recv(ClientSocket, recvBuf, recvbuflen, 0);
				break;


			case 2:
                std::cout << "\n\n///////////Bienvenido al gestor de reservas///////////\n\n";

				seleccionPelicula = pantallaCartelera(arrayPeliculas, numPeliculas, db);
				seleccionHorario = seleccionHorarios(seleccionPelicula, s.dia, arrayHorarios, arrayPeliculas);
				numEntradas = confirmacionTicket(seleccionPelicula, arrayPeliculas, arrayHorarios, seleccionHorario);
                arrayAsientosElegidos = new AsientoElegido[numEntradas];

				generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas, numEntradas);

				for (numEntradasSeleccionadas = 0; numEntradasSeleccionadas < numEntradas; numEntradasSeleccionadas++)
				{
					elegirAsiento(arrayAsientosElegidos, numEntradasSeleccionadas);
					generarSalaA(arrayAsientosElegidos, numEntradasSeleccionadas, numEntradas);
					numEntradasSeleccionadas = confirmacionAsiento(numEntradasSeleccionadas);
				}

				exportarDatos(numEntradasSeleccionadas, seleccionPelicula, arrayPeliculas);
				// confirmacionDefinitiva(seleccionPelicula, arrayPeliculas, seleccionHorario, arrayHorarios, numEntradas, arrayAsientosElegidos, numEntradasSeleccionadas);

                std::cout << "\n\nPresiona cualquier tecla y enter para volver al menú: ";
				iResult = recv(ClientSocket, recvBuf, recvbuflen, 0);
				break;

			case 3:

				p = verPeliculas(db);
                std::cout << "\n\nPresiona cualquier tecla y enter para volver al menú: ";
				iResult = recv(ClientSocket, recvBuf, recvbuflen, 0);
				break;

			case 4:
                std::cout << "\n\n///////////Has cerrado sesión, hasta pronto!///////////\n\n";

				opcion = 6;
                iResult = shutdown(ClientSocket, SD_SEND);
                if (iResult == SOCKET_ERROR) {
                    printf("shutdown failed with error: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }

                // cleanup
                closesocket(ClientSocket);
                WSACleanup();
                break;
				
			default:

                std::cout << "\n\n///////////La opción seleccionada no es válida///////////\n\n";
				fflush(stdin);
				break;

			}
		}




    /////////////////// RECIBOS ///////////////////////////////

    // Receive until the peer shuts down the connection

        /////////////USUARIO/////////////

        iResult = recv(ClientSocket, recvUsur, recvbuflen, 0);
        if (iResult > 0) {
            printf("Mensaje recibido en servidor: %s\n", recvUsur);
            

        // Echo the buffer back to the sender
            iSendResult = send( ClientSocket, recvUsur, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %s\n", recvUsur);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

        /////////////CONTRA/////////////

        iResult = recv(ClientSocket, recvContra, recvbuflen, 0);
        if (iResult > 0) {
            printf("Mensaje recibido en servidor: %s\n", recvContra);

        // Echo the buffer back to the sender
            iSendResult = send( ClientSocket, recvContra, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %s\n", recvContra);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

        /////////////OPCION MENU/////////////

        iResult = recv(ClientSocket, recvBuf, recvbuflen, 0);
        if (iResult >= 0) {
            printf("Mensaje recibido en servidor: %s\n", recvBuf);

        // Echo the buffer back to the sender
            iSendResult = send( ClientSocket, recvBuf, iResult, 0 );
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %s\n", recvBuf);
        }
        
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }


    // shutdown the connection since we're done

    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}











//c++ -o server servidor.cpp -lws2_32

// g++ -o main servidor.cpp ..\cliente\cliente.c ..\..\db\connect\connect.c ..\..\sqlite3.c

// https://stackoverflow.com/questions/5430688/compiling-c-and-c-files-together-using-gcc

// g++ -o main.exe servidor.cpp cliente.o connect.o sqlite3.o -lws2_32

// g++ -o main.exe servidor.cpp ../cliente/cliente.o ../../db/connect/connect.o ../../sqlite3.o -lws2_32

// g++ -o main.exe servidor.cpp ../cliente/cliente.o ../../db/connect/connect.o ../../sqlite3.o -lws2_32

// gcc -c -o ../../db/connect/connect.o ../../db/connect/connect.c 

// gcc -c -o ../cliente/cliente.o ../cliente/cliente.c 

// gcc -c -o ../../sqlite3.o ../../sqlite3.c