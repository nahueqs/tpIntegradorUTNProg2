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

    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    // Leer todos los alumnos en un vector temporal
    Alumno registro;
    int indices[1000]; // Guardar orden de índices
    int leidos = 0;

    // Primero leer todo en memoria
    fseek(p, 0, SEEK_SET);
    while (leidos < 1000 && fread(&registro, sizeof(Alumno), 1, p) == 1) {
        indices[leidos] = leidos;
        leidos++;
    }

    // Ordenar los ÍNDICES (no los objetos completos)
    for (int i = 0; i < leidos - 1; i++) {
        for (int j = i + 1; j < leidos; j++) {
            // Leer objetos para comparar
            Alumno a1, a2;
            fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
            fread(&a1, sizeof(Alumno), 1, p);
            fseek(p, indices[j] * sizeof(Alumno), SEEK_SET);
            fread(&a2, sizeof(Alumno), 1, p);

            if (strcmp(a1.getApellido(), a2.getApellido()) > 0) {
                // Intercambiar índices
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Mostrar en orden
    cout << "\n========== ALUMNOS ORDENADOS POR APELLIDO ==========\n";
    for (int i = 0; i < leidos; i++) {
        Alumno obj;
        fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
        fread(&obj, sizeof(Alumno), 1, p);
        obj.Mostrar();
        cout << "--------------------------------\n";
    }

    fclose(p);
}

void ArchivoAlumnos::listarPorDni() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay alumnos registrados.\n";
        return;
    }

    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    // Leer todos los alumnos en un vector temporal
    Alumno registro;
    int indices[1000]; // Guardar orden de índices
    int leidos = 0;

    // Primero leer todo en memoria
    fseek(p, 0, SEEK_SET);
    while (leidos < 1000 && fread(&registro, sizeof(Alumno), 1, p) == 1) {
        indices[leidos] = leidos;
        leidos++;
    }

    // Ordenar los ÍNDICES por DNI
    for (int i = 0; i < leidos - 1; i++) {
        for (int j = i + 1; j < leidos; j++) {
            // Leer objetos para comparar
            Alumno a1, a2;
            fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
            fread(&a1, sizeof(Alumno), 1, p);
            fseek(p, indices[j] * sizeof(Alumno), SEEK_SET);
            fread(&a2, sizeof(Alumno), 1, p);

            if (a1.getDni() > a2.getDni()) {
                // Intercambiar índices
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Mostrar en orden
    cout << "\n========== ALUMNOS ORDENADOS POR DNI ==========\n";
    for (int i = 0; i < leidos; i++) {
        Alumno obj;
        fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
        fread(&obj, sizeof(Alumno), 1, p);
        obj.Mostrar();
        cout << "--------------------------------\n";
    }

    fclose(p);
}

void ArchivoAlumnos::compactarArchivo() { ///método para limpiar registros corruptos
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay registros para compactar.\n";
        return;
    }

    // Archivo temporal
    FILE *pOrig = fopen(nombre, "rb");
    FILE *pTemp = fopen("Alumnos_temp.dat", "wb");

    if (pOrig == nullptr || pTemp == nullptr) {
        cout << "Error al abrir archivos.\n";
        if (pOrig) fclose(pOrig);
        if (pTemp) fclose(pTemp);
        return;
    }

    Alumno obj;
    int validos = 0;
    int eliminados = 0;

    while (fread(&obj, sizeof(Alumno), 1, pOrig) == 1) {
        // Solo copiar registros válidos (con legajo > 0 y activos)
        if (obj.getLegajo() > 0 && obj.getEstado()) {
            fwrite(&obj, sizeof(Alumno), 1, pTemp);
            validos++;
        } else {
            eliminados++;
        }
    }

    fclose(pOrig);
    fclose(pTemp);

    // Reemplazar archivo original
    remove(nombre);
    rename("Alumnos_temp.dat", nombre);

    cout << "\n===== ARCHIVO COMPACTADO =====\n";
    cout << "Registros validos: " << validos << "\n";
    cout << "Registros eliminados: " << eliminados << "\n";
}
