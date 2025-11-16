#include <iostream>
#include "MenuConsultas.h"
#include "ArchivoAlumnos.h"
#include "ArchivoPersonal.h"
using namespace std;

void menuConsultas(){

    int opcion;
    bool bandera = true;

    while(bandera){

        system("cls");
        cout << "======================================\n";
        cout << "                CONSULTAS              "<< endl;
        cout << "======================================\n";
        cout << "1 - Consultar Asistencias" << endl;
        cout << "2 - Consultar Docentes" << endl;
        cout << "3 - Consultar Personal" << endl;
        cout << "4 - Consultar Alumnos" << endl;
        cout << "5 - Consultar Cursos" << endl;
        cout << "6 - Consulta Inscripciones" << endl;
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
                consultaAsistencias();
                system("pause");
                break;
            case 2:
                consultaDocentes();
                system("pause");
                break;
            case 3:
                consultaPersonal();
                system("pause");
                break;
            case 4:
                consultaAlumnos();
                system("pause");
                break;
            case 5:
                consultaCursos();
                system("pause");
                break;
            case 6:
                consultaInscripciones();
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


void consultaAsistencias(){

     int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              CONSULTAS ASISTENCIAS    " << endl;
        cout << "======================================\n";
        cout << "1 - Consultar por Legajo y Curso" << endl;
        cout << "2 - Consultar por Legajo, Curso y fecha" << endl;
        cout << "3 - Consultar por Curso y fecha" << endl;
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
                    /// funcion consultar por legajo y curso
                    cout << "consultar por legajo y curso" << endl;
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    /// funcion consultar por legajo curso y fecha
                    cout << "consultar por legajo, curso y fecha" << endl;
                    system("pause");

                    break;
                 case 3:
                     system("cls");
                     /// funcion consultar por curso y fecha
                    cout << "consultar por curso y fecha" << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default:
                    cout << "Opcion no valida"<< endl;
                    system("pause");

            }


    }

}

void consultaDocentes(){

    ArchivoPersonal managerDocente("personal.dat");

     int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              CONSULTAS DOCENTES   " << endl;
        cout << "======================================\n";
        cout << "1 - Consultar por Legajo" << endl;
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
                        managerDocente.consultarPorLegajoDocente();
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default: cout << "Opcion no valida"<< endl;
                    system("pause");

            }


    }

}

void consultaPersonal(){

    ArchivoPersonal managerPersonal("personal.dat");
    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              CONSULTAS PERSONAL  " << endl;
        cout << "======================================\n";
        cout << "1 - Consultar por Legajo" << endl;
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
                        managerPersonal.consultarPorLegajo();
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default: cout << "Opcion no valida"<< endl;
                    system("pause");

            }

    }
}

void consultaAlumnos(){

    ArchivoAlumnos managerAlumno("Alumnos.dat");

    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              CONSULTAS ALUMNOS  " << endl;
        cout << "======================================\n";
        cout << "1 - Consultar por Legajo" << endl;
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
                    managerAlumno.consultarPorLegajo();
                    cout << "consultar ALUMNOS  por legajo" << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default: cout << "Opcion no valida"<< endl;
                    system("pause");

            }


    }
}

void consultaCursos(){
    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              CONSULTAS CURSOS    " << endl;
        cout << "======================================\n";
        cout << "1 - Consultar por Cantidad de inscriptos mayor o menor .... " << endl;
        cout << "2 - Consultar por Costo de matricula mayor o menor  A ..." << endl;
        cout << "3 - Consultar por numero de aula" << endl;
        cout << "4 - Consultar por ID docente a cargo" << endl;
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
                    /// Consultar por Cantidad de inscriptos mayor o menor ....
                    cout << "Consultar por Cantidad de inscriptos mayor o menor ...." << endl;
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    /// Consultar por Costo de matricula mayor o menor  A ...
                    cout << "Consultar por Costo de matricula mayor o menor  A ..." << endl;
                    system("pause");

                    break;
                case 3:
                     system("cls");
                     ///Consultar por numero de aula
                    cout << "Consultar por numero de aula" << endl;
                    system("pause");
                    break;
                case 4:
                     system("cls");
                     ///Consultar por ID docente a cargo
                    cout << "Consultar por ID docente a cargo" << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default:
                    cout << "Opcion no valida"<< endl;
                    system("pause");

            }


    }

}

void consultaInscripciones(){

    int opt;
    bool bandera = true;

    while (bandera) {

        system("cls");
        cout << "======================================\n";
        cout << "              CONSULTAS INSCRIPCIONES      " << endl;
        cout << "======================================\n";
        cout << "1 - Consultar por curso" << endl;
        cout << "2 - Consultar por alumno" << endl;
        cout << "3 - Consultar por curso y matricula no paga " << endl;
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
                    /// Consultar por CURSO
                    cout << "Consultar por curso" << endl;
                    system("pause");
                    break;
                case 2:
                    system("cls");
                    /// Consultar por alumno
                    cout << "Consultar por alumno" << endl;
                    system("pause");

                    break;
                case 3:
                     system("cls");
                     ///Consultar por curso y matricula no paga
                    cout << "Consultar por curso y matricula no paga " << endl;
                    system("pause");
                    break;
                case 0:
                    bandera = false;
                    break;
                default:
                     cout << "Opcion no valida"<< endl;
                     system("pause");

            }


    }

}

