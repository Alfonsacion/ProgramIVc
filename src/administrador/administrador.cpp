#include "administrador.h"
#include <iostream>
#include <string>
#include <string.h>
using namespace std;

int totalPersonas = Persona::getNumPersonas();

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
    for (int i = 0; i < totalPersonas; i++){
        delete usuarios[i];
    }
    delete[] usuarios;
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
    cout<<"Has seleccionado la opción de anyadir un nuevo Administrador."<<endl;
    cout<<"A continuacion indica sus datos: "<<endl;

    char nombre[20];
    char mail[20];
    char tlfn[9];
    char dni[9];
    unsigned int sueldo;

    cout << "Introduce el nombre del administrador: "<<endl;
    //cin.getline(nombre, 20, '\n');

    cout << "Introduce el mail del administrador: "<<endl;
    //cin.getline(mail, 20, '\n');

    cout<< "Introduce el telefono del administrador: "<<endl;
    //cin.getline(tlfn, 9, '\n');

    cout<< "Introduce el dni del administrador: "<<endl;
    //cin.getline(dni,9, '\n');

    cout<< "Introduce el sueldo del administrador: "<<endl;
    cin>>sueldo;

    cin.ignore();

    Administrador admin (nombre, mail, tlfn, dni, sueldo);

    cout<< "Administrador anyadido correctamente. "<< endl;


}

    void Administrador::modificarSueldo(unsigned int nuevoSueldo)
    {
        this->sueldo = nuevoSueldo;
        cout<<"Sueldo modificado correctamente."<<endl;
    }

    void Administrador::eliminarUsuario(const char* dni)
    {
        for(int i = 0; i < totalPersonas; i++){
            if(strcmp(usuarios[i]->getDni(), dni) == 0){
                for(int j = i; j < totalPersonas - 1; j++){
                    usuarios[j] = usuarios[j+1];
                }
                cout<< "Usuario con DNI " << dni << "eliminado correctamente."<<endl;
        

            }

        }
    }



/*  
    
    Administrador admin(nombre, mail, tlfn, dni, sueldo);
    cout<<"Administrador anyadido: "<< admin.getNombre() << endl;*/