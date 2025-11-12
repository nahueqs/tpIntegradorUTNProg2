#include <iostream>
#include <cstring>
#include <string>
#include "Persona.h"
#include "Fecha.h"
#include "Direccion.h"

using namespace std;


Persona::Persona()
    : _dni(0),
      _telefono(0),
      _direccion(),       // Llama al constructor vacío de Direccion
      _fechaNacimiento(), // Llama al constructor vacío de Fecha
      _estado(true)
{
   /// ponemos los nombres como "vacios"
    strcpy(_nombre, "S/N");
    strcpy(_apellido, "S/A");
    strcpy(_email, "S/E");
}


Persona::Persona(int d, const char *nom, const char *ape,
                 int tel, const Direccion &dir,
                 const char *mail, bool est, Fecha fN)
    : _dni(d),
      _telefono(tel),
      _direccion(dir),
      _fechaNacimiento(fN),
      _estado(est)
{
    //aca usamos la funcion del strcpy para copiar los punteros al array del char
    strcpy(_nombre, nom);
    strcpy(_apellido, ape);
    strcpy(_email, mail);
}

///getters

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

Direccion Persona::getDireccion() const {
    return _direccion;
}

const char* Persona::getEmail() const {
    return _email;
}

bool Persona::getEstado() const {
    return _estado;
}

Fecha Persona::getFechaNacimiento(){
    return _fechaNacimiento;
}

/// setters

void Persona::setDni(int valor) {
    _dni = valor;
}

void Persona::setNombre(const char* valor) {
    strcpy(_nombre, valor);
}

void Persona::setApellido(const char* valor) {
    strcpy(_apellido, valor);
}

void Persona::setTelefono(int valor) {
    _telefono = valor;
}

void Persona::setDireccion(const Direccion &valor) {
    _direccion = valor;
}

void Persona::setFechaNacimiento(Fecha fecha) {
    _fechaNacimiento = fecha;
}

void Persona::setEmail(const char* valor) {
    strcpy(_email, valor);
}

void Persona::setEstado(bool valor) {
    _estado = valor;
}

/// metodos

void Persona::Cargar() {
    cout << "Ingrese DNI: ";
    cin >> _dni;
    cout << "Ingrese Nombre: ";
    cin.ignore(); // Limpia el buffer después de leer un int
    cin.getline(_nombre, 50);
    cout << "Ingrese Apellido: ";
    cin.getline(_apellido, 50);
    cout << "Ingrese Telefono: ";
    cin >> _telefono;
    cin.ignore();

    cout << "--- Cargando Direccion ---" << endl;
    _direccion.Cargar(); // DELEGAMOS la carga a la clase Direccion

    cout << "Ingrese Email: ";
    cin.getline(_email, 50);

    cout << "--- Cargando Fecha de Nacimiento ---" << endl;
    _fechaNacimiento.Cargar(); // DELEGAMOS la carga a la clase Fecha

    // Limpiamos el buffer después del último cin >> de Fecha::Cargar()
    cin.ignore();

    _estado = true;
}

void Persona::Mostrar() {
    cout << "DNI: " << _dni << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Telefono: " << _telefono << endl;
    cout << "Email: " << _email << endl;

    cout << "--- Direccion ---" << endl;
    _direccion.Mostrar(); // DELEGAMOS la muestra a la clase Direccion

    cout << "Fecha de Nacimiento: ";
    _fechaNacimiento.Mostrar(); // DELEGAMOS la muestra a la clase Fecha

    cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << endl;
}
