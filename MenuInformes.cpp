#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
#include "rlutil.h"

#include "MenuInformes.h"
#include "ArchivoAlumnos.h"
#include "ArchivoPersonal.h"
#include "ArchivoCursos.h"
#include  "ArchivoInscripcion.h"
using namespace rlutil;
using namespace std;

void menuInformes(){

    int opcion;
    bool bandera =true;

    while(bandera){

        system("cls");
        cout << "======================================\n";
        cout << "               INFORMES                 " << endl;
        cout << "======================================\n";
        cout << "1 - Recaudacion anual de todos los cursos " << endl;
        cout << "2 - Recaudacion por curso" << endl;
        cout << "3 - Informe anual de alumnos inscriptos " << endl;
        cout << "4 - Informe anual de alumnos deudores por curso" << endl;
        cout << "5 - Informe de cursos a cargo de docente" << endl;

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
            case 5:
                system("cls");
                informeCursosPorProfesor();
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
    while (true) {
    cout << "Ingrese un anio: ";
    if (cin >> anio) {
        if (anio >= 1900 && anio <= 2100) {
            break;
        } else {
            cout << "Anio fuera de rango (1900-2100)" << endl;
        }
    } else {
        cout << "INGRESE UN ANIO VALIDO:" << endl;
    }
    cin.clear();
    cin.ignore(10000, '\n');
    }

    cout << "INFORME RECAUDACION ANIO " + anio  <<endl;

    ArchivoInscripcion inscripciones;
    FILE *p = fopen("Inscripciones.dat", "rb");


    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }



    int cant = inscripciones.contarRegistros();
    int leidos = 0;
    float recaudado = 0;

    Inscripcion obj_temporal;
    while (leidos < cant && fread(&obj_temporal, sizeof(Inscripcion), 1, p) == 1) {
        if (obj_temporal.getEstado()) {
                if(obj_temporal.getFechaInscripcion().getAnio() == anio){
                   recaudado += obj_temporal.getTotalPagado();
                    leidos++;
            }
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay inscripciones activas en ese anio." << endl;
        return;
    } else {
    cout << "Lo recaudado anualmente entre todos los cursos fue de $"<< fixed << setprecision(2)  << recaudado  << endl;
    cout << "Total de inscripciones encontradas: " << leidos << endl;

    }






}
void informeRecaudacionporCurso(){

    int idCurso;
    while (true) {
    cout << "Ingrese el id curso: ";
    if (cin >> idCurso) {
        if (idCurso > 0) {
            break;
        } else {
            cout << " Id curso debe ser positivo, ingrese otro id." << endl;
        }
    } else {
        cout << "INGRESE UN ID CURSO VALIDO:" << endl;
    }
    cin.clear();
    cin.ignore(10000, '\n');
    }

    cout << "INFORME RECAUDACION CURSO " <<  idCurso  <<endl;

    ArchivoInscripcion inscripciones;
    FILE *p = fopen("Inscripciones.dat", "rb");


    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int cant = inscripciones.contarRegistros();
    int leidos = 0;
    float recaudado = 0;

    Inscripcion obj_temporal;
    while (leidos < cant && fread(&obj_temporal, sizeof(Inscripcion), 1, p) == 1) {
        if (obj_temporal.getEstado()) {
                if(obj_temporal.getIdCurso() == idCurso){
                   recaudado += obj_temporal.getTotalPagado();
                    leidos++;
            }
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay inscripciones activas en ese curso." << endl;
        return;
    } else {
    cout << "Lo recaudado en total para ese curso fue de $"<< fixed << setprecision(2)  << recaudado  << endl;
    cout << "Total de inscripciones encontradas: " << leidos << endl;
    }
}
void informeAlumnosInscriptosAnual(){
    // busco todaas las inscripciones que pertenezcan al año, sumo la cantidad
    int anio;
        while (true) {
        cout << "Ingrese un anio: ";
        if (cin >> anio) {
            if (anio >= 1900 && anio <= 2100) {
                break;
            } else {
                cout << "Anio fuera de rango (1900-2100)" << endl;
            }
        } else {
            cout << "INGRESE UN ANIO VALIDO:" << endl;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        }

        cout << "INFORME RECAUDACION ANIO " <<  anio  <<endl;

        ArchivoInscripcion inscripciones;
        FILE *p = fopen("Inscripciones.dat", "rb");


        if (p == nullptr) {
            cout << "Error al abrir el archivo." << endl;
            return;
        }
        int cant = inscripciones.contarRegistros();
        int leidos = 0;


        Inscripcion obj_temporal;
        while (leidos < cant && fread(&obj_temporal, sizeof(Inscripcion), 1, p) == 1) {
            if (obj_temporal.getEstado()) {
                    if(obj_temporal.getFechaInscripcion().getAnio() == anio){
                        leidos++;
                }
            }
        }
        fclose(p);

        if (leidos == 0) {
            cout << "No hay inscripciones activas en ese curso en ese anio." << endl;
            return;
        } else {
        cout << "Total de inscripciones encontradas para el anio "<< anio << ": " << leidos << endl;
        }
}
void informeCursosPorProfesor(){
    // busco  todos los cursos que tengan  al legajodocente a cargo
    int legajo;
        while (true) {
        cout << "Ingrese un anio: ";
        if (cin >> legajo) {
            if (legajo > 0) {
                break;
            } else {
                cout << "El legajo docente debe ser positivo" << endl;
            }
        } else {
            cout << "INGRESE UN LEGAJO DOCENTE VALIDO:" << endl;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        }

        cout << "INFORME CANTIDAD CURSOS A CARGO DE DOCENTE LEGAJO " << legajo <<endl;

        ArchivoCursos cursos;
        FILE *p = fopen("Cursos.dat", "rb");


        if (p == nullptr) {
            cout << "Error al abrir el archivo." << endl;
            return;
        }

        Curso cursosDocente[1000] = {};
        int cant = cursos.contarRegistros();
        int leidos = 0;


        Curso obj_temporal;
        while (leidos < cant && fread(&obj_temporal, sizeof(Curso), 1, p) == 1) {
            if (obj_temporal.getEstado()) {
                    if(obj_temporal.getLegajoDocente() == legajo){
                        cursosDocente[leidos] = obj_temporal;
                        leidos++;
                }
            }
        }
        fclose(p);

        if (leidos == 0) {
            cout << "No hay inscripciones activas a cargo de ese docente." << endl;
            return;
        } else {
        cout << "Total de cursos a cargo del docente legajo  "<< legajo << ": " << leidos << endl;
        cout << "Detalle de cursos a cargo del docente:   "<< endl;
        int i;
        for (i=0; i < leidos; i++) {
            cursosDocente[i].Mostrar();
        }

        }


}

void informeAlumnoDeudores(){

    cout << "INFORME ALUMNOS DEUDORES"   <<endl;

    ArchivoInscripcion inscripciones;
    FILE *p = fopen("Inscripciones.dat", "rb");


    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int cant = inscripciones.contarRegistros();
    int leidos = 0;
    Inscripcion inscripcionesAlumnosDeudores[5000] = {};

    Inscripcion obj_temporal;
    while (leidos < cant && fread(&obj_temporal, sizeof(Inscripcion), 1, p) == 1) {
        if (obj_temporal.getEstado()) {
                if(obj_temporal.getMatriculaPaga() == false){
                   inscripcionesAlumnosDeudores[leidos] = obj_temporal;
                   leidos++;
            }
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay inscripciones activas en ese curso." << endl;
        return;
    } else {
        locate(1, 1); cout << "Total de alumnos deudores encontrados: " << leidos;
        locate(1, 2); cout << "Detalle de alumnos deudores: " << leidos;
        inscripciones.listarArrayOrdenadoPorCurso(inscripcionesAlumnosDeudores, leidos);
    }

}


