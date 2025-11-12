#pragma once
#include <string>
#include "Fecha.h"

class Inscripcion {
private:
    // --- Atributos Privados ---
    int _idInscripcion;
    int _legajoAlumno;
    int _idCurso;
    Fecha _fechaInscripcion;
    int _importeMatricula;
    bool _matriculaPaga;
    bool _estado;

public:
    // --- Constructores (solo declarados) ---
    Inscripcion();
    Inscripcion(int legajo, int idInsc, int idCurso, int dia, int mes, int anio, int importe, bool paga, bool estado);

    // --- Setters (solo declarados) ---
    void setLegajoAlumno(int legajo);
    void setIdInscripcion(int id);
    void setIdCurso(int id);
    void setFechaInscripcion(const Fecha& fecha);
    void setImporteMatricula(int importe);
    void setMatriculaPaga(bool paga);
    void setEstado(bool estado);

    // --- Getters (solo declarados) ---
    int getLegajoAlumno() const;
    int getIdInscripcion() const;
    int getIdCurso() const;
    Fecha getFechaInscripcion() const;
    int getImporteMatricula() const;
    bool getMatriculaPaga() const;
    bool getEstado() const;

    // mstrar cargar
    void mostar();
    void cargar();
};
