#include "Asistencia.h"
#include <iostream>

using namespace std;


Asistencia::Asistencia() {
    _legajoAlumno = 0;
    _idCurso = 0;
    _presente = false;
    _estado = false;
}



bool Asistencia::setLegajoAlumno(int legajo) {
    if (legajo > 0) {
        _legajoAlumno = legajo;
        return true;
    }
    return false;
}

bool Asistencia::setIdCurso(int id) {
    if (id > 0) {
        _idCurso = id;
        return true;
    }
    return false;
}

void Asistencia::setFecha(Fecha f) {
    _fecha = f;
}

void Asistencia::setPresente(bool p) {
    _presente = p;
}

void Asistencia::setEstado(bool e) {
    _estado = e;
}


int Asistencia::getLegajoAlumno() const {
    return _legajoAlumno;
}

int Asistencia::getIdCurso() const {
    return _idCurso;
}

Fecha Asistencia::getFecha() const {
    return _fecha;
}

bool Asistencia::getPresente() const {
    return _presente;
}

bool Asistencia::getEstado() const {
    return _estado;
}

// --- Mostrar ---

void Asistencia::Mostrar() {
    cout << "Legajo Alumno: " << _legajoAlumno << endl;
    cout << "ID Curso:      " << _idCurso << endl;
    cout << "Fecha:         ";
    _fecha.Mostrar();
    cout << endl;

    if (_presente) {
        cout << "Condicion:     PRESENTE" << endl;
    } else {
        cout << "Condicion:     AUSENTE" << endl;
    }
}
