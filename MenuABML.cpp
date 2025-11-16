#include <iostream>
#include "MenuABML.h"
#include "ArchivoAlumnos.h"
#include "ArchivoPersonal.h"
#include "ArchivoCursos.h"
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
        cout << "2 - ABML Personal" << endl;
        cout << "3 - ABML Cursos" << endl;
        cout << "4 - ABML Inscripciones" << endl;
        cout << "5 - ABML Asistencias" << endl;
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
                abmlAlumnos();
                system("pause");
                break;
            case 2:
                abmlPersonal();
                system("pause");
                break;
            case 3:
                abmlCursos();
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

    ArchivoAlumnos managerAlumnos("Alumnos.dat");

    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              Gestion ABML Alumnos        " << endl;
        cout << "======================================\n";
        cout << "1 - ALTA ALUMNO" << endl;
        cout << "2 - BAJA ALUMNO"<< endl;
        cout << "3 - ReAlta Alumno" << endl;
        cout << "4 - MODIFICACIONES" << endl;
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
                      managerAlumnos.altaAlumno();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                        managerAlumnos.bajaAlumno();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                        managerAlumnos.reactivarAlumno();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                        managerAlumnos.modificar();
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
void abmlPersonal(){
    ArchivoPersonal managerPersonal("personal.dat");

    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              Gestion ABML Alumnos        " << endl;
        cout << "======================================\n";
        cout << "1 - ALTA Personal" << endl;
        cout << "2 - BAJA Personal"<< endl;
        cout << "3 - ReAlta Personal" << endl;
        cout << "4 - MODIFICACIONES" << endl;
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
                      managerPersonal.darDeAlta();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                        managerPersonal.darDeBaja();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                        managerPersonal.reactivar();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                        managerPersonal.modificar();
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
void abmlCursos(){
    ArchivoCursos managerCursos("Cursos.dat");

    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              Gestion ABML Alumnos        " << endl;
        cout << "======================================\n";
        cout << "1 - ALTA Curso" << endl;
        cout << "2 - BAJA Curso"<< endl;
        cout << "3 - ReAlta Curso" << endl;
        cout << "4 - MODIFICACIONES" << endl;
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
                      managerCursos.darDeAlta();
                    system("pause");
                    break;
                case 2:
                    system("cls");
                        managerCursos.darDeBaja();
                    system("pause");
                    break;
                case 3:
                    system("cls");
                        managerCursos.reactivar();
                    system("pause");
                    break;
                case 4:
                    system("cls");
                        managerCursos.modificar();
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
void abmlAsistencias(){}


