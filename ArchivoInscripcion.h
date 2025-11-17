#pragma once
#include "Inscripcion.h"

class ArchivoInscripcion {
private:
    char _nombre[30];


public:

    ArchivoInscripcion(const char* nombre = "Inscripciones.dat");

    /// basicas
    int contarRegistros();
    bool grabarRegistro(Inscripcion obj);
    Inscripcion leerRegistro(int pos);
    bool modificarRegistro(Inscripcion obj, int pos);


    int generarNuevoIdInscripcion();

    /// bsquedas
    int buscarPorId(int id);
    int buscarInscripcionDuplicada(int legajoAlumno, int idCurso);

    //// alta, baja y cancelar si es que habia deuda
    void inscribirAlumno();
    void anularInscripcion();
    void cancelarDeuda();

    /// listadoss

    void listarPorCurso();
    void listarPorAlumno();
    void listarActivas(); /// lista todas las inscripciones
    void listarInactivas(); /// lista las bajas
    void listarArrayOrdenadoPorCurso(Inscripcion inscripciones[], int cantidad);
    //// consultas
    void consultarPorId();
    void consultarPorAlumnoYCurso();

    int contarInscriptos(int idCurso);
};
