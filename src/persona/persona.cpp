#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "Persona.h"


int Persona::numPersonas = 0;


Persona::Persona(const char *nombre)
{
    this->nombre = new char[strlen(nombre)+1];
    strcpy((char*)this->nombre, nombre);
    numPersonas++;
}


Persona::Persona(const Persona& p)
{
    this->nombre = new char[strlen(p.nombre) + 1];
    strcpy((char*)this->nombre, p.nombre);
    numPersonas++;
}


Persona::~Persona()
{
    numPersonas--;
    delete[] nombre;
}


char* Persona::getNombre() const
{
    return (char*)this->nombre;
}


void Persona::consultarDatos()
{
    cout << "NOMBRE: " << this->nombre << endl;
}


int Persona::getNumPersonas()
{
    return numPersonas;
}
