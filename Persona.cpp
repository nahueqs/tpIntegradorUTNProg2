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
      _direccion(),
      _fechaNacimiento(),
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
    //aca usamos la funcion del strcpy para copiar los punteros al vector del char
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

bool Persona::setDni(int dni) {

    if (dni > 100000) {
        _dni = dni;
        return true;
    }
    return false;
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

bool Persona::Cargar() {
    int dniTemporal;

    while (true) {
        cout << "Ingrese DNI (o 0 para cancelar): " << endl;

        if (cin >> dniTemporal) { /// este cin >> lo que haces es te devuelve true o false, si ingresaste un numero es true, si ingresaste alguna otra cosa es false
            if (dniTemporal == 0) {
                return false;
            }
            if (setDni(dniTemporal) == true) {
                break;
            } else {
                cout << "*** DNI no valido. Debe ser un numero positivo de 6 digitos o mas. ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. *** " << endl;;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }


    cout << "Ingrese Nombre: " << endl;
    cin.ignore(10000, '\n');
    cin.getline(_nombre, 50);
    setNombre(_nombre);

    cout << "Ingrese Apellido: " << endl;
    cin.getline(_apellido, 50);
    setApellido(_apellido);

    while (true) {
        cout << "Ingrese Telefono: " << endl;
        if (cin >> _telefono) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

        cout << "--- Cargando Direccion ---" << endl;
        if (!_direccion.Cargar()) {
            return false;
        };


    cout << "Ingrese Email: " << endl;
    cin.getline(_email, 50);


    cout << "--- Cargando Fecha de Nacimiento ---" << endl;
    _fechaNacimiento.Cargar();

    cin.ignore(10000, '\n');

    return true;
}

void Persona::Mostrar() {
    cout << "DNI: " << _dni << endl;
    cout << "Nombre: " << _nombre << endl;
    cout << "Apellido: " << _apellido << endl;
    cout << "Telefono: " << _telefono << endl;
    cout << "Email: " << _email << endl;

    cout << "--- Direccion ---" << endl;
    _direccion.Mostrar();

    cout << "Fecha de Nacimiento: ";
    _fechaNacimiento.Mostrar();

    cout << "Estado: " << (_estado ? "Activo" : "Inactivo") << endl;
}
