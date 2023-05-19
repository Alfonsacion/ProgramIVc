#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "persona.h"


int Persona::numPersonas = 0;


Persona::Persona(const char * nombre, char * mail, char * tlfn, char * contrasenya, char * dni) 
{
    this->nombre = new char[strlen(nombre)+1];
    strcpy((char*)this->nombre, nombre);

    this->mail = new char[strlen(mail)+1];
    strcpy((char*)this->mail = mail);

    this->mail = new char[strlen(tlfn)+1];
    strcpy((char*)this->mail = tlfn);

    this->mail = new char[strlen(contrasenya)+1];
    strcpy((char*)this->mail = contrasenya);

    this->mail = new char[strlen(dni)+1];
    strcpy((char*)this->mail = dni);

    numPersonas++;
}

Persona::Persona(const Persona& p)
{
    this->nombre = new char[strlen(p.nombre) + 1];
    strcpy((char*)this->nombre, p.nombre);

    this->mail = new char[strlen(p.mail) + 1];
    strcpy(this->mail, p.mail);

    this->tlfn = new char[strlen(p.tlfn) + 1];
    strcpy((char*)this->tlfn, p.tlfn);

    this->contrasenya = new char[strlen(p.contrasenya) + 1];
    strcpy(this->contrasenya, p.contrasenya);

    this->dni = new char[strlen(p.dni) + 1];
    strcpy(this->dni, p.dni);
    
    numPersonas++;
}



Persona::~Persona()
{
    numPersonas--;
    delete[] nombre;
    delete[] mail;
    delete[] tlfn;
    delete[] contrasenya;
    delete[] dni;
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
