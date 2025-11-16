#include <iostream>
#include <cstdlib>
#include "MenuListados.h"
#include "ArchivoAlumnos.h"
#include "ArchivoPersonal.h"
using namespace std;

void menuListados(){

    int opcion;
    bool bandera = true;

    while(bandera){

        system("cls");
        cout << "======================================\n";
        cout << "                LISTADOS\n";
        cout << "======================================\n";
        cout << "1 - Listar Personal" << endl;
        cout << "2 - Listar Alumnos" << endl;
        cout << "3 - Listar Cursos" << endl;
        cout << "4 - Listar Inscripciones" << endl;
        cout << "5 - Listar Cargos" << endl;
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
                listadoPersonal();
                system("pause");
                break;
            case 2:
                listadoAlumnos();
                system("pause");
                break;
            case 3:
                listadoCursos();
                system("pause");
                break;
            case 4:
                listadoInscripciones();
                system("pause");
                break;
            case 5:
                listadoCargos();;
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

void listadoPersonal (){

    ArchivoPersonal managerPersonal("personal.dat");

    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              LISTADO PERSONAL         " << endl;
        cout << "======================================\n";
        cout << "1 - Listar Ordenados por Legajo Docente" << endl;
        cout << "2 - Listar Ordenados por Legajo" << endl;
        cout << "3 - Listar Ordenados por Cargo" << endl;
        cout << "4 - Listar Ordenados por Turno" << endl;
        cout << "5 - Listar Inactivos" << endl;
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
                        managerPersonal.listarPorLegajoDocente();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                        managerPersonal.listarPorLegajo();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                        managerPersonal.listarPorCargo();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                        managerPersonal.listarPorTurno();
                    system("pause");
                    break;
                case 5:
                    system("cls");
                        managerPersonal.listarInactivos();
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

void listadoAlumnos (){

    ArchivoAlumnos managerAlumno("alumno.dat");
    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              LISTADO ALUMNOS         " << endl;
        cout << "======================================\n";
        cout << "1 - Listar por Apellido" << endl;
        cout << "2 - Listar por DNI" << endl;
        cout << "3 - listar por Legajo " << endl;
        cout << "4 - Listar Inactivos" << endl;
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
                    managerAlumno.listarPorApellido();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    managerAlumno.listarPorDni();

                    system("pause");

                    break;
                 case 3:
                     system("cls");
                     managerAlumno.listarPorLegajo();
                    system("pause");
                    break;
                 case 4:
                     system("cls");
                     managerAlumno.listarInactivos();
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

void listadoCursos(){
    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              LISTADO PERSONAL         " << endl;
        cout << "======================================\n";
        cout << "1 - Listar por Curso" << endl;
        cout << "2 - Listar por Cantidad Maxima Alumno" << endl;
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
                    cout << "listado por CUrso" << endl;
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    /// funcion listar por cargo;
                    cout << "listado por cantidad maxima alumno" << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default:
                    cout << "opcion no valida"<< endl;
                    system("pause");

            }


    }
}

void listadoInscripciones(){
    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              LISTADO CURSOS        " << endl;
        cout << "======================================\n";
        cout << "1 - Listados por id Curso" << endl;
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
                    cout << "listado por ID CURSO" << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default:
                    cout << "opcion no valida"<< endl;
                    system("pause");

            }


    }

}

void listadoCargos(){
    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              LISTADO CARGO        " << endl;
        cout << "======================================\n";
        cout << "1 - Listados por ID Cargo" << endl;
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
                    cout << "listado por ID CARGO" << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default:
                    cout << "opcion no valida"<< endl;
                    system("pause");

            }


    }

}
