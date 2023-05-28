#define WIN32_LEAN_AND_MEAN

#undef UNICODE

#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "1"

int __cdecl main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    ////////////////// A ENVIAR ///////////////////////

    string strUsuario = "Iker";
    string strContrasenya = "gym";
    string strBuf = "2";
    string strOpcionMenu;
    string tecla;

    ////////////////// A RECIBIR ///////////////////////

    char recvUsur[DEFAULT_BUFLEN];
    char recvContra[DEFAULT_BUFLEN];
    char recvBuf[DEFAULT_BUFLEN];

    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    if (argc != 2)
    {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                               ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET)
        {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer

    /////////////////// ENVIOS ///////////////////////////////
    ////////////USUARIO//////////////
    bool mandar = true;
    while (mandar)
    {
        cout << "Usuario: ";
        cin >> strBuf;
        const char *usuario = strBuf.c_str();
        if ((strcmp(usuario, "n") != 0))
        {
            iResult = send(ConnectSocket, usuario, (int)strlen(usuario), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %s\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }

            printf("Usuario enviado desde cliente: %s\n", usuario);

            cout << "Contrasena: ";
            cin >> strBuf;
            const char *contraseyna = strBuf.c_str();
            iResult = send(ConnectSocket, contraseyna, strlen(contraseyna), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %s\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }
            printf("Contrasena enviada desde cliente: %s\n", contraseyna);
            mandar = false;
        }
        else
        {

            iResult = send(ConnectSocket, usuario, (int)strlen(usuario), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %s\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }

            printf("Usuario enviado desde cliente: %s\n", usuario);

            cin >> strBuf;
            const char *contraseyna = strBuf.c_str();
            iResult = send(ConnectSocket, contraseyna, strlen(contraseyna), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %s\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }
            printf("Contrasena enviada desde cliente: %s\n", contraseyna);

            cin >> strBuf;
            const char *dni = strBuf.c_str();
            iResult = send(ConnectSocket, dni, strlen(dni), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %s\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }

            printf("DNI enviado desde cliente: %s\n", dni);

            cin >> strBuf;
            const char *correo = strBuf.c_str();
            iResult = send(ConnectSocket, correo, strlen(correo), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %s\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }
            printf("Correo enviado desde cliente: %s\n", correo);

            cin >> strBuf;
            const char *tlf = strBuf.c_str();
            iResult = send(ConnectSocket, tlf, strlen(tlf), 0);
            if (iResult == SOCKET_ERROR)
            {
                printf("send failed with error: %s\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }
            printf("telefono enviado desde cliente: %s\n", tlf);
        }
    }

    cin >> strOpcionMenu;
    const char *opcionMenu = strOpcionMenu.c_str();
    iResult = send(ConnectSocket, opcionMenu, strlen(opcionMenu), 0);
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed with error: %s\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Opcion enviada desde cliente: %s\n", opcionMenu);

    cin >> tecla;
    const char *opcionVolver = tecla.c_str();
    iResult = send(ConnectSocket, opcionVolver, strlen(opcionVolver), 0);
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Opción volver envíada desde cliente");

    // iResult = recv(ConnectSocket, recvBuf, recvbuflen - 1, 0);
    // if (iResult == SOCKET_ERROR)
    // {
    //     printf("recv failed with error: %d\n", WSAGetLastError());
    //     closesocket(ConnectSocket);
    //     WSACleanup();
    //     return 1;
    // }

    // // Asegurarse de que la respuesta sea terminada con el carácter nulo
    // recvBuf[iResult] = '\0';

    // // Imprimir la respuesta recibida del servidor
    // printf("Respuesta del servidor: %s\n", recvBuf);

    // cin >> strOpcionMenu;
    // const char *volver = strOpcionMenu.c_str();
    // iResult = send(ConnectSocket, volver, strlen(volver), 0);
    // if (iResult == SOCKET_ERROR)
    // {
    //     printf("send failed with error: %s\n", WSAGetLastError());
    //     closesocket(ConnectSocket);
    //     WSACleanup();
    //     return 1;
    // }

    // printf("Boton para volver enviado desde cliente: %s\n", volver);

    ////////////CONTRASENYA//////////////

    /*cin >> strContrasenya;
    const char *contrasenya = strContrasenya.c_str();
    iResult = send( ConnectSocket, contrasenya, (int)strlen(contrasenya), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %s\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Conrtasenya enviada desde cliente: %s\n", contrasenya);

    ////////////OPCION MENU//////////////

    cin >> strOpcionMenu;
    const char *opcionMenu = strOpcionMenu.c_str();
    iResult = send( ConnectSocket, opcionMenu, (int)strlen(opcionMenu), 0 );
    if (iResult == SOCKET_ERROR) {
        printf("send failed with error: %s\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Opcion enviada desde cliente: %s\n", opcionMenu);

    //printf("Message Sent: %s\n", iResult);


    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }*/

    // Receive until the peer closes the connection

    /////////////////// RECIBOS ///////////////////////////////
    ////////////USUARIO//////////////

    /*printf("el tmanyo es: %i\n", (int)strlen(usuario));

    iResult = recv(ConnectSocket, recvUsur, (int)strlen(usuario), 0);
    if ( iResult > 0 ){
        printf("Usuario de vuelta en cliente: %s\n", recvUsur); }
    else if ( iResult == 0 )
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());*/

    ////////////CONTRASENYA//////////////

    /*iResult = recv(ConnectSocket, recvContra, (int)strlen(contrasenya), 0);
    if ( iResult > 0 ){
        printf("Contrasenya de vuelta en cliente: %s\n", recvContra); }
    else if ( iResult == 0 )
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());

    ////////////OPCION MENU//////////////

    iResult = recv(ConnectSocket, recvOpMen, (int)strlen(opcionMenu), 0);
    if ( iResult > 0 ){
        printf("Opcion de vuelta en cliente: %s\n", recvOpMen); }
    else if ( iResult == 0 )
        printf("Connection closed\n");
    else
        printf("recv failed with error: %d\n", WSAGetLastError());*/

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}

// https://learn.microsoft.com/en-us/windows/win32/winsock/complete-server-code

// c++ -o cliente cliente.cpp -lws2_32