#include <iostream>
#include <cstdio>
#include <cstring>
#include "ArchivoCursos.h"

using namespace std;

ArchivoCursos::ArchivoCursos(const char *n) {
    strcpy(nombre, n);
}

int ArchivoCursos::contarRegistros() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Curso);
    fclose(p);
    return cant;
}

Curso ArchivoCursos::leerRegistro(int pos) {
    Curso obj;
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return obj;
    fseek(p, pos * sizeof(Curso), SEEK_SET);
    fread(&obj, sizeof(Curso), 1, p);
    fclose(p);
    return obj;
}

bool ArchivoCursos::grabarRegistro(Curso obj) {
    FILE *p = fopen(nombre, "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&obj, sizeof(Curso), 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCursos::modificarRegistro(Curso obj, int pos) {
    FILE *p = fopen(nombre, "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Curso), SEEK_SET);
    bool escribio = fwrite(&obj, sizeof(Curso), 1, p);
    fclose(p);
    return escribio;
}

int ArchivoCursos::buscarPorId(int idCurso) {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return -1;
    Curso obj;
    int pos = 0;
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getIdCurso() == idCurso) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2; // No encontrado
}

int ArchivoCursos::buscarPorAula(int aula) {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) return -1;
    Curso obj;
    int pos = 0;
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getNumAula() == aula && obj.getEstado()) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}

void ArchivoCursos::listar() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay cursos registrados.\n";
        return;
    }
    Curso obj;
    while (fread(&obj, sizeof(Curso), 1, p)) {
        obj.Mostrar();
        cout << "--------------------------------\n";
    }
    fclose(p);
}

void ArchivoCursos::listarActivos() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay cursos registrados.\n";
        return;
    }
    Curso obj;
    bool encontro = false;
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getEstado()) {
            obj.Mostrar();
            cout << "--------------------------------\n";
            encontro = true;
        }
    }
    fclose(p);
    if (!encontro) {
        cout << "No hay cursos activos.\n";
    }
}

void ArchivoCursos::listarPorMaxAlumnos() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay cursos registrados.\n";
        return;
    }

    Curso *cursos = new Curso[cant];
    FILE *p = fopen(nombre, "rb");

    for (int i = 0; i < cant; i++) {
        fread(&cursos[i], sizeof(Curso), 1, p);
    }
    fclose(p);

    // Ordenamiento burbuja por maxAlumnos (descendente)
    for (int i = 0; i < cant - 1; i++) {
        for (int j = 0; j < cant - i - 1; j++) {
            if (cursos[j].getMaxAlumnos() < cursos[j + 1].getMaxAlumnos()) {
                Curso temp = cursos[j];
                cursos[j] = cursos[j + 1];
                cursos[j + 1] = temp;
            }
        }
    }

    cout << "\n=== CURSOS ORDENADOS POR CAPACIDAD MAXIMA ===\n";
    for (int i = 0; i < cant; i++) {
        cursos[i].Mostrar();
        cout << "--------------------------------\n";
    }

    delete[] cursos;
}

void ArchivoCursos::listarPorDocente(int legajoDocente) {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay cursos registrados.\n";
        return;
    }
    Curso obj;
    bool encontro = false;
    cout << "\n=== CURSOS DEL DOCENTE (Legajo: " << legajoDocente << ") ===\n";
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getLegajoDocenteACargo() == legajoDocente && obj.getEstado()) {
            obj.Mostrar();
            cout << "--------------------------------\n";
            encontro = true;
        }
    }
    fclose(p);
    if (!encontro) {
        cout << "Este docente no tiene cursos asignados.\n";
    }
}

void ArchivoCursos::listarConCupoDisponible() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay cursos registrados.\n";
        return;
    }
    Curso obj;
    bool encontro = false;
    cout << "\n=== CURSOS CON CUPO DISPONIBLE ===\n";
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.tieneCupoDisponible()) {
            obj.Mostrar();
            cout << "--------------------------------\n";
            encontro = true;
        }
    }
    fclose(p);
    if (!encontro) {
        cout << "No hay cursos con cupos disponibles.\n";
    }
}

void ArchivoCursos::listarPorAnio(int anio) {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay cursos registrados.\n";
        return;
    }
    Curso obj;
    bool encontro = false;
    cout << "\n=== CURSOS DEL ANIO " << anio << " ===\n";
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getAnio().getAnio() == anio && obj.getEstado()) {
            obj.Mostrar();
            cout << "--------------------------------\n";
            encontro = true;
        }
    }
    fclose(p);
    if (!encontro) {
        cout << "No hay cursos para ese año.\n";
    }
}
