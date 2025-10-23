#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED

#include "Persona.h"

class Alumno : public Persona {
private:
    // No necesita legajo propio, lo hereda de Persona como _legajo

public:
    // Constructor
    Alumno(int l = 0, int d = 0, const char *nom = "S/N", const char *ape = "S/A",
           int tel = 0, const char *dir = "S/D", const char *mail = "S/E",
           bool est = true, Fecha fN = Fecha());

    // Métodos sobrescritos
    void Cargar() override;
    void Mostrar() override;
};

#endif // ALUMNO_H_INCLUDED
