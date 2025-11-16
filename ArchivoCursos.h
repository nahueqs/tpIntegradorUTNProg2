#ifndef ARCHIVOCURSOS_H_INCLUDED
#define ARCHIVOCURSOS_H_INCLUDED

#include "Curso.h"

class ArchivoCursos {
private:
    char nombre[30];

public:
    ArchivoCursos(const char *n = "Cursos.dat");

    /// metodos basicos
    int contarRegistros();
    Curso leerRegistro(int pos);
    bool grabarRegistro(Curso obj);
    bool modificarRegistro(Curso obj, int pos);
    int generarIdCurso();
    Curso buscarYLeerPorId(int id);

    // BÚSQUEDAS
    int buscarPorId(int idCurso);
    int buscarPorAula(int aula);

    /// alta Baja Modificaciones
    void darDeAlta();
    void darDeBaja();
    void modificar();
    void reactivar();

    // LISTADOS
    void listarActivos();
    void listarInactivos();
    void listarPorIdCurso();
    void listarPorMaxAlumnos(); // Ordenado por mayores alumnos

    /// consultas
    void consularPorLegajoDocente();
    void consultarPorNumAula();
    void consultarPorCosto();
    void consultarPorIdCurso();
};

#endif // ARCHIVOCURSOS_H_INCLUDED
