#ifndef ARCHIVOCURSOS_H_INCLUDED
#define ARCHIVOCURSOS_H_INCLUDED

#include "Curso.h"

class ArchivoCursos {
private:
    char nombre[30];

public:
    ArchivoCursos(const char *n = "Cursos.dat");

    // MÉTODOS BÁSICOS
    int contarRegistros();
    Curso leerRegistro(int pos);
    bool grabarRegistro(Curso obj);
    bool modificarRegistro(Curso obj, int pos);

    // BÚSQUEDAS
    int buscarPorId(int idCurso);
    int buscarPorAula(int aula);

    // LISTADOS
    void listar();
    void listarActivos();
    void listarPorMaxAlumnos(); // Ordenado por cupo máximo

    // CONSULTAS ESPECÍFICAS
    void listarPorDocente(int legajoDocente);
    void listarConCupoDisponible();
    void listarPorAnio(int anio);
};

#endif // ARCHIVOCURSOS_H_INCLUDED
