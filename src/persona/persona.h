#ifndef PERSONA_H_
#define PERSONA_H_


class Persona
{
private:
    const char * nombre;
    const char * mail;
    const char * tlfn;
    char * contrasenya;
    const char * dni;
    static int numPersonas;

public:
    Persona();
    Persona(const char * nombre, const char * mail, const char * tlfn, const char * dni);
    Persona(const Persona& p);
    virtual ~Persona();

    char * getNombre() const;
    char * getMail() const;
    char * getTlfn() const;
    char * getDni() const;
    virtual void consultarDatos();
    static int getNumPersonas();
};


#endif
