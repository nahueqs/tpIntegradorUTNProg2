#pragma once
#include "Fecha.h"

class Inscripcion {
private:
    int _idInscripcion;
    int _legajoAlumno;
    int _idCurso;
    Fecha _fechaInscripcion;
<<<<<<< HEAD
    float _importeMatricula;
    float _totalPagado;
=======
    float _importeMatricula; /// este guarda lo que valia la matricula
    float _importePagado; /// este guarda lo que pago
>>>>>>> b78f4eef4c3ecd795c1626d60b849d95e8b58276
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
<<<<<<< HEAD
    void setTotalPagado(float pagado);
=======
    void setImportePagado(float importe);
>>>>>>> b78f4eef4c3ecd795c1626d60b849d95e8b58276
    void setMatriculaPaga(bool pagada);
    void setEstado(bool estado);

    /// getters
    int getIdInscripcion() const;
    int getLegajoAlumno() const;
    int getIdCurso() const;
    Fecha getFechaInscripcion() const;
    float getImporteMatricula() const;
<<<<<<< HEAD
    float getTotalPagado() const;
=======
    float getImportePagado() const;
>>>>>>> b78f4eef4c3ecd795c1626d60b849d95e8b58276
    bool getMatriculaPaga() const;
    bool getEstado() const;

    //// cargar mostrar

    bool Cargar();
    void Mostrar();
};
