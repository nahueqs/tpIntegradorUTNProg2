#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include "Fecha.h"

class Persona {
protected:
    int _legajo;
    int _dni;
    char _nombre[50];
    char _apellido[50];
    int _telefono;
    char _direccion[200];
    Fecha _fechaNacimiento;
    char _email[50];
    bool _estado;

public:
    Persona(int l = 0, int d = 0, const char *nom = "S/N", const char *ape = "S/A",
            int tel = 0, const char *dir = "S/D", const char *mail = "S/E",
            bool est = true, Fecha fN = Fecha());

    /// GETTERS (IMPORTANTE: con const)
    int getLegajo() const;
    int getDni() const;
    const char* getNombre() const;
    const char* getApellido() const;
    int getTelefono() const;
    const char* getDireccion() const;
    const char* getEmail() const;
    bool getEstado() const;
    Fecha getFechaNacimiento() const;

    /// SETTERS
    void setLegajo(int valor);
    void setDni(int valor);
    void setNombre(const char* valor);
    void setApellido(const char* valor);
    void setTelefono(int valor);
    void setDireccion(const char* valor);
    void setFechaNacimiento(Fecha fecha);
    void setEmail(const char* valor);
    void setEstado(bool valor);

    /// MÉTODOS
    virtual void Cargar();
    virtual void Mostrar();
};

#endif // PERSONA_H_INCLUDED
