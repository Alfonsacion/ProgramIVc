#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_
#include "persona.h"

class Administrador: public Persona
{
    private:
        unsigned int sueldo;

    public:
        Administrador();
        Administrador(const char * nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo);
        Administrador(const Administrador &a);
        virtual ~Administrador();


        virtual void consultarDatos();
        void anyadirAdministrador(const char* nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo);
        void modificarDatosUsuario();//adasfs
};

#endif