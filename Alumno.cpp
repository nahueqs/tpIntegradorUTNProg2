#include "Alumno.h"
#include <iostream>

using namespace std;

// Constructor - DEBE coincidir con el de Persona
Alumno::Alumno(int l, int d, const char *nom, const char *ape,
               int tel, const char *dir, const char *mail,
               bool est, Fecha fN)
    : Persona(l, d, nom, ape, tel, dir, mail, est, fN) {
    // Llama al constructor de Persona correctamente
}

// Métodos

void Alumno::Cargar() {
    cout << "\n=== CARGAR ALUMNO ===\n";
    Persona::Cargar(); // Usa el método de la clase base
    cout << "Alumno cargado exitosamente.\n";
}

void Alumno::Mostrar() {
    cout << "\n=== DATOS DEL ALUMNO ===\n";
    Persona::Mostrar(); // Usa el método de la clase base
}
