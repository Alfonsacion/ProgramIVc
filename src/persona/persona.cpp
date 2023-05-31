#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;
#include "persona.h"


int Persona::numPersonas = 0;

Persona::Persona()
{
}

Persona::Persona(const char * nombre, const char * mail, const char * tlfn, const char * dni) 
{
    this->nombre = new char[strlen(nombre)+1];
    strcpy((char*)this->nombre, nombre);

    this->mail = new char[strlen(mail)+1];
    strcpy((char*)this->mail, mail);

    this->mail = new char[strlen(tlfn)+1];
    strcpy((char*)this->mail, tlfn);

    this->mail = new char[strlen(dni)+1];
    strcpy((char*)this->mail,  dni);

    numPersonas++;
}

Persona::Persona(const Persona& p)
{
    this->nombre = new char[strlen(p.nombre) + 1];
    strcpy((char*)this->nombre, p.nombre);

    this->mail = new char[strlen(p.mail) + 1];
    strcpy((char*)this->mail, p.mail);

    this->tlfn = new char[strlen(p.tlfn) + 1];
    strcpy((char*)this->tlfn, p.tlfn);

    this->contrasenya = new char[strlen(p.contrasenya) + 1];
    strcpy(this->contrasenya, p.contrasenya);

    this->dni = new char[strlen(p.dni) + 1];
    strcpy((char*)this->dni, p.dni);
    
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

char * Persona::getDni() const
{
    return (char*) this->dni;
}

char * Persona::getMail() const
{
    return (char*) this-> mail;
}

char * Persona::getTlfn() const
{
    return (char*) this->tlfn;
}

int Persona::getNumPersonas()
{
    return numPersonas;
}

void Persona::setNombre(char * nombre)
{
    this->nombre = nombre;
}

void Persona::setMail(char * mail)
{
    this->mail = mail;
}

void Persona::setTlfn(char * tlfn){
    this->tlfn = tlfn;
}

void Persona::setContrasenya(char * contrasenya)
{
    this->contrasenya = contrasenya;
}

void Persona::setDni(char * dni)
{
    this->dni = dni;
}