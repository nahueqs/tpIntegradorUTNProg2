#include <iostream>
#include <cstdlib>
#include "ArchivoAlumnos.h"
#include "ArchivoCursos.h"

using namespace std;

// ============= MENÚ ABML ALUMNOS =============
void abmlAlumnos() {
    ArchivoAlumnos arc;
    int opcion;
    do {
        system("cls");
        cout << "==========================================\n";
        cout << "            ABML ALUMNOS\n";
        cout << "==========================================\n";
        cout << "1 - Alta de alumno\n";
        cout << "2 - Baja de alumno\n";
        cout << "3 - Modificar alumno\n";
        cout << "4 - Listar todos los alumnos\n";
        cout << "0 - Volver\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: {
            Alumno obj;
            obj.Cargar();
            bool legajoValido = arc.validarLegajoUnico(obj.getLegajo());
            bool dniValido = arc.validarDniUnico(obj.getDni());
            if (legajoValido && dniValido) {
                if (arc.grabarRegistro(obj))
                    cout << "\n*** ALUMNO GUARDADO EXITOSAMENTE ***\n";
                else
                    cout << "\n*** ERROR AL GUARDAR ALUMNO ***\n";
            } else {
                cout << "\n*** NO SE PUDO GUARDAR EL ALUMNO ***\n";
            }
            system("pause");
            break;
        }
        case 2: {
            int leg;
            cout << "\nIngrese legajo del alumno a dar de baja: ";
            cin >> leg;
            int pos = arc.buscarPorLegajo(leg);
            if (pos >= 0) {
                Alumno obj = arc.leerRegistro(pos);
                obj.setEstado(false);
                if (arc.modificarRegistro(obj, pos))
                    cout << "\n*** ALUMNO DADO DE BAJA EXITOSAMENTE ***\n";
                else
                    cout << "\n*** ERROR AL DAR DE BAJA ***\n";
            } else {
                cout << "\n*** ALUMNO NO ENCONTRADO ***\n";
            }
            system("pause");
            break;
        }
        case 3: {
            int leg;
            cout << "\nIngrese legajo del alumno a modificar: ";
            cin >> leg;
            int pos = arc.buscarPorLegajo(leg);
            if (pos >= 0) {
                Alumno obj = arc.leerRegistro(pos);
                cout << "\nDatos actuales:\n";
                obj.Mostrar();
                cout << "\nIngrese los nuevos datos:\n";
                Alumno nuevoObj;
                nuevoObj.Cargar();
                nuevoObj.setLegajo(leg);
                if (arc.modificarRegistro(nuevoObj, pos))
                    cout << "\n*** ALUMNO MODIFICADO EXITOSAMENTE ***\n";
                else
                    cout << "\n*** ERROR AL MODIFICAR ***\n";
            } else {
                cout << "\n*** ALUMNO NO ENCONTRADO ***\n";
            }
            system("pause");
            break;
        }
        case 4:
            arc.listar();
            system("pause");
            break;
        }
    } while(opcion != 0);
}

// ============= MENÚ ABML CURSOS =============
void abmlCursos() {
    ArchivoCursos arc;
    int opcion;
    do {
        system("cls");
        cout << "==========================================\n";
        cout << "             ABML CURSOS\n";
        cout << "==========================================\n";
        cout << "1 - Alta de curso\n";
        cout << "2 - Baja de curso\n";
        cout << "3 - Modificar curso\n";
        cout << "4 - Listar todos los cursos\n";
        cout << "0 - Volver\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: {
            Curso obj;
            obj.Cargar();
            if (arc.grabarRegistro(obj))
                cout << "\n*** CURSO GUARDADO EXITOSAMENTE ***\n";
            else
                cout << "\n*** ERROR AL GUARDAR CURSO ***\n";
            system("pause");
            break;
        }
        case 2: {
            int id;
            cout << "\nIngrese ID del curso a dar de baja: ";
            cin >> id;
            int pos = arc.buscarPorId(id);
            if (pos >= 0) {
                Curso obj = arc.leerRegistro(pos);
                obj.setEstado(false);
                if (arc.modificarRegistro(obj, pos))
                    cout << "\n*** CURSO DADO DE BAJA EXITOSAMENTE ***\n";
                else
                    cout << "\n*** ERROR AL DAR DE BAJA ***\n";
            } else {
                cout << "\n*** CURSO NO ENCONTRADO ***\n";
            }
            system("pause");
            break;
        }
        case 3: {
            int id;
            cout << "\nIngrese ID del curso a modificar: ";
            cin >> id;
            int pos = arc.buscarPorId(id);
            if (pos >= 0) {
                Curso obj;
                cout << "\nIngrese los nuevos datos:\n";
                obj.Cargar();
                obj.setIdCurso(id);
                if (arc.modificarRegistro(obj, pos))
                    cout << "\n*** CURSO MODIFICADO EXITOSAMENTE ***\n";
                else
                    cout << "\n*** ERROR AL MODIFICAR ***\n";
            } else {
                cout << "\n*** CURSO NO ENCONTRADO ***\n";
            }
            system("pause");
            break;
        }
        case 4:
            arc.listar();
            system("pause");
            break;
        }
    } while(opcion != 0);
}

// ============= MENÚ GESTIONES ABML =============
void menuGestionesABML() {
    int opcion;
    do {
        system("cls");
        cout << "==========================================\n";
        cout << "             MENU ABML\n";
        cout << "==========================================\n";
        cout << "1 - ABML Alumnos\n";
        cout << "2 - ABML Personal\n";
        cout << "3 - ABML Cargos\n";
        cout << "4 - ABML Cursos\n";
        cout << "5 - ABML Inscripciones\n";
        cout << "6 - ABML Asistencias\n";
        cout << "==========================================\n";
        cout << "0 - Volver al Menu Principal\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: abmlAlumnos(); break;
        case 2: cout << "\nABML Personal en desarrollo...\n"; system("pause"); break;
        case 3: cout << "\nABML Cargos en desarrollo...\n"; system("pause"); break;
        case 4: abmlCursos(); break;
        case 5: cout << "\nABML Inscripciones en desarrollo...\n"; system("pause"); break;
        case 6: cout << "\nABML Asistencias en desarrollo...\n"; system("pause"); break;
        }
    } while(opcion != 0);
}

// ============= MENÚ LISTADOS =============
void menuListados() {
    int opcion;
    do {
        system("cls");
        cout << "==========================================\n";
        cout << "              LISTADOS\n";
        cout << "==========================================\n";
        cout << "1 - Listado Personal\n";
        cout << "2 - Listado Alumnos\n";
        cout << "3 - Listado Cursos\n";
        cout << "4 - Listado Inscripciones\n";
        cout << "5 - Listado Cargos\n";
        cout << "==========================================\n";
        cout << "0 - Volver al Menu Principal\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: {
            int subopcion;
            system("cls");
            cout << "==========================================\n";
            cout << "           LISTADO PERSONAL\n";
            cout << "==========================================\n";
            cout << "1 - Listar por Turno\n";
            cout << "2 - Listar por Cargo\n";
            cout << "0 - Volver\n";
            cout << "==========================================\n";
            cout << "Opcion: ";
            cin >> subopcion;
            cout << "\nEn desarrollo...\n";
            system("pause");
            break;
        }
        case 2: {
            ArchivoAlumnos arc;
            int subopcion;
            system("cls");
            cout << "==========================================\n";
            cout << "           LISTADO ALUMNOS\n";
            cout << "==========================================\n";
            cout << "1 - Ordenados por Apellido\n";
            cout << "2 - Ordenados por DNI\n";
            cout << "3 - Ordenados por Legajo\n";
            cout << "0 - Volver\n";
            cout << "==========================================\n";
            cout << "Opcion: ";
            cin >> subopcion;
            switch(subopcion) {
            case 1: arc.listarPorApellido(); system("pause"); break;
            case 2: arc.listarPorDni(); system("pause"); break;
            case 3: arc.listar(); system("pause"); break;
            }
            break;
        }
        case 3: {
            ArchivoCursos arc;
            int subopcion;
            system("cls");
            cout << "==========================================\n";
            cout << "            LISTADO CURSOS\n";
            cout << "==========================================\n";
            cout << "1 - Listar por Curso\n";
            cout << "2 - Listar por Cantidad Maxima Alumno\n";
            cout << "0 - Volver\n";
            cout << "==========================================\n";
            cout << "Opcion: ";
            cin >> subopcion;
            switch(subopcion) {
            case 1: arc.listar(); system("pause"); break;
            case 2: arc.listarPorMaxAlumnos(); system("pause"); break;
            }
            break;
        }
        case 4:
            cout << "\nListado Inscripciones en desarrollo...\n";
            system("pause");
            break;
        case 5:
            cout << "\nListado Cargos en desarrollo...\n";
            system("pause");
            break;
        }
    } while(opcion != 0);
}

// ============= MENÚ CONSULTAS =============
void menuConsultas() {
    int opcion;
    do {
        system("cls");
        cout << "==========================================\n";
        cout << "              CONSULTAS\n";
        cout << "==========================================\n";
        cout << "1 - Consultar Asistencias\n";
        cout << "2 - Consultar Docentes\n";
        cout << "3 - Consultar Personal\n";
        cout << "4 - Consultar Alumnos\n";
        cout << "5 - Consultar Cursos\n";
        cout << "6 - Consultar Inscripciones\n";
        cout << "==========================================\n";
        cout << "0 - Volver al Menu Principal\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1:
            cout << "\nConsultar Asistencias en desarrollo...\n";
            system("pause");
            break;
        case 2:
            cout << "\nConsultar Docentes en desarrollo...\n";
            system("pause");
            break;
        case 3:
            cout << "\nConsultar Personal en desarrollo...\n";
            system("pause");
            break;
        case 4: {
            ArchivoAlumnos arc;
            int subopcion;
            system("cls");
            cout << "==========================================\n";
            cout << "         CONSULTAR ALUMNOS\n";
            cout << "==========================================\n";
            cout << "1 - Buscar por Legajo\n";
            cout << "2 - Buscar por DNI\n";
            cout << "0 - Volver\n";
            cout << "==========================================\n";
            cout << "Opcion: ";
            cin >> subopcion;
            if (subopcion == 1) {
                int leg;
                cout << "\nIngrese legajo: ";
                cin >> leg;
                int pos = arc.buscarPorLegajo(leg);
                if (pos >= 0) {
                    Alumno obj = arc.leerRegistro(pos);
                    obj.Mostrar();
                } else {
                    cout << "\n*** ALUMNO NO ENCONTRADO ***\n";
                }
                system("pause");
            } else if (subopcion == 2) {
                int dni;
                cout << "\nIngrese DNI: ";
                cin >> dni;
                int pos = arc.buscarPorDni(dni);
                if (pos >= 0) {
                    Alumno obj = arc.leerRegistro(pos);
                    obj.Mostrar();
                } else {
                    cout << "\n*** ALUMNO NO ENCONTRADO ***\n";
                }
                system("pause");
            }
            break;
        }
        case 5: {
            ArchivoCursos arc;
            int subopcion;
            system("cls");
            cout << "==========================================\n";
            cout << "          CONSULTAR CURSOS\n";
            cout << "==========================================\n";
            cout << "1 - Por cantidad de inscriptos\n";
            cout << "2 - Por costo de matricula\n";
            cout << "3 - Por numero de aula\n";
            cout << "4 - Por docente a cargo\n";
            cout << "0 - Volver\n";
            cout << "==========================================\n";
            cout << "Opcion: ";
            cin >> subopcion;

            if (subopcion == 3) {
                int aula;
                cout << "\nIngrese numero de aula: ";
                cin >> aula;
                int pos = arc.buscarPorAula(aula);
                if (pos >= 0) {
                    Curso obj = arc.leerRegistro(pos);
                    obj.Mostrar();
                } else {
                    cout << "\n*** CURSO NO ENCONTRADO EN ESA AULA ***\n";
                }
                system("pause");
            } else if (subopcion == 4) {
                int legajo;
                cout << "\nIngrese legajo del docente: ";
                cin >> legajo;
                arc.listarPorDocente(legajo);
                system("pause");
            } else {
                cout << "\nEn desarrollo...\n";
                system("pause");
            }
            break;
        }
        case 6:
            cout << "\nConsultar Inscripciones en desarrollo...\n";
            system("pause");
            break;
        }
    } while(opcion != 0);
}

// ============= MENÚ INFORMES =============
void menuInformes() {
    int opcion;
    do {
        system("cls");
        cout << "==========================================\n";
        cout << "              INFORMES\n";
        cout << "==========================================\n";
        cout << "1 - Recaudacion anual de todos los cursos\n";
        cout << "2 - Recaudacion por curso\n";
        cout << "3 - Informe Anual de alumnos inscriptos por curso\n";
        cout << "4 - Informe anual de alumnos deudores por curso\n";
        cout << "==========================================\n";
        cout << "0 - Volver al Menu Principal\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1:
            cout << "\nInforme en desarrollo...\n";
            system("pause");
            break;
        case 2:
            cout << "\nInforme en desarrollo...\n";
            system("pause");
            break;
        case 3:
            cout << "\nInforme en desarrollo...\n";
            system("pause");
            break;
        case 4:
            cout << "\nInforme en desarrollo...\n";
            system("pause");
            break;
        }
    } while(opcion != 0);
}

// ============= MENÚ PRINCIPAL =============
int main() {
    int opcion;
    do {
        system("cls");
        cout << "==========================================\n";
        cout << "     SISTEMA DE GESTION DE COLEGIO\n";
        cout << "==========================================\n";
        cout << "1 - Listados\n";
        cout << "2 - Consultas\n";
        cout << "3 - Informes y Reportes\n";
        cout << "4 - Gestiones ABML\n";
        cout << "==========================================\n";
        cout << "0 - Salir del sistema\n";
        cout << "==========================================\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
        case 1: menuListados(); break;
        case 2: menuConsultas(); break;
        case 3: menuInformes(); break;
        case 4: menuGestionesABML(); break;
        case 0: cout << "\nSaliendo del sistema...\n"; break;
        default: cout << "\nOpcion invalida.\n"; system("pause");
        }
    } while(opcion != 0);

    return 0;
}
