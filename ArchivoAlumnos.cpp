#include <iostream>
#include <cstdio>
#include <cstring>
#include "ArchivoAlumnos.h"

using namespace std;

ArchivoAlumnos::ArchivoAlumnos(const char *n) {
    strcpy(nombre, n);
}

int ArchivoAlumnos::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Alumno);
    fclose(p);
    return cant;
}

Alumno ArchivoAlumnos::leerRegistro(int pos) {
    Alumno obj;
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return obj;
    fseek(p, pos * sizeof(Alumno), SEEK_SET);
    fread(&obj, sizeof(Alumno), 1, p);
    fclose(p);
    return obj;
}

bool ArchivoAlumnos::grabarRegistro(Alumno obj) {
    FILE *p = fopen(nombre, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&obj, sizeof(Alumno), 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoAlumnos::modificarRegistro(Alumno obj, int pos) {
    FILE *p = fopen(nombre, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Alumno), SEEK_SET);
    bool escribio = fwrite(&obj, sizeof(Alumno), 1, p);
    fclose(p);
    return escribio;
}

// ========== BÚSQUEDAS ==========

int ArchivoAlumnos::buscarPorLegajo(int legajo) {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return -1;
    Alumno obj;
    int pos = 0;
    while (fread(&obj, sizeof(Alumno), 1, p)) {
        if (obj.getLegajo() == legajo) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2; // No encontrado
}

int ArchivoAlumnos::buscarPorDni(int dni) {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return -1;
    Alumno obj;
    int pos = 0;
    while (fread(&obj, sizeof(Alumno), 1, p)) {
        if (obj.getDni() == dni) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2; // No encontrado
}

// ========== VALIDACIONES ==========

bool ArchivoAlumnos::existeLegajo(int legajo) {
    return buscarPorLegajo(legajo) >= 0;
}

bool ArchivoAlumnos::existeDni(int dni) {
    return buscarPorDni(dni) >= 0;
}

bool ArchivoAlumnos::validarLegajoUnico(int legajo) {
    if (existeLegajo(legajo)) {
        cout << "\n*** ERROR: Ya existe un alumno con el legajo " << legajo << " ***\n";
        return false;
    }
    return true;
}

bool ArchivoAlumnos::validarDniUnico(int dni) {
    if (existeDni(dni)) {
        cout << "\n*** ERROR: Ya existe un alumno con el DNI " << dni << " ***\n";
        return false;
    }
    return true;
}

// ========== LISTADOS ==========

void ArchivoAlumnos::listar() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay registros de alumnos.\n";
        return;
    }
    Alumno obj;
    bool hayRegistros = false;
    while (fread(&obj, sizeof(Alumno), 1, p)) {
        obj.Mostrar();
        cout << "--------------------------------\n";
        hayRegistros = true;
    }
    fclose(p);

    if (!hayRegistros) {
        cout << "No hay alumnos registrados.\n";
    }
}

void ArchivoAlumnos::listarActivos() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay registros de alumnos.\n";
        return;
    }
    Alumno obj;
    bool encontro = false;
    cout << "\n========== ALUMNOS ACTIVOS ==========\n";
    while (fread(&obj, sizeof(Alumno), 1, p)) {
        if (obj.getEstado()) {
            obj.Mostrar();
            cout << "--------------------------------\n";
            encontro = true;
        }
    }
    fclose(p);

    if (!encontro) {
        cout << "No hay alumnos activos.\n";
    }
}

void ArchivoAlumnos::listarPorApellido() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay alumnos registrados.\n";
        return;
    }

    Alumno *alumnos = new Alumno[cant];
    FILE *p = fopen(nombre, "rb");

    for (int i = 0; i < cant; i++) {
        fread(&alumnos[i], sizeof(Alumno), 1, p);
    }
    fclose(p);

    // Ordenamiento burbuja por apellido
    for (int i = 0; i < cant - 1; i++) {
        for (int j = 0; j < cant - i - 1; j++) {
            if (strcmp(alumnos[j].getApellido(), alumnos[j + 1].getApellido()) > 0) {
                Alumno temp = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temp;
            }
        }
    }

    cout << "\n========== ALUMNOS ORDENADOS POR APELLIDO ==========\n";
    for (int i = 0; i < cant; i++) {
        alumnos[i].Mostrar();
        cout << "--------------------------------\n";
    }

    delete[] alumnos;
}

void ArchivoAlumnos::listarPorDni() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay alumnos registrados.\n";
        return;
    }

    Alumno *alumnos = new Alumno[cant];
    FILE *p = fopen(nombre, "rb");

    for (int i = 0; i < cant; i++) {
        fread(&alumnos[i], sizeof(Alumno), 1, p);
    }
    fclose(p);

    // Ordenamiento burbuja por DNI
    for (int i = 0; i < cant - 1; i++) {
        for (int j = 0; j < cant - i - 1; j++) {
            if (alumnos[j].getDni() > alumnos[j + 1].getDni()) {
                Alumno temp = alumnos[j];
                alumnos[j] = alumnos[j + 1];
                alumnos[j + 1] = temp;
            }
        }
    }

    cout << "\n========== ALUMNOS ORDENADOS POR DNI ==========\n";
    for (int i = 0; i < cant; i++) {
        alumnos[i].Mostrar();
        cout << "--------------------------------\n";
    }

    delete[] alumnos;
}
