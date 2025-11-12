#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED
#include "Persona.h"

class Alumno : public Persona {
private:
    int _legajoAlumno;

public:

    Alumno();


    Alumno(int d, const char *nom, const char *ape,
           int tel, const Direccion &dir, const char *mail,
           bool est, Fecha fN,
           int legajo);

    void setLegajoAlumno(int legajo);
    int getLegajoAlumno() const;


    void Cargar() override;
    void Mostrar() override;
};

#endif // ALUMNO_H_INCLUDED
