#pragma once
#include "Asistencia.h"
#include "Fecha.h"

class ArchivoAsistencia {
private:
    char _nombre[30];

public:
    // --- Constructor ---

    ArchivoAsistencia(const char* nombre = "Asistencias.dat");
    /// basicos
    int contarRegistros();
    bool grabarRegistro(Asistencia obj);
    Asistencia leerRegistro(int pos);
    bool modificarRegistro(Asistencia obj, int pos);


    int buscarAsistencia(int legajo, int idCurso, Fecha fecha);

    /// tomar asistencia x curso y modificar 1 en es pecifiico
    void tomarAsistencia();
    void modificarAsistencia();

    /// consulta por de un aula entera en un dia especifico
    void listarPorCursoYFecha();

    // total de asistencias de un alumno en un curso
    void listarPorAlumnoYCurso();

    //// consulta esxpecfiica de un alumno en un curso y dia puntual
    void listarPorAlumnoCursoYFecha();
};
