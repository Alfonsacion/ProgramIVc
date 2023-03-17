#define _STRUCT_H_
#ifndef _STRUCT_H_

typedef struct Usuario Usuario;
struct Usuario{
    char[10] nombre;
    int contraseyna;
    Usuario *siguiente;
};

#endif