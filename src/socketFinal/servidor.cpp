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
}

#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1"

int __cdecl main(void)
{

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

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    closesocket(ListenSocket);

    std::cout << endl
              << "Servidor preparado para cliente";

    sqlite3 *db;
    char *error;
    FILE *f;
    f = fopen("DatosUsuarios.txt", "a");
    int baseDedatos = openDB(db);
    int pelicula = tablaPelicula(db, error);
    int horario = tablaHorario(db, error);
    int fecha = tablaFecha(db, error);
    int usuarioTest = tablaUsuario(db, error);
    int bucleEntradas;

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

    Usuario u;
    bool mandar = true;
    while (mandar == true)
    {
        iResult = recv(ClientSocket, nombreUsuario, sizeof(nombreUsuario), 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
        nombreUsuario[iResult] = '\0';
        printf("Usuario recibido desde cliente: %s\n", nombreUsuario);

        if (strcmp(nombreUsuario, "n") == 0)
        {

            iResult = recv(ClientSocket, nombreUsuario, sizeof(nombreUsuario), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            nombreUsuario[iResult] = '\0';
            printf("Usuario recibido desde cliente: %s\n", nombreUsuario);

            iResult = recv(ClientSocket, contraseyna, sizeof(contraseyna), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            contraseyna[iResult] = '\0';
            printf("Contrasena recibida desde cliente: %s\n", contraseyna);

            iResult = recv(ClientSocket, dniUsuario, sizeof(dniUsuario), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            dniUsuario[iResult] = '\0';
            printf("Dni recibido desde cliente: %s\n", dniUsuario);

            iResult = recv(ClientSocket, correoUsuario, sizeof(correoUsuario), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            correoUsuario[iResult] = '\0';
            printf("Correo recibido desde cliente: %s\n", correoUsuario);

            iResult = recv(ClientSocket, tlf, sizeof(tlf), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            tlf[iResult] = '\0';
            printf("Telefono recibido desde cliente: %s\n", tlf);

            agregarUsuario(nombreUsuario, contraseyna, dniUsuario, correoUsuario, tlf, db);
            fprintf(f, "%s %s\n", nombreUsuario, contraseyna);
            fclose(f);

            mandar = false;
        }
        else
        {
            iResult = recv(ClientSocket, contraseyna, sizeof(contraseyna), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            contraseyna[iResult] = '\0';

            printf("Contrasena recibida desde cliente: %s\n", contraseyna);
            mandar = false;
        }
    }
    mandar = false;
    u = login(nombreUsuario, contraseyna, dniUsuario, correoUsuario, tlf, db);
    fclose(f);

    int seleccionPelicula = 0;
    int seleccionHorario = 0;
    int numEntradas = 0;
    int numEntradasSeleccionadas = 0;
    int numPeliculas = 0;
    const char *arrayPeliculas[6];
    const char *arrayHorarios[4];

    AsientoElegido *arrayAsientosElegidos;
    Pelicula p;
    UsuarioDatos ud;
    Horario h;
    Seleccion s;
    int menu = 1;
    char volverMenu[MAX_PASSWORD_LENGTH];
    int opcion = 1;

    do
    {
        iResult = recv(ClientSocket, recvBuf, sizeof(recvBuf), 0);
        if (iResult == SOCKET_ERROR)
        {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }
        recvBuf[iResult] = '\0';

        std::cout << "Opcion recibida desde cliente" << std::endl;

        opcion = stoi(recvBuf);

        switch (opcion)

        {

        case 1:

            ud = usuarioDatos(u.nombreUsuario, db);
            char *datos;
            strcpy(datos, "Nombre: ");
            strcat(datos, ud.nombreUsuario);
            strcat(datos, "\nDNI: ");
            strcat(datos, ud.dni);
            strcat(datos, "\nCorreo: ");
            strcat(datos, ud.correo);
            strcat(datos, "\nTelefono: ");
            strcat(datos, ud.tlf);

            iSendResult = send(ClientSocket, datos, strlen(datos), 0);
            if (iSendResult == SOCKET_ERROR)
            {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

            break;

        case 2:

            iResult = recv(ClientSocket, recvBuf, sizeof(recvBuf), 0);

            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

            recvBuf[iResult] = '\0';

            std::cout << "Numero de entradas recibida desde cliente" << std::endl;

            iSendResult = send(ClientSocket, recvBuf, strlen(recvBuf), 0);
            if (iSendResult == SOCKET_ERROR)
            {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

            int bucleWhile;
            bucleWhile = stoi(recvBuf);
            cout << "el bucle es " << bucleWhile << endl;

            iResult = recv(ClientSocket, recvBuf, sizeof(recvBuf), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("recv failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            recvBuf[iResult] = '\0';

            std::cout << "Eleccion de asiento recibido desde cliente" << std::endl;
            std::cout << "El asiento en servidor es " << recvBuf << std::endl;

            iSendResult = send(ClientSocket, recvBuf, strlen(recvBuf), 0);
            if (iSendResult == SOCKET_ERROR)
            {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

            break;

        case 3:
            const char *mensajeEnviar;
            mensajeEnviar = verPeliculas(db);

            iSendResult = send(ClientSocket, mensajeEnviar, strlen(mensajeEnviar), 0);
            if (iSendResult == SOCKET_ERROR)
            {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

            break;

        case 4:

            opcion = 6;
            iResult = shutdown(ClientSocket, SD_SEND);
            if (iResult == SOCKET_ERROR)
            {
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

    } while (opcion >= 1 && opcion <= 4);
}

// c++ -o server servidor.cpp -lws2_32

// g++ -o main servidor.cpp ..\cliente\cliente.c ..\..\db\connect\connect.c ..\..\sqlite3.c

// https://stackoverflow.com/questions/5430688/compiling-c-and-c-files-together-using-gcc

// g++ -o main.exe servidor.cpp cliente.o connect.o sqlite3.o -lws2_32

// g++ -o main.exe servidor.cpp ../cliente/cliente.o ../../db/connect/connect.o ../../sqlite3.o -lws2_32

// g++ -o cliente.exe cliente.cpp ../cliente/cliente.o ../../db/connect/connect.o ../../sqlite3.o -lws2_32

// gcc -c -o ../../db/connect/connect.o ../../db/connect/connect.c

// gcc -c -o ../cliente/cliente.o ../cliente/cliente.c

// gcc -c -o ../../sqlite3.o ../../sqlite3.c