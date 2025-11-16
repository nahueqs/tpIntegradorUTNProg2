#include <iostream>
#include <cstdlib>
#include "ArchivoAlumnos.h"
#include "ArchivoCursos.h"
#include "MenuListados.h"
#include "MenuConsultas.h"
#include "MenuInformes.h"
#include "MenuABML.h"

using namespace std;

int main() {
    int opcion;
    bool bandera = true;

    while(bandera){

        system("cls");
        cout << "======================================" << endl;
        cout << "   SISTEMA DE GESTION DE COLEGIO" << endl;
        cout << "======================================" << endl;
        cout << "1 - Listados " << endl;
        cout << "2 - Consultas" << endl;
        cout << "3 - Informes y Reportes " << endl;
        cout << "4 - Gestiones ABML" << endl;
        cout << "0 - Salir del sistema "<< endl;
        cout << "======================================" << endl;
        cout << "Opcion: " << endl;
        cin >> opcion;

        if (cin.fail()) {
            cout << "Error: Debe ingresar solo numeros." << endl;
            cin.clear();
            cin.ignore(10000, '\n');

            system("pause");
            continue;
        }

            switch(opcion) {
                case 1:
                    menuListados();
                    break;
                case 2:
                    menuConsultas();
                    break;
                case 3:
                    menuInformes();
                    system("pause");
                    break;
                case 4:
                    menuABML();
                    system("pause");
                    break;
                case 0:
                     bandera = false;
                    cout << "Saliendo del sistema..."<< endl;

                    break;
                default:
                    cout << "Opcion invalida. Intente nuevamente" << endl;
                    system("pause");
                    system("clear");
            }

    }


    return 0;
}
