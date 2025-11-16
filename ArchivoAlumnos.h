#ifndef ARCHIVOALUMNOS_H_INCLUDED
#define ARCHIVOALUMNOS_H_INCLUDED

#include "Alumno.h"

class ArchivoAlumnos {
private:
    char nombre[30];

public:
    ArchivoAlumnos(const char *n = "Alumnos.dat");

    // metodos basicos
    int contarRegistros();
    Alumno leerRegistro(int pos);
    bool grabarRegistro(Alumno obj);
    bool modificarRegistro(Alumno obj, int pos);
    int generarNuevoLegajo();

    // busquedas
    int buscarPorLegajo(int legajo);
    int buscarPorDni(int dni);

    // validacinoes
    bool existeLegajo(int legajo);
    bool existeDni(int dni);
    bool validarLegajoUnico(int legajo);
    bool validarDniUnico(int dni);

    // listados
    void listar();
    void listarInactivos();
    void listarPorApellido();
    void listarPorDni();
    void listarPorLegajo();

    /// Consultas
    void consultarPorLegajo();

    // ALTA Y BAJA
    void altaAlumno();
    void bajaAlumno();
    void reactivarAlumno();

    // MODIFICACIONES
    void modificar();

    /// MODIFICAICONES

};

#endif
