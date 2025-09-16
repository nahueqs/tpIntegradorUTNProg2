#ifndef MATERIA_H_INCLUDED
#define MATERIA_H_INCLUDED

class Materia {
private:
    int codigo;
    char nombre[50];
    int cupoMaximo;

public:
    Materia(int cod = 0, const char *nom = "Sin nombre", int cupo = 30);

    void setCodigo(int c);
    void setNombre(const char *n);
    void setCupoMaximo(int c);

    int getCodigo();
    const char* getNombre();
    int getCupoMaximo();

    void Cargar();
    void Mostrar();
};

#endif // MATERIA_H_INCLUDED
