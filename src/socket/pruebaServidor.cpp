// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <iostream>
// #include "socketStruct.h"

// int server_socket = socket(AF_INET, SOCK_STREAM, 0);

// int bind_status = bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));

// int listen_status = listen(server_socket, SOMAXCONN);

// if (client_socket == -1) {
//     std::cout << "Error al aceptar la conexión entrante\n";
//     close(server_socket);
//     return 1;
// }

