#ifndef ALUMNO_H_INCLUDED
#define ALUMNO_H_INCLUDED
#include "Persona.h"

class Alumno : public Persona {
private:
    int _legajoAlumno;

public:
    // --- Constructores ---
    Alumno(); // Constructor vacío

    // Constructor parametrizado
    // Nota: Acepta todos los params de Persona + los de Alumno
    Alumno(int d, const char *nom, const char *ape,
           int tel, const Direccion &dir, const char *mail,
           bool est, Fecha fN,
           int legajo); // Parámetro propio de Alumno

    // --- Setters y Getters ---
    void setLegajoAlumno(int legajo);
    int getLegajoAlumno() const;

    // --- Métodos Sobrescritos ---
    // Usamos 'override' para asegurar que estamos sobrescribiendo
    // un método virtual de la clase base
    void Cargar() override;
    void Mostrar() override;
};

#endif // ALUMNO_H_INCLUDED
