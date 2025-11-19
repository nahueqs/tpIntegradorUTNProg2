#include <iostream>
#include <cstring>
#include "Direccion.h"
using namespace std;

/// constructores
Direccion::Direccion()
    : _numero(0)
{

    strncpy(_calle, "S/C", 3); _calle[99] = '\0';
    strncpy(_piso, "S/P", 3); _piso[9] = '\0';
    strncpy(_depto, "S/D", 3); _depto[9] = '\0';
    strncpy(_localidad, "S/L", 3); _localidad[49] = '\0';
    strncpy(_codigoPostal, "S/CP", 4); _codigoPostal[9] = '\0';
}

Direccion::Direccion(const char *calle, int num, const char *piso,
                     const char *depto, const char *loc, const char *cp)
    : _numero(num)
{

    setCalle(calle);
    setPiso(piso);
    setDepto(depto);
    setLocalidad(loc);
    setCodigoPostal(cp);
}


void Direccion::setCalle(const char *calle) {
    strncpy(_calle, calle, 99);
    _calle[99] = '\0';
}

bool Direccion::setNumero(int num) {
    if (num < 9999 && num > 0) {
      _numero = num;
      return true;
    } else {
      return false;
    }
}

void Direccion::setPiso(const char *piso) {
    strncpy(_piso, piso, 9); _piso[9] = '\0';
}

void Direccion::setDepto(const char *depto) {
    strncpy(_depto, depto, 9); _depto[9] = '\0';
}

void Direccion::setLocalidad(const char *loc) {
    strncpy(_localidad, loc, 49); _localidad[49] = '\0';
}

void Direccion::setCodigoPostal(const char *cp) {
    strncpy(_codigoPostal, cp, 9); _codigoPostal[9] = '\0';
}


bool Direccion::Cargar() {
    cin.ignore(10000, '\n');


    char tempCalle[100];
    std::cout << "Calle: ";
    std::cin.getline(tempCalle, 100);
    setCalle(tempCalle);


    int numero;
    while (true) {
        std::cout << "Numero: ";
        if (std::cin >> numero) {
            if (setNumero(numero) == true ){
                break;
            } else {
                std::cout << "*** ERROR: Debe ingresar solo numeros menores a 9999. ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    std::cin.ignore(10000, '\n');

    char tempPiso[10];
    std::cout << "Piso (o PB): ";
    std::cin.getline(tempPiso, 10);
    setPiso(tempPiso);

    char tempDepto[10];
    std::cout << "Depto: ";
    std::cin.getline(tempDepto, 10);
    setDepto(tempDepto);

    char tempLocalidad[50];
    std::cout << "Localidad: ";
    std::cin.getline(tempLocalidad, 50);
    setLocalidad(tempLocalidad);

    char tempCP[10];
    std::cout << "Codigo Postal: ";
    std::cin.getline(tempCP, 10);
    setCodigoPostal(tempCP);

    return true;
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
