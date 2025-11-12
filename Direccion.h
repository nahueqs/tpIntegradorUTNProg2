#ifndef DIRECCION_H_INCLUDED
#define DIRECCION_H_INCLUDED

class Direccion {
private:
    char _calle[100];
    int _numero;
    char _piso[10];     // Ej: "5", "PB"
    char _depto[10];    // Ej: "B"
    char _localidad[50];
    char _codigoPostal[10];

public:
    // --- Constructores ---
    Direccion(); // Vacio
    Direccion(const char *calle, int num, const char *piso,
              const char *depto, const char *loc, const char *cp);

    // --- Setters ---
    void setCalle(const char *calle);
    void setNumero(int num);
    void setPiso(const char *piso);
    void setDepto(const char *depto);
    void setLocalidad(const char *loc);
    void setCodigoPostal(const char *cp);

    // --- Getters ---
    const char* getCalle() const; // Devuelve const char*
    int getNumero() const;
    const char* getPiso() const;
    const char* getDepto() const;
    const char* getLocalidad() const;
    const char* getCodigoPostal() const;

    // --- Métodos ---
    void Cargar();
    void Mostrar();
};

#endif // DIRECCION_H_INCLUDED
