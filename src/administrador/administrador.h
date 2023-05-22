#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_
#include "persona.h"

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
};

#endif