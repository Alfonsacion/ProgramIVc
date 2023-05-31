Compilacion: 

Cliente: g++ -o cliente.exe cliente.cpp ../cliente/cliente.o ../../db/connect/connect.o ../../sqlite3.o -lws2_32

Servidor: g++ -o main.exe servidor.cpp ../cliente/cliente.o ../../db/connect/connect.o ../../sqlite3.o -lws2_32

El programa se ejecuta mediante 'cliente localhost' con main.exe abierto.