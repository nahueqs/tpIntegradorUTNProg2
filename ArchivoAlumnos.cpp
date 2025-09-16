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

int ArchivoAlumnos::buscarPorLegajo(int legajo) {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return -1;
    Alumno obj;
    int pos = 0;
    while (fread(&obj, sizeof obj, 1, p)) {
        if (obj.getLegajo() == legajo) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2; // no encontrado
}

Alumno ArchivoAlumnos::leerRegistro(int pos) {
    Alumno obj;
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return obj;
    fseek(p, pos * sizeof obj, SEEK_SET);
    fread(&obj, sizeof obj, 1, p);
    fclose(p);
    return obj;
}

bool ArchivoAlumnos::grabarRegistro(Alumno obj) {
    FILE *p = fopen(nombre, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&obj, sizeof obj, 1, p);
    fclose(p);
    return escribio;
}

void ArchivoAlumnos::listar() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay registros de alumnos.\n";
        return;
    }
    Alumno obj;
    while (fread(&obj, sizeof obj, 1, p)) {
        obj.Mostrar();
        cout << "------------------------\n";
    }
    fclose(p);
}
