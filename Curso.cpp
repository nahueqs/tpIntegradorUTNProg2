#include "Curso.h"
#include <iostream>
#include <cstring>

using namespace std;

Curso::Curso() {
    _idCurso = 0;
    _legajoDocenteACargo = 0;
    strcpy(_descripcionCurso, "");
    _numAula = 0;
    _maxAlumnos = 0;
    _anio = 0;
    _costoMatricula = 0.0f;
    _estado = false;
}


Curso::Curso(int id, int legajoDoc, const char* desc, int numAula, int maxAlu, int anio, float costo, bool estado) {

    setIdCurso(id);
    setLegajoDocente(legajoDoc);
    setDescripcion(desc);
    setNumAula(numAula);
    setMaxAlumnos(maxAlu);
    setAnio(anio);
    setCostoMatricula(costo);
    setEstado(estado);
}

//// setters

void Curso::setIdCurso(int id) { _idCurso = id; }

void Curso::setLegajoDocente(int legajo) { _legajoDocenteACargo = legajo; }

void Curso::setDescripcion(const char* descripcion) {
    strncpy(_descripcionCurso, descripcion, 99);
    _descripcionCurso[99] = '\0';
}

bool Curso::setNumAula(int num) {
    if (num <= 0) {
        return false;
    }
    _numAula = num;
    return true;
}

bool Curso::setMaxAlumnos(int max) {
    if (max <= 0) {
        return false;
    }
    _maxAlumnos = max;
    return true;
}

bool Curso::setAnio(int anio) {
    if (anio < 2020 || anio > 2030) {
        return false;
    }
    _anio = anio;
    return true;
}

bool Curso::setCostoMatricula(float costo) {
    if (costo < 0) {
        return false;
    }
    _costoMatricula = costo;
    return true;
}

void Curso::setEstado(bool estado) { _estado = estado; }

/// ggetters
int Curso::getIdCurso() const { return _idCurso; }
int Curso::getLegajoDocente() const { return _legajoDocenteACargo; }
const char* Curso::getDescripcion() const { return _descripcionCurso; }
int Curso::getNumAula() const { return _numAula; }
int Curso::getMaxAlumnos() const { return _maxAlumnos; }
int Curso::getAnio() const { return _anio; }
float Curso::getCostoMatricula() const { return _costoMatricula; }
bool Curso::getEstado() const { return _estado; }


/// cargar msotrar
bool Curso::Cargar() {
    char descTemporal[100];
    int intTemporal;
    float floatTemporal;

    while (true) {
        cout << "Ingrese Numero de Aula (o 0 para cancelar): " << endl;

        if (cin >> intTemporal) { /// pd: como en persona esta explicado ahi

            if (intTemporal == 0) {
                return false;
            }


            if (setNumAula(intTemporal)) {
                break;
            } else {
                cout << "*** ERROR: El numero de aula debe ser positivo ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numero ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cin.ignore(10000, '\n');
    cout << "Ingrese Descripcion del Curso: " << endl;
    cin.getline(descTemporal, 100);
    setDescripcion(descTemporal);

    while (true) {
        cout << "Ingrese Capacidad Maxima de Alumnos: " << endl;
        if (cin >> intTemporal) {
            if (setMaxAlumnos(intTemporal)) {
                break;
            } else {
                cout << "*** ERROR: La capacidad debe ser positiva ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    while (true) {
        cout << "Ingrese Anio (ej. 2024): " << endl;
        if (cin >> intTemporal) {
            if (setAnio(intTemporal)) {
                break;
            } else {
                cout << "*** ERROR: El anio debe ser entre 2020 y 2030. ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    while (true) {
        cout << "Ingrese Costo de Matricula: " << endl;
        if (cin >> floatTemporal) {
            if (setCostoMatricula(floatTemporal)) {
                break;
            } else {
                cout << "*** ERROR: El costo no puede ser negativo. ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    cin.ignore(10000, '\n');

    return true;
}

void Curso::Mostrar() {
    cout << "ID Curso: " << _idCurso << endl;
    cout << "Descripcion: " << _descripcionCurso << endl;
    cout << "Docente a Cargo (Legajo): " << _legajoDocenteACargo << endl;
    cout << "Aula Nro: " << _numAula << endl;
    cout << "Anio: " << _anio << endl;
    cout << "Costo Matricula: $" << _costoMatricula << endl;
    cout << "Capacidad Maxima: " << _maxAlumnos << endl;
    if(_estado) {
        cout << "Estado : Activo" << endl;
    }else {cout << "Estado : Inactivo"<< endl;}
}
