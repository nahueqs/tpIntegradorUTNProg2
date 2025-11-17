#include <iostream>
#include <cstring>
#include "Direccion.h"

/// constructores
Direccion::Direccion()
    : _numero(0)
{
    strcpy(_calle, "S/C");
    strcpy(_piso, "S/P");
    strcpy(_depto, "S/D");
    strcpy(_localidad, "S/L");
    strcpy(_codigoPostal, "S/CP");
}


Direccion::Direccion(const char *calle, int num, const char *piso,
                     const char *depto, const char *loc, const char *cp)
    : _numero(num)
{
    strcpy(_calle, calle);
    strcpy(_piso, piso);
    strcpy(_depto, depto);
    strcpy(_localidad, loc);
    strcpy(_codigoPostal, cp);
}

/// setters
void Direccion::setCalle(const char *calle) {
strcpy(_calle, calle);
}

void Direccion::setNumero(int num) {
     _numero = num;
}

void Direccion::setPiso(const char *piso) {
    strcpy(_piso, piso);
}
void Direccion::setDepto(const char *depto) {
strcpy(_depto, depto);
}

void Direccion::setLocalidad(const char *loc) {
     strcpy(_localidad, loc);
}

void Direccion::setCodigoPostal(const char *cp) {
     strcpy(_codigoPostal, cp);
}

/// getters
const char* Direccion::getCalle() const {
    return _calle;
}

int Direccion::getNumero() const {
    return _numero;
}

const char* Direccion::getPiso() const {
    return _piso;
}

const char* Direccion::getDepto() const {
    return _depto;
}

const char* Direccion::getLocalidad() const {
    return _localidad;
}

const char* Direccion::getCodigoPostal() const {
    return _codigoPostal;
}

 /// metodos
void Direccion::Cargar() {
    std::cout << "Calle: ";
    std::cin.getline(_calle, 100);
    std::cout << "Numero: ";
    std::cin >> _numero;
    std::cin.ignore();
    std::cout << "Piso (o PB): ";
    std::cin.getline(_piso, 10);
    std::cout << "Depto: ";
    std::cin.getline(_depto, 10);
    std::cout << "Localidad: ";
    std::cin.getline(_localidad, 50);
    std::cout << "Codigo Postal: ";
    std::cin.getline(_codigoPostal, 10);
}

void Direccion::Mostrar() {

    std::cout << _calle << " " << _numero;
    if (strcmp(_piso, "") != 0 && strcmp(_piso, "S/P") != 0) {
        std::cout << ", Piso " << _piso;
    }
    if (strcmp(_depto, "") != 0 && strcmp(_depto, "S/D") != 0) {
        std::cout << ", Depto " << _depto;
    }
    std::cout << std::endl;
    std::cout << _localidad << " (" << _codigoPostal << ")" << std::endl;
}
