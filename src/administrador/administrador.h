#ifndef ADMINISTRADOR_H_
#define ADMINISTRADOR_H_


#include "persona.h"


class Administrador: public Persona
{
    private:
        unsigned int sueldo;



    public:
        Administrador();
        Administrador(const char * nombre, unsigned int sueldo);
        Administrador(const Administrador &a);
        virtual ~Administrador();


        virtual void consultarDatos();
        void modificarDatosUsuario();//adasfs




};


#endif