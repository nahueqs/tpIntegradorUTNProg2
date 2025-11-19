#ifndef CURSO_H_INCLUDED
#define CURSO_H_INCLUDED

#pragma once
#include <cstring>

class Curso {
private:
    int _idCurso;
    int _legajoDocenteACargo;
    char _descripcionCurso[100];
    int _numAula;
    int _maxAlumnos;
    int _anio;
    float _costoMatricula;
    bool _estado;

public:

    Curso();
    Curso(int id, int legajoDoc, const char* desc, int numAula, int maxAlu, int anio, float costo, bool estado);


    void setIdCurso(int id);
    void setLegajoDocente(int legajo);
    void setDescripcion(const char* descripcion);
    bool setNumAula(int num);
    bool setMaxAlumnos(int max);
    bool setAnio(int anio);
    bool setCostoMatricula(float costo);
    void setEstado(bool estado);


    int getIdCurso() const;
    int getLegajoDocente() const;
    const char* getDescripcion() const;
    int getNumAula() const;
    int getMaxAlumnos() const;
    int getAnio() const;
    float getCostoMatricula() const;
    bool getEstado() const;


    bool Cargar();
    void Mostrar();
};

#endif // CURSO_H_INCLUDED
