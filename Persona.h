#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include <iostream>
#include <cstring>
#include "clsFecha.h"
#include "clsDomicilio.h"

class Persona {
protected:
    char nombre[30];
    char apellido[30];
    int dni;
    Fecha fechaNacimiento;
    Domicilio domicilio;
    char email[40];

public:
    Persona(const char *nom = "S/N", const char *ape = "S/A", int d = 0,
            Fecha fN = Fecha(), const char *mail = "S/E");

    // SETTERS
    void setNombre(const char *n);
    void setApellido(const char *a);
    void setDni(int d);
    void setFechaNacimiento(Fecha f);
    void setEmail(const char *mail);

    // GETTERS
    const char* getNombre();
    const char* getApellido();
    int getDni();
    Fecha getFechaNacimiento();
    const char* getEmail();

    // Métodos
    virtual void Cargar();
    virtual void Mostrar();
};

#endif // PERSONA_H_INCLUDED
