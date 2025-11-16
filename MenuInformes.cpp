#include <iostream>
#include <cstdlib>
#include "MenuInformes.h"


using namespace std;

void menuInformes(){

    int opcion;
    bool bandera =true;

    while(bandera){

        system("cls");
        cout << "======================================\n";
        cout << "               INFORMES                 " << endl;
        cout << "======================================\n";
        cout << "1 - Recaudacion anueal de todos los cursos " << endl;
        cout << "2 - Recaudacion por curso" << endl;
        cout << "3 - Informe Anual de alumnos inscriptos por cursos " << endl;
        cout << "4 - Informe anual de alumnos deudores por curso" << endl;
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
                system("cls");
                informeRecaudacionAnualCursos();
                system("pause");
                break;
            case 2:
                system("cls");
                informeRecaudacionporCurso();
                system("pause");
                break;
            case 3:
                system("cls");
                informeAlumnosInscriptosAnual();
                system("pause");
                break;
            case 4:
                system("cls");
                informeAlumnoDeudores();
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

void informeRecaudacionAnualCursos(){
    int anio;
    cout <<"INGRESE EL ANIO:" << endl;
    cin >> anio;
    cout << "INFORME ANIO";

}
void informeRecaudacionporCurso(){}
void informeAlumnosInscriptosAnual(){}
void informeAlumnoDeudores(){}


