#ifndef PERSONA_H_
#define PERSONA_H_


class Persona
{
private:
    const char * nombre;
    static int numPersonas;


public:
    Persona();
    Persona(const char * nombre);
    Persona(const Persona& p);
    virtual ~Persona();


    char * getNombre() const;


    virtual void consultarDatos();


    static int getNumPersonas();
};


#endif
