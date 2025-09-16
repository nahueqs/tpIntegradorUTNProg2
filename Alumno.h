#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED

#include "Persona.h"

class Alumno : public Persona {
private:
    int legajo;
    Fecha fechaInscripcion;

public:
    Alumno(int leg = 0, Fecha fI = Fecha());

    void setLegajo(int l);
    int getLegajo();

    void Cargar() override;
    void Mostrar() override;
};

#endif // ALUMNO_H_INCLUDED
