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
{

    char tipo;
    cout << "-------------------" << endl;
    cout << "   ¡Bienvenido!    " << endl;
    cout << "-------------------" << endl;
    cout << "Queremos saber si eres Administrador o Cliente" << endl;
    cout << "Indica con una 'A' si eres administrador y con una 'C' si eres cliente: " << endl;
    cin >> tipo;
    
    if(tipo == 'A'){
        mainAdmin();

    }else if(tipo == 'C') {
        mainCliente();
    }else {
        cout << "Indique una de las letras mencionadas ('A' o 'C')" << endl;
    }
}
