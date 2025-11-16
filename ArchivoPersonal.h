#pragma once
#include "Personal.h"
#include <iostream>

class ArchivoPersonal {
private:
    char _nombre[30];


public:
    // Constructor
    ArchivoPersonal(const char* nombre);


    int contarRegistros();
    bool grabarRegistro(Personal obj);
    Personal leerRegistro(int pos);
    bool modificarRegistro(Personal obj, int pos);

    /// Legajos
    int generarNuevoLegajo();
    int generarNuevoLegajoDocente();

    //// busquedas
    int buscarPorLegajo(int legajo);
    int buscarPorDni(int dni);
    int buscarPorLegajoDocente(int legajoDocente);

    //// alta, baja, modificar y reactivar el alta
    void darDeAlta();
    void darDeBaja();
    void modificar();
    void reactivar();

    /// consultas
    void consultarPorLegajo();
    void consultarPorLegajoDocente();

    /// listados
    void listarPorLegajoDocente(); /// ordenados por el legajo docente
    void listarPorLegajo(); /// ordenados por el legajo personal, lista todos
    void listarPorCargo();   /// ordenados por cargo
    void listarPorTurno(); /// ordenados por turno primero ma;ana despues tarde y ultimo noche
    void listarInactivos(); /// ordenados por turnos maniana tarde noche
};
