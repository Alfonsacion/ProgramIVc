#ifndef _STRUCT_H_
#define _STRUCT_H_
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


typedef struct Usuario{ 
    char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];
}Usuario;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct UsuarioDatos{
    char nombreUsuario[MAX_USERNAME_LENGTH];
    char dni[MAX_PASSWORD_LENGTH];
    char correo[MAX_PASSWORD_LENGTH];
    char telefono[MAX_PASSWORD_LENGTH];
}UsuarioDatos;


typedef struct Pelicula{
    char nom_pel_fecha[MAX_PASSWORD_LENGTH];
    char fecha[MAX_PASSWORD_LENGTH];
}Pelicula;

typedef struct Horario{
    char nom_pel_horario[MAX_PASSWORD_LENGTH];
    char HoraInicio[MAX_PASSWORD_LENGTH];
    char HoraFin[MAX_PASSWORD_LENGTH];
}Horario;

#endif