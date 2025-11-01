#include <iostream>
#include <cstdlib>
#include "ArchivoAlumnos.h"
#include "ArchivoCursos.h"

using namespace std;

// ============= MENÚ DE ALUMNOS =============
void menuAlumnos() {
    ArchivoAlumnos arc;
    int opcion;
    do {
        system("cls");
        cout << "========== GESTION DE ALUMNOS ==========\n";
        cout << "1 - Agregar alumno\n";
        cout << "2 - Listar todos los alumnos\n";
        cout << "3 - Buscar alumno por LEGAJO\n";
        cout << "4 - Buscar alumno por DNI\n";
        cout << "5 - Modificar alumno\n";
        cout << "6 - Dar de baja alumno\n";
        cout << "7 - Listar por apellido\n";
        cout << "8 - Listar por DNI\n";
        cout << "9 - Listar solo activos\n";
        cout << "0 - Volver al menu principal\n";
        cout << "========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: {
            Alumno obj;
            obj.Cargar();

            // VALIDAR QUE EL LEGAJO Y DNI SEAN ÚNICOS
            bool legajoValido = arc.validarLegajoUnico(obj.getLegajo());
            bool dniValido = arc.validarDniUnico(obj.getDni());

            if (legajoValido && dniValido) {
                if (arc.grabarRegistro(obj)) {
                    cout << "\n*** ALUMNO GUARDADO EXITOSAMENTE ***\n";
                } else {
                    cout << "\n*** ERROR AL GUARDAR ALUMNO ***\n";
                }
            } else {
                cout << "\n*** NO SE PUDO GUARDAR EL ALUMNO ***\n";
                cout << "El legajo o DNI ya existen en el sistema.\n";
            }
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
                cout << "\n*** ALUMNO NO ENCONTRADO ***\n";
            }
            system("pause");
            break;
        }
        case 4: {
            int dni;
            cout << "\nIngrese DNI del alumno: ";
            cin >> dni;
            int pos = arc.buscarPorDni(dni);
            if (pos >= 0) {
                Alumno obj = arc.leerRegistro(pos);
                obj.Mostrar();
            } else {
                cout << "\n*** ALUMNO NO ENCONTRADO ***\n";
            }
            system("pause");
            break;
        }
        case 5: {
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
        case 6: {
            int leg;
            cout << "\nIngrese legajo del alumno a dar de baja: ";
            cin >> leg;
            int pos = arc.buscarPorLegajo(leg);
            if (pos >= 0) {
                Alumno obj = arc.leerRegistro(pos);
                obj.setEstado(false);
                if (arc.modificarRegistro(obj, pos)) {
                    cout << "\n*** ALUMNO DADO DE BAJA EXITOSAMENTE ***\n";
                } else {
                    cout << "\n*** ERROR AL DAR DE BAJA ***\n";
                }
            } else {
                cout << "\n*** ALUMNO NO ENCONTRADO ***\n";
            }
            system("pause");
            break;
        }
        case 7:
            arc.listarPorApellido();
            system("pause");
            break;
        case 8:
            arc.listarPorDni();
            system("pause");
            break;
        case 9:
            arc.listarActivos();
            system("pause");
            break;
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
            cout << "\nIngrese año: ";
            cin >> anio;
            arc.listarPorAnio(anio);
            system("pause");
            break;
        }
        }
    } while(opcion != 0);
}

// ============= MENÚ PRINCIPAL =============
int main() {
    int opcion;
    do {
        system("cls");
        cout << "======================================\n";
        cout << "   SISTEMA DE GESTION DE COLEGIO\n";
        cout << "======================================\n";
        cout << "1 - Gestion de Alumnos\n";
        cout << "2 - Gestion de Cursos\n";
        cout << "3 - Gestion de Inscripciones (En desarrollo)\n";
        cout << "4 - Gestion de Personal (En desarrollo)\n";
        cout << "5 - Gestion de Asistencias (En desarrollo)\n";
        cout << "6 - Informes y Reportes (En desarrollo)\n";
        cout << "0 - Salir del sistema\n";
        cout << "======================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1:
            menuAlumnos();
            break;
        case 2:
            menuCursos();
            break;
        case 3:
            cout << "\nModulo de Inscripciones en desarrollo...\n";
            system("pause");
            break;
        case 4:
            cout << "\nModulo de Personal en desarrollo...\n";
            system("pause");
            break;
        case 5:
            cout << "\nModulo de Asistencias en desarrollo...\n";
            system("pause");
            break;
        case 6:
            cout << "\nModulo de Informes en desarrollo...\n";
            system("pause");
            break;
        case 0:
            cout << "\nSaliendo del sistema...\n";
            break;
        default:
            cout << "\nOpcion invalida. Intente nuevamente.\n";
            system("pause");
        }
    } while(opcion != 0);

    return 0;
}
