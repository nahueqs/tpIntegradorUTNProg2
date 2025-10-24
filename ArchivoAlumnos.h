#ifndef ARCHIVOALUMNOS_H_INCLUDED
#define ARCHIVOALUMNOS_H_INCLUDED

#include "Alumno.h"

class ArchivoAlumnos {
private:
    char nombre[30];
public:
    ArchivoAlumnos(const char *n = "Alumnos.dat");

    int contarRegistros();
    int buscarPorLegajo(int legajo);
    Alumno leerRegistro(int pos);
    bool grabarRegistro(Alumno obj);
    bool modificarRegistro(Alumno obj, int pos);
    void listar();
};

#endif // ARCHIVOALUMNOS_H_INCLUDED
