#include "cliente2.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

Cliente2::Cliente2(const char *nombre, const char *mail, const char *tlfn, const char *dni) : Persona(nombre, mail, tlfn, dni)
{
}

Cliente2::Cliente2(const Cliente2 &c2) : Persona(Persona::getNombre(), c2.getDni(), c2.getMail(), c2.getTlfn())
{
}

Cliente2::~Cliente2()
{
}

void Cliente2::usuarioDatos()
{
    Persona::usuarioDatos();
    // getters y setters
}
