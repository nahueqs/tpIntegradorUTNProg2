#ifndef CURSO_H_INCLUDED
#define CURSO_H_INCLUDED

#include "Fecha.h"

class Curso {
private:
    int _idCurso;
    int _legajoDocenteACargo;
    char _descripcionCurso[100];
    int _numAula;
    int _cantInscriptos;
    Fecha _anio;  // Se usa Fecha pero solo importa el año
    int _maxAlumnos;
    float _costoMatricula;
    bool _estado;

public:
    // Constructor
    Curso(int id = 0, int legajoDoc = 0, const char* desc = "Sin descripcion",
          int aula = 0, int cantInsc = 0, Fecha anio = Fecha(),
          int maxAlum = 30, float costo = 0.0, bool est = true);

    // GETTERS
    int getIdCurso() const;
    int getLegajoDocenteACargo() const;
    const char* getDescripcionCurso() const;
    int getNumAula() const;
    int getCantInscriptos() const;
    Fecha getAnio() const;
    int getMaxAlumnos() const;
    float getCostoMatricula() const;
    bool getEstado() const;

    // SETTERS
    void setIdCurso(int valor);
    void setLegajoDocenteACargo(int valor);
    void setDescripcionCurso(const char* valor);
    void setNumAula(int valor);
    void setCantInscriptos(int valor);
    void setAnio(Fecha valor);
    void setMaxAlumnos(int valor);
    void setCostoMatricula(float valor);
    void setEstado(bool valor);

    // MÉTODOS
    void Cargar();
    void Mostrar();
    bool tieneCupoDisponible(); // Verifica si hay lugar
    void incrementarInscriptos(); // Suma 1 inscripto
    void decrementarInscriptos(); // Resta 1 inscripto
};

#endif // CURSO_H_INCLUDED
