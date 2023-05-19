#include "administrador.h"
#include <iostream>


using namespace std;


Administrador::Administrador(const char * nombre, unsigned int sueldo): Persona(nombre)
{
    this->sueldo = sueldo;
}


Administrador::Administrador(const Administrador &a): Persona(a.getNombre())
{
    this->sueldo = a.sueldo;
}


Administrador::~Administrador()
{
}


void Administrador::consultarDatos()
{
    Persona::consultarDatos();
    cout << "Sueldo: " << this->sueldo << endl;
}


