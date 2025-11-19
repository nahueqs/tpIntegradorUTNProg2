#pragma once
#include "Fecha.h"

class Asistencia {
private:
    int _legajoAlumno;
    int _idCurso;
    Fecha _fecha;
    bool _presente;
    bool _estado;

public:
    Asistencia();


    bool setLegajoAlumno(int legajo);
    bool setIdCurso(int id);
    void setFecha(Fecha f);
    void setPresente(bool p);
    void setEstado(bool e);


    int getLegajoAlumno() const;
    int getIdCurso() const;
    Fecha getFecha() const;
    bool getPresente() const;
    bool getEstado() const;


    void Mostrar();
};
