#include <iostream>
#include <cstdlib>
#include "ArchivoAlumnos.h"
#include "ArchivoCursos.h"
#include "MenuListados.h"
#include "MenuConsultas.h"
#include "MenuInformes.h"
#include "MenuABML.h"

using namespace std;

// ============= MENÚ DE ALUMNOS =============
/* void menuAlumnos() {
    ArchivoAlumnos arc;
    cout << "test" << endl;
    int opcion;
    do {
        system("cls");
        cout << "========== GESTION DE ALUMNOS ==========\n";
        cout << "1 - Agregar alumno\n";
        cout << "2 - Listar todos los alumnos\n";
        cout << "3 - Buscar alumno por legajo\n";
        cout << "4 - Modificar alumno\n";
        cout << "5 - Dar de baja alumno\n";
        cout << "0 - Volver al menu principal\n";
        cout << "========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: {
            Alumno obj;
            obj.Cargar();
            if (arc.grabarRegistro(obj))
                cout << "\nAlumno guardado exitosamente.\n";
            else
                cout << "\nError al guardar alumno.\n";
            system("pause");
            break;
        }
        case 2:
            cout << "\n========== LISTADO DE ALUMNOS ==========\n";
            arc.listar();
            system("pause");
            break;
        case 3: {
            int leg;
            cout << "\nIngrese legajo del alumno: ";
            cin >> leg;
            int pos = arc.buscarPorLegajo(leg);
            if (pos >= 0) {
                Alumno obj = arc.leerRegistro(pos);
                obj.Mostrar();
            } else {
                cout << "\nAlumno no encontrado.\n";
            }
            system("pause");
            break;
        }
        case 4: {
            int leg;
            cout << "\nIngrese legajo del alumno a modificar: ";
            cin >> leg;
            int pos = arc.buscarPorLegajo(leg);
            if (pos >= 0) {
                Alumno obj;
                cout << "\nIngrese los nuevos datos:\n";
                obj.Cargar();
                // Mantener el mismo legajo
                obj.setLegajo(leg);
                if (arc.grabarRegistro(obj)) // Nota: necesitarías un método modificar
                    cout << "\nAlumno modificado exitosamente.\n";
                else
                    cout << "\nError al modificar.\n";
            } else {
                cout << "\nAlumno no encontrado.\n";
            }
            system("pause");
            break;
        }
        case 5: {
            int leg;
            cout << "\nIngrese legajo del alumno a dar de baja: ";
            cin >> leg;
            int pos = arc.buscarPorLegajo(leg);
            if (pos >= 0) {
                Alumno obj = arc.leerRegistro(pos);
                obj.setEstado(false);
                // Aquí necesitarías modificarRegistro en ArchivoAlumnos
                cout << "\nAlumno dado de baja.\n";
            } else {
                cout << "\nAlumno no encontrado.\n";
            }
            system("pause");
            break;
        }
        }
    } while(opcion != 0);
}

// ============= MENÚ DE CURSOS =============
void menuCursos() {
    ArchivoCursos arc;
    int opcion;
    do {
        system("cls");
        cout << "=========== GESTION DE CURSOS ===========\n";
        cout << "1 - Agregar curso\n";
        cout << "2 - Listar todos los cursos\n";
        cout << "3 - Listar cursos activos\n";
        cout << "4 - Buscar curso por ID\n";
        cout << "5 - Modificar curso\n";
        cout << "6 - Dar de baja curso\n";
        cout << "7 - Listar cursos por capacidad maxima\n";
        cout << "8 - Listar cursos con cupo disponible\n";
        cout << "9 - Buscar cursos por docente\n";
        cout << "10 - Buscar cursos por anio\n";
        cout << "0 - Volver al menu principal\n";
        cout << "=========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: {
            Curso obj;
            obj.Cargar();
            if (arc.grabarRegistro(obj))
                cout << "\nCurso guardado exitosamente.\n";
            else
                cout << "\nError al guardar curso.\n";
            system("pause");
            break;
        }
        case 2:
            cout << "\n========== LISTADO DE CURSOS ==========\n";
            arc.listar();
            system("pause");
            break;
        case 3:
            cout << "\n========== CURSOS ACTIVOS ==========\n";
            arc.listarActivos();
            system("pause");
            break;
        case 4: {
            int id;
            cout << "\nIngrese ID del curso: ";
            cin >> id;
            int pos = arc.buscarPorId(id);
            if (pos >= 0) {
                Curso obj = arc.leerRegistro(pos);
                obj.Mostrar();
            } else {
                cout << "\nCurso no encontrado.\n";
            }
            system("pause");
            break;
        }
        case 5: {
            int id;
            cout << "\nIngrese ID del curso a modificar: ";
            cin >> id;
            int pos = arc.buscarPorId(id);
            if (pos >= 0) {
                Curso obj;
                cout << "\nIngrese los nuevos datos:\n";
                obj.Cargar();
                obj.setIdCurso(id); // Mantener el mismo ID
                if (arc.modificarRegistro(obj, pos))
                    cout << "\nCurso modificado exitosamente.\n";
                else
                    cout << "\nError al modificar.\n";
            } else {
                cout << "\nCurso no encontrado.\n";
            }
            system("pause");
            break;
        }
        case 6: {
            int id;
            cout << "\nIngrese ID del curso a dar de baja: ";
            cin >> id;
            int pos = arc.buscarPorId(id);
            if (pos >= 0) {
                Curso obj = arc.leerRegistro(pos);
                obj.setEstado(false);
                if (arc.modificarRegistro(obj, pos))
                    cout << "\nCurso dado de baja exitosamente.\n";
                else
                    cout << "\nError al dar de baja.\n";
            } else {
                cout << "\nCurso no encontrado.\n";
            }
            system("pause");
            break;
        }
        case 7:
            arc.listarPorMaxAlumnos();
            system("pause");
            break;
        case 8:
            arc.listarConCupoDisponible();
            system("pause");
            break;
        case 9: {
            int legajo;
            cout << "\nIngrese legajo del docente: ";
            cin >> legajo;
            arc.listarPorDocente(legajo);
            system("pause");
            break;
        }
        case 10: {
            int anio;
            cout << "\nIngrese anio: ";
            cin >> anio;
            arc.listarPorAnio(anio);
            system("pause");
            break;
        }
        }
    } while(opcion != 0);
}
*/
// ============= MENÚ PRINCIPAL =============
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
                    cout << "Saliendo del sistema...\n"<< endl;

                    break;
                default:
                    cout << "Opcion invalida. Intente nuevamente" << endl;
                    system("pause");
                    system("clear");
            }

    }


    return 0;
}
