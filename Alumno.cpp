#include <iostream>
#include "Alumno.h"


using namespace std;




Alumno::Alumno()
    : Persona(),
      _legajoAlumno(0)
{

}


Alumno::Alumno(int d, const char *nom, const char *ape,
               int tel, const Direccion &dir, const char *mail,
               bool est, Fecha fN,
               int legajo)
    : Persona(d, nom, ape, tel, dir, mail, est, fN),
      _legajoAlumno(legajo)
{
}

void Alumno::setLegajoAlumno(int legajo) {
    _legajoAlumno = legajo;
}

int Alumno::getLegajoAlumno() const {
    return _legajoAlumno;
}

bool Alumno::Cargar() {

    if (!Persona::Cargar()) {

        return false;
    }

    return true;
}

void Alumno::Mostrar() {

    Persona::Mostrar();

    cout << "Legajo: " << getLegajoAlumno() << endl;
}
