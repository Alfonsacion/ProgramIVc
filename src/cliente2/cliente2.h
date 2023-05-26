#ifndef CLIENTE2_H_
#define CLIENTE2_H_
#include "../persona/persona.h"

class Cliente2: public Persona
{
    private:
        

    public:
        Cliente2();
        Cliente2(const char * nombre, const char * mail, const char * tlfn, const char * dni);
        Cliente2(const Cliente2 &C2);
        virtual ~Cliente2();


        virtual void usuarioDatos();
        void generarSalaA();

};

#endif