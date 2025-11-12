#include <iostream>
#include "MenuABML.h"

using namespace std;

void menuABML(){

    int opcion;
    bool bandera = true;

    while(bandera){

        system("cls");
        cout << "======================================\n";
        cout << "                MENU ABML            "<< endl;
        cout << "======================================\n";
        cout << "1 - ABML Alumnos" << endl;
        cout << "2 - ABML personal" << endl;
        cout << "3 - ABML Cargos" << endl;
        cout << "4 - ABML cursos" << endl;
        cout << "5 - ABML inscripciones" << endl;
        cout << "6 - ABML asistencias" << endl;
        cout << "--------------------------------------" << endl;
        cout << "0 - Volver al Menu Principal" << endl;
        cout << "======================================" << endl;
        cout << "Opcion: ";
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

                system("pause");
                break;
            case 2:

                system("pause");
                break;
            case 3:

                system("pause");
                break;
            case 4:

                system("pause");
                break;
            case 5:
                system("pause");
                break;
            case 0:
                bandera = false;
                break;
            default:
                cout << endl << "Opcion no valida." << endl;
                system("pause");
                break;
        }

    }

}

void abmlAlumnos(){

    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              Gestion ABML Alumnos        " << endl;
        cout << "======================================\n";
        cout << "1 - ALTA ALUMNO" << endl;
        cout << "2 - BAJA ALUMNO"<< endl;
        cout << "0 - Volver " << endl;
        cin >> opt;

         if (cin.fail()) {
            cout << "Error: Debe ingresar solo numeros." << endl;
            cin.clear();
            cin.ignore(10000, '\n');

            system("pause");
            continue;
        }


            switch(opt) {
                case 1:
                    system("cls");
                      /// funcion listar por turno
                    cout << "listado por turnoooooooooooooo" << endl;
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    /// funcion listar por cargo;
                    cout << "listado por cargoooooo" << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default: cout << "opcion no valida"<< endl;
                    system("pause");

            }


    }


}
void abmlPersonal(){}
void abmlCargos(){}
void abmlCursos(){}
void abmlAsistencias(){}


