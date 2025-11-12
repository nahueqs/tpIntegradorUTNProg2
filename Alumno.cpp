#include <iostream>
#include "Alumno.h"


using namespace std;

// --- Implementación de Constructores ---

/**
 * Constructor Vacío
 * Llama al constructor vacío de Persona() e inicializa el legajo en 0.
 */
Alumno::Alumno()
    : Persona(), // Llama a Persona()
      _legajoAlumno(0)
{
    // El cuerpo queda vacío
}

/**
 * Constructor Parametrizado
 * Pasa todos los datos de Persona al constructor de Persona
 * e inicializa los miembros propios de Alumno.
 */
Alumno::Alumno(int d, const char *nom, const char *ape,
               int tel, const Direccion &dir, const char *mail,
               bool est, Fecha fN,
               int legajo)
    : Persona(d, nom, ape, tel, dir, mail, est, fN), // Llama a Persona(...)
      _legajoAlumno(legajo) // Inicializa el miembro propio
{
    // El cuerpo queda vacío
}


// --- Implementación de Setters y Getters ---

void Alumno::setLegajoAlumno(int legajo) {
    // Aquí podrías añadir validación, ej: if(legajo > 0)
    _legajoAlumno = legajo;
}

int Alumno::getLegajoAlumno() const {
    return _legajoAlumno;
}


// --- Implementación de Métodos Sobrescritos ---

/**
 * Carga primero todos los datos de Persona y
 * luego pide los datos propios de Alumno.
 */
void Alumno::Cargar() {
    // 1. Llama al Cargar() de la clase base
    Persona::Cargar();

    // 2. Pide solo los datos propios de Alumno
    int tempLegajo;
    cout << "Ingrese Legajo: ";
    cin >> tempLegajo;
    setLegajoAlumno(tempLegajo); // Usamos el setter

    // Limpiamos el buffer por si se usa un getline() después
    cin.ignore();
}

/**
 * Muestra primero todos los datos de Persona y
 * luego muestra los datos propios de Alumno.
 */
void Alumno::Mostrar() {
    // 1. Llama al Mostrar() de la clase base
    Persona::Mostrar();

    // 2. Muestra solo los datos propios de Alumno
    cout << "Legajo: " << getLegajoAlumno() << endl;
}
