#ifndef ARCHIVOALUMNOS_H_INCLUDED
#define ARCHIVOALUMNOS_H_INCLUDED

#include "Alumno.h"

class ArchivoAlumnos {
private:
    char nombre[30];

public:
    ArchivoAlumnos(const char *n = "Alumnos.dat");

<<<<<<< HEAD
    // MÉTODOS BÁSICOS
=======
    // metodos basicos
>>>>>>> origin/alex
    int contarRegistros();
    Alumno leerRegistro(int pos);
    bool grabarRegistro(Alumno obj);
    bool modificarRegistro(Alumno obj, int pos);
<<<<<<< HEAD

    // BÚSQUEDAS
    int buscarPorLegajo(int legajo);
    int buscarPorDni(int dni);

    // VALIDACIONES
=======
    int generarNuevoLegajo();

    // busquedas
    int buscarPorLegajo(int legajo);
    int buscarPorDni(int dni);
    Alumno buscarYLeerPorLegajo(int legajo);

    // validacinoes
>>>>>>> origin/alex
    bool existeLegajo(int legajo);
    bool existeDni(int dni);
    bool validarLegajoUnico(int legajo);
    bool validarDniUnico(int dni);

<<<<<<< HEAD
    // LISTADOS
    void listar();
    void listarActivos();
    void listarPorApellido();
    void listarPorDni();
    void listarSinOrdenar(); // ← AGREGAR ESTA LÍNEA
    void compactarArchivo();
=======
    // listados
    void listar();
    void listarInactivos();
    void listarPorApellido();
    void listarPorDni();
    void listarPorLegajo();

    /// Consultas
    void consultarPorLegajo();

    // ALTA Y BAJA
    void altaAlumno();
    void bajaAlumno();
    void reactivarAlumno();
    void modificar();

    /// MODIFICAICONES

>>>>>>> origin/alex
};

#endif
