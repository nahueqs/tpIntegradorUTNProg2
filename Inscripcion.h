#pragma once
#pragma once
#include "Fecha.h"

class Inscripcion {
private:
    int _idInscripcion;
    int _legajoAlumno;
    int _idCurso;
    Fecha _fechaInscripcion;
    float _importeMatricula;
    float _totalPagado;
    bool _matriculaPaga;
    bool _estado;

public:
    Inscripcion();

    /// setter
    void setIdInscripcion(int id);
    bool setLegajoAlumno(int legajo);
    bool setIdCurso(int id);
    void setFechaInscripcion(Fecha fecha);
    void setImporteMatricula(float importe);
    void setTotalPagado(float pagado);
    void setMatriculaPaga(bool pagada);
    void setEstado(bool estado);

    /// getters
    int getIdInscripcion() const;
    int getLegajoAlumno() const;
    int getIdCurso() const;
    Fecha getFechaInscripcion() const;
    float getImporteMatricula() const;
    float getTotalPagado() const;
    bool getMatriculaPaga() const;
    bool getEstado() const;

    //// cargar mostrar

    bool Cargar();
    void Mostrar();
};
