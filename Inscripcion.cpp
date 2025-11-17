#include "Inscripcion.h"
#include <iostream>
#include <cstring>

using namespace std;


Inscripcion::Inscripcion() {
    _idInscripcion = 0;
    _legajoAlumno = 0;
    _idCurso = 0;
    _importeMatricula = 0.0f;
    _totalPagado = 0.0f;
    _matriculaPaga = false;
    _estado = false;
}


void Inscripcion::setIdInscripcion(int id) { _idInscripcion = id; }

bool Inscripcion::setLegajoAlumno(int legajo) {
    if (legajo > 0) {
        _legajoAlumno = legajo;
        return true;
    }
    return false;
}

bool Inscripcion::setIdCurso(int id) {
    if (id > 0) {
        _idCurso = id;
        return true;
    }
    return false;
}
/// settters
void Inscripcion::setFechaInscripcion(Fecha fecha) { _fechaInscripcion = fecha; }
void Inscripcion::setImporteMatricula(float importe) { _importeMatricula = importe; }
void Inscripcion::setMatriculaPaga(bool pagada) { _matriculaPaga = pagada; }
void  Inscripcion::setTotalPagado(float pagado) {_totalPagado = pagado; }
void Inscripcion::setEstado(bool estado) { _estado = estado; }


/// getters
int Inscripcion::getIdInscripcion() const { return _idInscripcion; }
int Inscripcion::getLegajoAlumno() const { return _legajoAlumno; }
int Inscripcion::getIdCurso() const { return _idCurso; }
Fecha Inscripcion::getFechaInscripcion() const { return _fechaInscripcion; }
float Inscripcion::getImporteMatricula() const { return _importeMatricula; }
bool Inscripcion::getMatriculaPaga() const { return _matriculaPaga; }
float Inscripcion::getTotalPagado() const { return _totalPagado; }
bool Inscripcion::getEstado() const { return _estado; }

/// cargar mostrar

bool Inscripcion::Cargar() {
    int legajoTemporal;
    int idTemporal;


    while (true) {
        cout << "Ingrese Legajo del Alumno (o 0 para cancelar): " << endl;
        if (cin >> legajoTemporal) {
            if (legajoTemporal == 0) {
                return false;
            }
            if (setLegajoAlumno(legajoTemporal)) {
                break;
            } else {
                cout << "*** ERROR: El legajo debe ser un numero positivo. ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }


    while (true) {
        cout << "Ingrese ID del Curso (o 0 para cancelar): " << endl;
        if (cin >> idTemporal) {
            if (idTemporal == 0) {
                return false;
            }
            if (setIdCurso(idTemporal)) {
                break;
            } else {
                cout << "*** ERROR: El ID del curso debe ser un numero positivo. ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }


    cout << "--- Ingresando Fecha de Inscripcion ---" << endl;
    _fechaInscripcion.Cargar();

    cin.ignore(10000, '\n');
    return true;
}

void Inscripcion::Mostrar() {
    cout << "ID Inscripcion: " << _idInscripcion << endl;
    cout << "Legajo Alumno: " << _legajoAlumno << endl;
    cout << "ID Curso: " << _idCurso << endl;
    cout << "Fecha de Inscripcion: ";
    _fechaInscripcion.Mostrar();
    cout << endl;
    cout << "Importe Matricula: $" << _importeMatricula << endl;
    cout << "Importe Pagado :  $ " << _totalPagado << endl;
    cout << "Matricula Pagada: " << (_matriculaPaga ? "SI" : "NO") << endl;
    cout << "Estado: " << (_estado ? "Activa" : "Inactiva") << endl;
}


