#ifndef _STRUCT_H_
#define _STRUCT_H_
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


typedef struct Usuario {
    char nombreUsuario[MAX_USERNAME_LENGTH];
    char contraseyna[MAX_PASSWORD_LENGTH];
    
}Usuario;

typedef struct {
  char *nombreUsuario;
  char *dni;
  char *correo;
  char *tlf;
} UsuarioDatos;


typedef struct{
    char *nom_pel_fecha;
    char *fecha;
}PeliculaFecha;

typedef struct{
    int id;
    char *nom_pel;
    char *genero_pel;
    char *duracion;
}Pelicula;

typedef struct Horario{
    char *nom_pel_horario;
    char *HoraInicio;
    char *HoraFin;
}Horario;

typedef struct{
    char *dia;
    int seleccion;
}Seleccion;

#endif