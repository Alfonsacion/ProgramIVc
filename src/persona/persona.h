#ifndef PERSONA_H_
#define PERSONA_H_


class Persona
{
private:
    const char * nombre;
    char * mail;
    char * tlfn;
    char * contrasenya;
    char * dni;
    static int numPersonas;

public:
    Persona();
    Persona(const char * nombre, char * mail, char * tlfn, char * contrasenya, char * dni);
    Persona(const Persona& p);
    virtual ~Persona();


    char * getNombre() const;


    virtual void consultarDatos();


    static int getNumPersonas();
};


#endif
