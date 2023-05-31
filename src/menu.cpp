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
/*

    
    if (validarCliente(dni, contrasena)) {
        sqlite3_close(db);
        printf("Bienvenido, cliente!\n");
        menu_cliente();

       
    } else if (validarAdministrador(dni, contrasena)) {
        printf("Bienvenido, administrador!\n");
        closeConn(db);
        admin_menu();
    
    } else {
        printf("Usuario o contraseña incorrectos.\n");
    }
    sqlite3_exec(db, "COMMIT TRANSACTION", NULL, NULL, NULL);
    sqlite3_close(db);
    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Función de callback para la consulta a la base de datos
int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *errMsg = 0;
    int rc;
    char dni[20];
    char password[20];
    char query[100];

    // Abrir la base de datos
    rc = sqlite3_open("database.db", &db);
    if (rc) {
        fprintf(stderr, "No se pudo abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    printf("Ingrese su DNI: ");
    scanf("%s", dni);
    printf("Ingrese su contraseña: ");
    scanf("%s", password);

    // Construir y ejecutar la consulta para validar las credenciales
    sprintf(query, "SELECT tipo FROM usuarios WHERE dni='%s' AND contrasena='%s'", dni, password);
    rc = sqlite3_exec(db, query, callback, 0, &errMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error en la consulta SQL: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        // Verificar el tipo de usuario y abrir el menú correspondiente
        if (sqlite3_changes(db) > 0) {
            char tipo[20];
            sprintf(query, "SELECT tipo FROM usuarios WHERE dni='%s'", dni);
            rc = sqlite3_exec(db, query, callback, tipo, &errMsg);
            if (rc != SQLITE_OK) {
                fprintf(stderr, "Error en la consulta SQL: %s\n", errMsg);
                sqlite3_free(errMsg);
            } else {
                if (strcmp(tipo, "cliente") == 0) {
                    printf("Bienvenido, cliente\n");
                    // Aquí puedes colocar el código para el menú del cliente
                } else if (strcmp(tipo, "administrador") == 0) {
                    printf("Bienvenido, administrador\n");
                    // Aquí puedes colocar el código para el menú del administrador
                }
            }
        } else {
            printf("Credenciales inválidas\n");
        }
    }

    // Cerrar la base de datos
    sqlite3_close(db);
    return 0;
}



*/