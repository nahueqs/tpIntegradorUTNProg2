#ifndef PERSONA_H_INCLUDED
#define PERSONA_H_INCLUDED

#include "Fecha.h"
#include "Direccion.h"

class Persona {
private:
    int _dni;
    char _nombre[50];
    char _apellido[50];
    int _telefono;
    Direccion _direccion;
    Fecha _fechaNacimiento;
    char _email[50];
    bool _estado;
protected:

public:
    /// CONSTRUCTORES
    Persona();

    Persona(int d, const char *nom, const char *ape,
            int tel, const Direccion &dir,
            const char *mail, bool est, Fecha fN);

    /// GETTERS
    int getDni() const;
    const char* getNombre() const;
    const char* getApellido() const;
    int getTelefono() const;
    Direccion getDireccion() const;
    const char* getEmail() const;
    bool getEstado() const;
    Fecha getFechaNacimiento();

    /// SETTERS
    bool setDni(int valor);
    void setNombre(const char* valor);
    void setApellido(const char* valor);
    void setTelefono(int valor);
    void setDireccion(const Direccion &valor);
    void setFechaNacimiento(Fecha fecha);
    void setEmail(const char* valor);
    void setEstado(bool valor);

    /// MÉTODOS
    virtual bool Cargar();
    virtual void Mostrar();
};

#endif // PERSONA_H_INCLUDED
