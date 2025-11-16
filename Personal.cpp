#include "Personal.h"
#include <iostream>
#include "Persona.h"
#include <string>
#include <cstring>

using namespace std;


Personal::Personal() : Persona() { // Llama al constructor de Persona
    _legajo = 0;
    _turnos[0] = false;
    _turnos[1] = false;
    _turnos[2] = false;
    _cargo = 0; // 0 = Indefinido
    _legajoDocente = 0;
}

 /// setters
void Personal::setLegajo(int legajo) {
     _legajo = legajo;
}
void Personal::setTurno(int indice, bool valor) {
    if (indice >= 0 && indice < 3) {
        _turnos[indice] = valor;
    }
}
void Personal::setCargo(int cargo) {
    _cargo = cargo;
}
void Personal::setLegajoDocente(int legajo) {
    _legajoDocente = legajo;
}


/// getters
int Personal::getLegajo() const { return _legajo; }
bool Personal::getTurno(int indice) const {
    if (indice >= 0 && indice < 3) {
        return _turnos[indice];
    }
    return false;
}
int Personal::getCargo() const { return _cargo; }
int Personal::getLegajoDocente() const { return _legajoDocente; }



std::string Personal::getTurnosComoTexto() const {
    string textoTurnos = "";
    bool ninguno = true;
    if (_turnos[0]) { textoTurnos += "Maniana"; ninguno = false; }
    if (_turnos[1]) { if (!ninguno) textoTurnos += ", "; textoTurnos += "Tarde"; ninguno = false; }
    if (_turnos[2]) { if (!ninguno) textoTurnos += ", "; textoTurnos += "Noche"; ninguno = false; }
    if (ninguno) { return "Sin turnos asignados"; }
    return textoTurnos;
}

std::string Personal::getCargoComoTexto() const {
    switch (_cargo) {
        case 1: return "Director";
        case 2: return "Preceptor";
        case 3: return "Personal de Limpieza";
        case 4: return "Docente";
        default: return "No definido";
    }
}


bool Personal::Cargar() {

    if (!Persona::Cargar()) {
        return false;
    }

    cout << "--- Asignacion de Turnos ---" << endl;
    int opcion;


    cout << "Trabaja en el turno Maniana? (1: SI / 0: NO): ";
    cin >> opcion;
    if (opcion == 1) {
        setTurno(0, true);
    } else {
        setTurno(0, false);
    }

    cout << "Trabaja en el turno Tarde? (1: SI / 0: NO): ";
    cin >> opcion;
    if (opcion == 1) {
        setTurno(1, true);
    } else {
        setTurno(1, false);
    }

    cout << "Trabaja en el turno Noche? (1: SI / 0: NO): ";
    cin >> opcion;
    if (opcion == 1) {
        setTurno(2, true);
    } else {
        setTurno(2, false);
    }

    int cargoIngresado;
    while (true) {
        cout << "\n--- ASIGNAR CARGO ---\n";
        cout << "1: Director\n";
        cout << "2: Preceptor\n";
        cout << "3: Limpieza\n";
        cout << "4: Docente\n";
        cout << "Ingrese el nro de cargo: ";
        cin >> cargoIngresado;

        if (cin.fail()) {
            cout << "Error: Debe ingresar solo numeros." << endl;
            cin.clear();
            cin.ignore(10000, '\n');

            system("pause");
            continue;
        }
        if (cargoIngresado && cargoIngresado >= 1 && cargoIngresado <= 4) {
            setCargo(cargoIngresado);
            break;
        } else {
            cout << "\n*** ERROR: Opcion no valida. ***\n";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }


    cin.ignore(10000, '\n');
    return true;
}


void Personal::Mostrar() {
    Persona::Mostrar();

    cout << "--- Datos Laborales ---" << endl;
    cout << "Legajo Personal: " << _legajo << endl;
    cout << "Cargo:           " << getCargoComoTexto() << endl;
    cout << "Turnos:          " << getTurnosComoTexto() << endl;
    if (_cargo == 4) {
        cout << "--- Datos Docentes ---" << endl;
        cout << "Legajo Docente:  " << _legajoDocente << endl;
    }
}
