#ifndef _STRUCT_H_
#define _STRUCT_H_


typedef struct Usuario{
    char nombre[10];
    int contraseyna;
    struct Usuario* siguiente;
}Usuario;



#endif