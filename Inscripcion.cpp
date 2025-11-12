#include <iostream>
#include "Inscripcion.h"
using namespace std;

 // --- Definición de Constructores ---

// Constructor por defecto
Inscripcion::Inscripcion() :
    _legajoAlumno(0),
    _idInscripcion(0),
    _idCurso(0),
    _fechaInscripcion(), // Llama al constructor por defecto de Fecha
    _importeMatricula(0),
    _matriculaPaga(false),
    _estado(false)
{
    // El cuerpo queda vacío
}

// Constructor "para llenar"
Inscripcion::Inscripcion(int legajo, int idInsc, int idCurso, int dia, int mes, int anio, int importe, bool paga, bool estado) :
    _legajoAlumno(legajo),
    _idInscripcion(idInsc),
    _idCurso(idCurso),
    _fechaInscripcion(dia, mes, anio), // Llama al constructor Fecha(d,m,a)
    _importeMatricula(importe),
    _matriculaPaga(paga),
    _estado(estado)
{
    // El cuerpo queda vacío
}


// --- Definición de Setters ---

void Inscripcion::setLegajoAlumno(int legajo) {
    _legajoAlumno = legajo;
}

void Inscripcion::setIdInscripcion(int id) {
    _idInscripcion = id;
}

void Inscripcion::setIdCurso(int id) {
    _idCurso = id;
}

void Inscripcion::setFechaInscripcion(const Fecha& fecha) {
    _fechaInscripcion = fecha;
}

void Inscripcion::setImporteMatricula(int importe) {
    _importeMatricula = importe;
}

void Inscripcion::setMatriculaPaga(bool paga) {
    _matriculaPaga = paga;
}

void Inscripcion::setEstado(bool estado) {
    _estado = estado;
}


// --- Definición de Getters ---

int Inscripcion::getLegajoAlumno() const {
    return _legajoAlumno;
}

int Inscripcion::getIdInscripcion() const {
    return _idInscripcion;
}

int Inscripcion::getIdCurso() const {
    return _idCurso;
}

Fecha Inscripcion::getFechaInscripcion() const {
    return _fechaInscripcion;
}

int Inscripcion::getImporteMatricula() const {
    return _importeMatricula;
}

bool Inscripcion::getMatriculaPaga() const {
    return _matriculaPaga;
}

bool Inscripcion::getEstado() const {
    return _estado;
}


