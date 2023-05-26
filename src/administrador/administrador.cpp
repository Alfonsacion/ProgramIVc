#include "administrador.h"
#include <iostream>
#include <string>
#include <string.h>
#include "../../struct.h"
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

void Administrador::usuarioDatos()
{
    Persona::usuarioDatos();
    cout<< "Mail: " << getMail() << endl; //Esto va en persona.h
    cout<< "DNI: " << getDni() << endl;
    cout<< "Telefono: " << getTlfn() << endl;
    cout << "Sueldo: " << this->sueldo << endl;
}

void Administrador::anyadirAdministrador(const char* nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo)
{
    cout<<"Has seleccionado la opcion de anyadir un nuevo Administrador."<<endl;
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

    void visualizarDatosClientes(Persona& cliente){
        cout<< "El nombre: " << cliente.getNombre() <<endl;
        cout<<"El DNI: "<<cliente.getDni()<<endl;
        cout<< "El mail: " << cliente.getMail() << endl;
        cout<< "El telefono: "<<cliente.getTlfn()<<endl;
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

    void eliminarPelicula(){
        sqlite3* db;
        Pelicula p = verPeliculas(db);
        char** peliculas = new char*[5];
        for(int i = 0; i < 5; i++){
            peliculas[i] = p.nom_pel;

        }

    }



/*  
FUNCIONES A METER EN ADMIN
        Administrador();
        Administrador(const char * nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo);
        Administrador(const Administrador &a);
        virtual ~Administrador();


        virtual void usuarioDatos();
        void consultarDatosClientes();
        void anyadirAdministrador(const char* nombre, const char * mail, const char * tlfn, const char * dni, unsigned int sueldo);
        void modificarSueldo(unsigned int nuevoSueldo);
        void eliminarUsuario(const char* dni);
        
        void anyadirPelicula();
        void eliminarPelicula();

};


    VER SI ESTO ES SICUA
    Administrador admin(nombre, mail, tlfn, dni, sueldo);
    cout<<"Administrador anyadido: "<< admin.getNombre() << endl;*/