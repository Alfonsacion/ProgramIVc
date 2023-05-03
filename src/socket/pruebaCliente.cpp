// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// #include <iostream>
// #include "socketStruct.h"

// int client_socket = socket(AF_INET, SOCK_STREAM, 0);

// int connection_status = connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

// if (connection_status == -1) {
//     std::cout << "Error al conectar al servidor\n";
//     close(client_socket);
//     return 1;
// }