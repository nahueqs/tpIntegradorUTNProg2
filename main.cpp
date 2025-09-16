#include <iostream>
#include <cstdlib>
#include "ArchivoAlumnos.h"

using namespace std;

void menuAlumnos() {
    ArchivoAlumnos arc;
    int opcion;
    do {
        system("cls");
        cout << "===== GESTION DE ALUMNOS =====\n";
        cout << "1 - Agregar alumno\n";
        cout << "2 - Listar alumnos\n";
        cout << "3 - Buscar por legajo\n";
        cout << "0 - Volver\n";
        cout << "==============================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: {
            Alumno obj;
            obj.Cargar();
            if (arc.grabarRegistro(obj))
                cout << "Alumno guardado.\n";
            else
                cout << "Error al guardar.\n";
            system("pause");
            break;
        }
        case 2:
            arc.listar();
            system("pause");
            break;
        case 3: {
            int leg;
            cout << "Ingrese legajo: ";
            cin >> leg;
            int pos = arc.buscarPorLegajo(leg);
            if (pos >= 0) {
                Alumno obj = arc.leerRegistro(pos);
                obj.Mostrar();
            } else {
                cout << "Alumno no encontrado.\n";
            }
            system("pause");
            break;
        }
        }
    } while(opcion != 0);
}

int main() {
    int opcion;
    do {
        system("cls");
        cout << "===== SISTEMA DE GESTION COLEGIO =====\n";
        cout << "1 - Gestion de alumnos\n";
        cout << "2 - Gestion de profesores\n";
        cout << "3 - Gestion de materias\n";
        cout << "0 - Salir\n";
        cout << "======================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: menuAlumnos(); break;
        case 2: cout << "Modulo profesores en desarrollo\n"; system("pause"); break;
        case 3: cout << "Modulo materias en desarrollo\n"; system("pause"); break;
        }
    } while(opcion != 0);

    return 0;
}
