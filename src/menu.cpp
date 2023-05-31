#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../sqlite3.h"
#include "../struct.h"
#include "mainAdmin.cpp"
#include "mainCliente.c"
#include "../db/connect/connect.h"


sqlite3* db;

int main()
{    db = (sqlite3*)startConn();
    qulite3_ex
    ec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);

    char dni[];
    char contrasenya[];
    int opcion;

    cout << "Bienvenido!\n" << endl;
    
    cout << "Porfavor ingrese el DNI: " << endl;
    fgets(dni, sizeof(dni), stdin);
    dni[strcspn(dni, "\n")] = 0;
}
/*

 db = (sqlite3*)startConn();
t
