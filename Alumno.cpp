#include "Alumno.h"
#include <iostream>
#include <cstring>

using namespace std;

// Constructor
Alumno::Alumno(int l, int d, const char *nom, const char *ape,
               int tel, const char *dir, const char *mail,
               bool est, Fecha fN)
    : Persona(l, d, nom, ape, tel, dir, mail, est, fN) {
    // Llama al constructor de Persona correctamente
}

// Métodos

void Alumno::Cargar() {
    cout << "\n=== CARGAR ALUMNO ===\n";

    // Validación de legajo (básica - la validación de unicidad se hace en el main)
    int legajo;
    do {
        cout << "Ingrese legajo (mayor a 0): ";
        cin >> legajo;
        if (legajo <= 0) {
            cout << "*** ERROR: El legajo debe ser mayor a 0 ***\n";
        }
    } while (legajo <= 0);
    setLegajo(legajo);

    // Validación de DNI (básica)
    int dni;
    do {
        cout << "Ingrese DNI (7-8 digitos): ";
        cin >> dni;
        if (dni < 1000000 || dni > 99999999) {
            cout << "*** ERROR: El DNI debe tener entre 7 y 8 digitos ***\n";
        }
    } while (dni < 1000000 || dni > 99999999);
    setDni(dni);

    cin.ignore(); // Limpiar buffer

    // Nombre
    char nombre[50];
    do {
        cout << "Ingrese nombre: ";
        cin.getline(nombre, 50);
        if (strlen(nombre) == 0) {
            cout << "*** ERROR: El nombre no puede estar vacio ***\n";
        }
    } while (strlen(nombre) == 0);
    setNombre(nombre);

    // Apellido
    char apellido[50];
    do {
        cout << "Ingrese apellido: ";
        cin.getline(apellido, 50);
        if (strlen(apellido) == 0) {
            cout << "*** ERROR: El apellido no puede estar vacio ***\n";
        }
    } while (strlen(apellido) == 0);
    setApellido(apellido);

    // Teléfono
    int telefono;
    cout << "Ingrese telefono: ";
    cin >> telefono;
    setTelefono(telefono);

    cin.ignore();

    // Dirección
    char direccion[200];
    cout << "Ingrese direccion: ";
    cin.getline(direccion, 200);
    setDireccion(direccion);

    // Email
    char email[50];
    cout << "Ingrese email: ";
    cin.getline(email, 50);
    setEmail(email);

    // Fecha de nacimiento
    cout << "Fecha de nacimiento:\n";
    int dia, mes, anio;
    do {
        cout << "Dia (1-31): ";
        cin >> dia;
    } while (dia < 1 || dia > 31);

    do {
        cout << "Mes (1-12): ";
        cin >> mes;
    } while (mes < 1 || mes > 12);

    do {
        cout << "Anio (1900-2024): ";
        cin >> anio;
    } while (anio < 1900 || anio > 2024);

    setFechaNacimiento(Fecha(dia, mes, anio));
    setEstado(true); // Por defecto activo

    cout << "\nDatos cargados correctamente.\n";
}

void Alumno::Mostrar() {
    cout << "\n=== DATOS DEL ALUMNO ===\n";
    Persona::Mostrar(); // Usa el método de la clase base
}
