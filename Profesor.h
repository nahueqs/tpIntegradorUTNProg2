#ifndef PROFESOR_H_INCLUDED
#define PROFESOR_H_INCLUDED

#include "Persona.h"

class Profesor : public Persona {
private:
    int legajo;
    char titulo[50];

public:
    Profesor(int leg = 0, const char *tit = "Sin titulo");

    void setLegajo(int l);
    int getLegajo();
    void setTitulo(const char *t);
    const char* getTitulo();

    void Cargar() override;
    void Mostrar() override;
};

#endif // PROFESOR_H_INCLUDED
