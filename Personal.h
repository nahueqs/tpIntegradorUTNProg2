#pragma once
#include "Persona.h"
#include <string>



class Personal : public Persona {
private:

    int _legajo;
    bool _turnos[3];  // 0 mañana, 1 tarde, 2 noche

    // 1: Director
    // 2: Preceptor
    // 3: Limpieza
    // 4: Docente
    // 0: nada/ indefinido
    int _cargo;


    int _legajoDocente;

public:
    Personal();

    /// setters
    void setLegajo(int legajo);
    void setTurno(int indice, bool valor);
    void setCargo(int cargo);
    void setLegajoDocente(int legajo);

    /// getters
    int getLegajo() const;
    bool getTurno(int indice) const;
    int getCargo() const;
    int getLegajoDocente() const;


    std::string getTurnosComoTexto() const;
    std::string getCargoComoTexto() const;

    bool Cargar();
    void Mostrar();
};
