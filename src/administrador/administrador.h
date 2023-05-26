#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_
#include "../../db/connect/connect.h"
#include "../persona/persona.h"
#include "../../sqlite3.c"

class Administrador: public Persona
{
    private:
        unsigned int sueldo;
        Persona** usuarios;

    public:
        Administrador();
        Administrador(const char * nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo);
        Administrador(const Administrador &a);
        virtual ~Administrador();


        virtual void usuarioDatos();
        void consultarDatosClientes();
        void anyadirAdministrador(const char* nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo);
        void modificarSueldo(unsigned int nuevoSueldo);
        void eliminarUsuario(const char* dni);
         void agregarUsuario(char* username, char* password, char *dni, char *correo, char *tlf, sqlite3* db);
        void anyadirPelicula();
        void eliminarPelicula();
        

};

#endif