#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "cliente/cliente.h"
#include "../db/connect/connect.h"
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


// #include <iostream>
// #include <cstring>
// #include <cerrno>
// #include "cpp/dec/socket_server.h"
// #include "cpp/dec/socket_client.h"
// #include "cpp/dec/socket_handler.h"

// #ifdef _WIN32
// #include <winsock2.h>
// #else
// #include <unistd.h>
// #endif


//SOCKET
// void handle_client(SOCKET client_socket) {
//     char buffer[1024];
//     int recv_size;

//     while ((recv_size = recv(client_socket, buffer, sizeof(buffer) - 1, 0)) > 0) {
//         buffer[recv_size] = '\0';
//         std::cout << "Mensaje recibido: " << buffer << std::endl;

//         // Enviar respuesta al cliente
//         const char *response = "Mensaje recibido por el servidor.";
//         send(client_socket, response, strlen(response), 0);
//     }

//     if (recv_size == 0) {
//         std::cout << "Cliente desconectado." << std::endl;
//     } else {
//         std::cerr << "Error al recibir datos del cliente: " << strerror(errno) << std::endl;
//     }

//     closesocket(client_socket);
    
// }

int main(void)
{

// 	  const char *ip_address = "127.0.0.1";
//     int port = 8080;

//     SOCKET server_socket = iniciar_servidor(port);

//     std::cout << "Servidor iniciado en puerto " << port << std::endl;

//     while (true) {
//         struct sockaddr_in client_address;
//         int client_address_len = sizeof(client_address);

//         SOCKET client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
//         if (client_socket < 0) {
//             std::cerr << "Error al aceptar la conexión del cliente: " << strerror(errno) << std::endl;
//             continue;
//         }

//         std::cout << "Cliente conectado: " << inet_ntoa(client_address.sin_addr) << ":" << ntohs(client_address.sin_port) << std::endl;

//         handle_client(client_socket);
//     }

//     closesocket(server_socket);



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
	// free(b);
	// free(c);
	// free(d);
	//free(e);

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
