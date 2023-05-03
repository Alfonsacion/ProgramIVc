// #ifndef _SOCKETSTRUCT_H_
// #define _SOCKETSTRUCT_H_
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

// typedef struct{
//     short int sin_family;           
//     unsigned short int sin_port;    
//     typedef struct in_addr sin_addr;       
//     unsigned char sin_zero[8];     
// }sockaddr_in;

// struct sockaddr_in server_address;
// server_address.sin_family = AF_INET;
// server_address.sin_port = htons(port_number);
// server_address.sin_addr.s_addr = inet_addr(server_ip_address);

// struct sockaddr_in client_address;
// socklen_t client_address_size = sizeof(client_address);
// int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_size);

// #endif