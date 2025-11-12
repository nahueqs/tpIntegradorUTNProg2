#ifndef ARCHIVOALUMNOS_H_INCLUDED
#define ARCHIVOALUMNOS_H_INCLUDED

#include "Alumno.h"

class ArchivoAlumnos {
private:
    char nombre[30];

public:
    ArchivoAlumnos(const char *n = "Alumnos.dat");

    // MÉTODOS BÁSICOS
    int contarRegistros();
    Alumno leerRegistro(int pos);
    bool grabarRegistro(Alumno obj);
    bool modificarRegistro(Alumno obj, int pos);
    int generarNuevoLegajo();

    // BÚSQUEDAS
    int buscarPorLegajo(int legajo);
    int buscarPorDni(int dni);

    // VALIDACIONES
    bool existeLegajo(int legajo);
    bool existeDni(int dni);
    bool validarLegajoUnico(int legajo);
    bool validarDniUnico(int dni);

    // LISTADOS
    void listar();
    void listarActivos();
    void listarPorApellido();
    void listarPorDni();
    void listarSinOrdenar();

    /// MODIFICAICONES

};

#endif
