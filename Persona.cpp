#include "Persona.h"
#include <cstring>
#include <iostream>

using namespace std;

// Constructor CORREGIDO - Ahora sí copia los strings
Persona::Persona(int l, int d, const char *nom, const char *ape,
                 int tel, const char *dir, const char *mail,
                 bool est, Fecha fN) :
                 _legajo(l), _dni(d), _telefono(tel), _fechaNacimiento(fN), _estado(est) {
    // Copiar los char* de forma segura
    strncpy(_nombre, nom, 49);
    _nombre[49] = '\0';

    strncpy(_apellido, ape, 49);
    _apellido[49] = '\0';

    strncpy(_direccion, dir, 199);
    _direccion[199] = '\0';

    strncpy(_email, mail, 49);
    _email[49] = '\0';
}

/// GETTERS

int Persona::getLegajo() const {
    return _legajo;
}

int Persona::getDni() const {
    return _dni;
}

const char* Persona::getNombre() const {
    return _nombre;
}

const char* Persona::getApellido() const {
    return _apellido;
}

int Persona::getTelefono() const {
    return _telefono;
}

const char* Persona::getDireccion() const {
    return _direccion;
}

const char* Persona::getEmail() const {
    return _email;
}

bool Persona::getEstado() const {
    return _estado;
}

Fecha Persona::getFechaNacimiento() const {
    return _fechaNacimiento;
}

/// SETTERS

void Persona::setLegajo(int valor) {
    _legajo = valor;
}

void Persona::setDni(int valor) {
    _dni = valor;
}

void Persona::setNombre(const char* valor) {
    strncpy(_nombre, valor, 49);
    _nombre[49] = '\0';
}

void Persona::setApellido(const char* valor) {
    strncpy(_apellido, valor, 49);
    _apellido[49] = '\0';
}

void Persona::setTelefono(int valor) {
    _telefono = valor;
}

void Persona::setDireccion(const char* valor) {
    strncpy(_direccion, valor, 199);
    _direccion[199] = '\0';
}

void Persona::setFechaNacimiento(Fecha fecha) {
    _fechaNacimiento = fecha;
}

void Persona::setEmail(const char* valor) {
    strncpy(_email, valor, 49);
    _email[49] = '\0';
}

void Persona::setEstado(bool valor) {
    _estado = valor;
}

/// MÉTODOS - IMPLEMENTADOS

void Persona::Cargar() {
    cout << "Ingrese legajo: ";
    cin >> _legajo;

    cout << "Ingrese DNI: ";
    cin >> _dni;

    cin.ignore(); // Limpiar buffer antes de getline

    cout << "Ingrese nombre: ";
    cin.getline(_nombre, 50);

    cout << "Ingrese apellido: ";
    cin.getline(_apellido, 50);

    cout << "Ingrese telefono: ";
    cin >> _telefono;

    cin.ignore();

    cout << "Ingrese direccion: ";
    cin.getline(_direccion, 200);

    cout << "Ingrese email: ";
    cin.getline(_email, 50);

    cout << "Fecha de nacimiento:\n";
    int dia, mes, anio;
    cout << "Dia: ";
    cin >> dia;
    cout << "Mes: ";
    cin >> mes;
    cout << "Anio: ";
    cin >> anio;
    _fechaNacimiento = Fecha(dia, mes, anio);

    _estado = true; // Por defecto activo
}

void Persona::Mostrar() {
    cout << "Legajo: " << _legajo << endl;
    cout << "DNI: " << _dni << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Telefono: " << _telefono << endl;
    cout << "Direccion: " << _direccion << endl;
    cout << "Email: " << _email << endl;
    cout << "Fecha Nacimiento: " << _fechaNacimiento.toString() << endl;
    cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << endl;
}
