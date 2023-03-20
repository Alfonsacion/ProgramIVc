#ifndef _STRUCT_H_
#define _STRUCT_H_
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


typedef struct Usuario{ 
    char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];
}Usuario;



#endif