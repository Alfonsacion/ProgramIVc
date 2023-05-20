#include "administrador.h"
#include <iostream>
using namespace std;

Administrador::Administrador(const char * nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo): Persona(nombre, mail, tlfn, dni)
{
    this->sueldo = sueldo;
}


Administrador::Administrador(const Administrador &a): Persona(Persona::getNombre(), a.getMail(), a.getTlfn(), a.getDni())
{
    this->sueldo = a.sueldo;
}


Administrador::~Administrador()
{
}


void Administrador::consultarDatos()
{
    Persona::consultarDatos();
    cout<< "Mail: " << getMail() << endl;
    cout<< "DNI: " << getDni() << endl;
    cout<< "Telefono: " << getTlfn() << endl;
    cout << "Sueldo: " << this->sueldo << endl;
}


void Administrador::anyadirAdministrador(const char* nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo)
{
    Administrador admin(nombre, mail, tlfn, dni, sueldo);
    cout<<"Administrador anyadido: "<< admin.getNombre() << endl;
}


