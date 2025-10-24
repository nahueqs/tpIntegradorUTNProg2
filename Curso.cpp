#include "Curso.h"
#include <cstring>
#include <iostream>

using namespace std;

// Constructor
Curso::Curso(int id, int legajoDoc, const char* desc, int aula,
             int cantInsc, Fecha anio, int maxAlum, float costo, bool est)
    : _idCurso(id), _legajoDocenteACargo(legajoDoc), _numAula(aula),
      _cantInscriptos(cantInsc), _anio(anio), _maxAlumnos(maxAlum),
      _costoMatricula(costo), _estado(est) {
    strncpy(_descripcionCurso, desc, 99);
    _descripcionCurso[99] = '\0';
}

// GETTERS
int Curso::getIdCurso() const {
    return _idCurso;
}

int Curso::getLegajoDocenteACargo() const {
    return _legajoDocenteACargo;
}

const char* Curso::getDescripcionCurso() const {
    return _descripcionCurso;
}

int Curso::getNumAula() const {
    return _numAula;
}

int Curso::getCantInscriptos() const {
    return _cantInscriptos;
}

Fecha Curso::getAnio() const {
    return _anio;
}

int Curso::getMaxAlumnos() const {
    return _maxAlumnos;
}

float Curso::getCostoMatricula() const {
    return _costoMatricula;
}

bool Curso::getEstado() const {
    return _estado;
}

// SETTERS
void Curso::setIdCurso(int valor) {
    _idCurso = valor;
}

void Curso::setLegajoDocenteACargo(int valor) {
    _legajoDocenteACargo = valor;
}

void Curso::setDescripcionCurso(const char* valor) {
    strncpy(_descripcionCurso, valor, 99);
    _descripcionCurso[99] = '\0';
}

void Curso::setNumAula(int valor) {
    _numAula = valor;
}

void Curso::setCantInscriptos(int valor) {
    _cantInscriptos = valor;
}

void Curso::setAnio(Fecha valor) {
    _anio = valor;
}

void Curso::setMaxAlumnos(int valor) {
    _maxAlumnos = valor;
}

void Curso::setCostoMatricula(float valor) {
    _costoMatricula = valor;
}

void Curso::setEstado(bool valor) {
    _estado = valor;
}

// MÉTODOS
void Curso::Cargar() {
    cout << "\n=== CARGAR CURSO ===\n";

    cout << "Ingrese ID del curso: ";
    cin >> _idCurso;

    cout << "Ingrese legajo del docente a cargo: ";
    cin >> _legajoDocenteACargo;

    cin.ignore();
    cout << "Ingrese descripcion del curso: ";
    cin.getline(_descripcionCurso, 100);

    cout << "Ingrese numero de aula: ";
    cin >> _numAula;

    cout << "Ingrese cantidad maxima de alumnos: ";
    cin >> _maxAlumnos;

    cout << "Ingrese costo de matricula: $";
    cin >> _costoMatricula;

    cout << "Ingrese anio del curso: ";
    int anio;
    cin >> anio;
    _anio = Fecha(1, 1, anio); // Solo nos importa el año

    _cantInscriptos = 0; // Comienza sin inscriptos
    _estado = true; // Por defecto activo

    cout << "Curso cargado exitosamente.\n";
}

void Curso::Mostrar() {
    cout << "\n=== DATOS DEL CURSO ===\n";
    cout << "ID Curso: " << _idCurso << endl;
    cout << "Descripcion: " << _descripcionCurso << endl;
    cout << "Docente (legajo): " << _legajoDocenteACargo << endl;
    cout << "Aula: " << _numAula << endl;
    cout << "Inscriptos: " << _cantInscriptos << "/" << _maxAlumnos << endl;
    cout << "Anio: " << _anio.getAnio() << endl;
    cout << "Costo Matricula: $" << _costoMatricula << endl;
    cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << endl;

    if (tieneCupoDisponible()) {
        cout << "CUPOS DISPONIBLES: " << (_maxAlumnos - _cantInscriptos) << endl;
    } else {
        cout << "CURSO COMPLETO" << endl;
    }
}

bool Curso::tieneCupoDisponible() {
    return _cantInscriptos < _maxAlumnos && _estado;
}

void Curso::incrementarInscriptos() {
    if (_cantInscriptos < _maxAlumnos) {
        _cantInscriptos++;
    }
}

void Curso::decrementarInscriptos() {
    if (_cantInscriptos > 0) {
        _cantInscriptos--;
    }
}
