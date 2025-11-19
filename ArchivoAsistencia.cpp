#include "ArchivoAsistencia.h"
#include "ArchivoInscripcion.h"
#include "ArchivoAlumnos.h"
#include "ArchivoCursos.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "rlutil.h"

using namespace std;
using namespace rlutil;


ArchivoAsistencia::ArchivoAsistencia(const char* nombre) {
    strncpy(_nombre, nombre, 29);
    _nombre[29] = '\0';
}


 /// basicos
int ArchivoAsistencia::contarRegistros() {
    FILE *p = fopen("Asistencias.dat", "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Asistencia);
}

bool ArchivoAsistencia::grabarRegistro(Asistencia obj) {
    FILE *p = fopen("Asistencias.dat", "ab");
    if (p == nullptr) return false;
    bool ok = fwrite(&obj, sizeof(Asistencia), 1, p);
    fclose(p);
    return ok;
}

Asistencia ArchivoAsistencia::leerRegistro(int pos) {
    Asistencia obj;
    obj.setLegajoAlumno(0);
    obj.setEstado(false);

    FILE *p = fopen("Asistencias.dat", "rb");
    if (p == nullptr) return obj;

    fseek(p, pos * sizeof(Asistencia), SEEK_SET);
    fread(&obj, sizeof(Asistencia), 1, p);
    fclose(p);
    return obj;
}

bool ArchivoAsistencia::modificarRegistro(Asistencia obj, int pos) {
    FILE *p = fopen("Asistencias.dat", "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Asistencia), SEEK_SET);
    bool ok = fwrite(&obj, sizeof(Asistencia), 1, p);
    fclose(p);
    return ok;
}

/// Busqquedas
int ArchivoAsistencia::buscarAsistencia(int legajo, int idCurso, Fecha fecha) {
    FILE *p = fopen("Asistencias.dat", "rb");
    if (p == nullptr) return -1;

    Asistencia obj;
    int pos = 0;
    while (fread(&obj, sizeof(Asistencia), 1, p)) {
        if (obj.getEstado() &&
            obj.getLegajoAlumno() == legajo &&
            obj.getIdCurso() == idCurso &&
            obj.getFecha().getDia() == fecha.getDia() &&
            obj.getFecha().getMes() == fecha.getMes() &&
            obj.getFecha().getAnio() == fecha.getAnio()) {

            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}


/// alta  y cambio de asistencias
void ArchivoAsistencia::tomarAsistencia() {
    cout << "--- TOMAR ASISTENCIA ---" << endl;

    int idCurso;
    while (true) {
        cout << "Ingrese ID del Curso: " << endl;
        if (cin >> idCurso) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    ArchivoCursos adminCursos("Cursos.dat");
    Curso c = adminCursos.buscarYLeerPorId(idCurso);
    if (c.getIdCurso() == -1 || !c.getEstado()) {
        cout << "*** Curso no encontrado o inactivo. ***" << endl;
        return;
    }
    cout << "Curso seleccionado: " << c.getDescripcion() << endl;

    cout << "Ingrese la Fecha de la clase:" << endl;
    Fecha fechaClase;
    fechaClase.Cargar();
    cin.ignore(10000, '\n');

    FILE *pInsc = fopen("Inscripciones.dat", "rb");
    if (pInsc == nullptr) {
        cout << "No hay inscripciones registradas." << endl;
        return;
    }


    ArchivoAlumnos adminAlumnos("Alumnos.dat");

    Inscripcion insc;
    int procesados = 0;
    int presentes = 0;

    cout << endl << "--- COMENZANDO LISTA ---" << endl;

    while (fread(&insc, sizeof(Inscripcion), 1, pInsc)) {
        if (insc.getIdCurso() == idCurso && insc.getEstado()) {

            int legajo = insc.getLegajoAlumno();

            if (buscarAsistencia(legajo, idCurso, fechaClase) >= 0) {
                continue;
            }


            Alumno alu = adminAlumnos.buscarYLeerPorLegajo(legajo);

            int opcion;
            while(true){
                cout << "Alumno: " << alu.getApellido() << ", " << alu.getNombre() << " (Leg: " << legajo << ")" << endl;
                cout << "Esta Presente? (1: SI / 0: NO): ";
                if(cin >> opcion && (opcion == 0 || opcion == 1)) break;
                cout << "Opcion invalida. Ingrese 1 o 0." << endl;
                cin.clear(); cin.ignore(10000, '\n');
            }

            Asistencia nuevaAsis;
            nuevaAsis.setLegajoAlumno(legajo);
            nuevaAsis.setIdCurso(idCurso);
            nuevaAsis.setFecha(fechaClase);
            nuevaAsis.setPresente(opcion == 1);
            nuevaAsis.setEstado(true);

            if (grabarRegistro(nuevaAsis)) {
                procesados++;
                if(opcion == 1) presentes++;
            }
            cout << "-----------------------" << endl;
        }
    }
    fclose(pInsc);

    if (procesados == 0) {
        cout << "No se procesaron alumnos (curso vacio o ya se tomo lista completa)." << endl;
    } else {
        cout << endl << "--- FIN DE LA LISTA ---" << endl;
        cout << "Total Procesados: " << procesados << endl;
        cout << "Total Presentes: " << presentes << endl;
    }
}

void ArchivoAsistencia::modificarAsistencia() {
    cout << "--- MODIFICAR ASISTENCIA (RECTIFICAR) ---" << endl;

    int legajo, idCurso;

    while (true) {
        cout << "Ingrese Legajo del Alumno: " << endl;
        if (cin >> legajo) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }
    while (true) {
        cout << "Ingrese ID del Curso: " << endl;
        if (cin >> idCurso) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }


    cout << "Ingrese la Fecha de la asistencia a modificar:" << endl;
    Fecha fechaBuscada;
    fechaBuscada.Cargar();
    cin.ignore(10000, '\n');


    int pos = buscarAsistencia(legajo, idCurso, fechaBuscada);

    if (pos < 0) {
        cout << "*** No se encontro un registro de asistencia para esos datos. ***" << endl;
        return;
    }


    Asistencia obj = leerRegistro(pos);


    ArchivoAlumnos adminAlu("Alumnos.dat");
    Alumno alu = adminAlu.buscarYLeerPorLegajo(legajo);

    cout << endl << "========== REGISTRO ACTUAL ==========" << endl;
    cout << "Alumno: " << alu.getApellido() << ", " << alu.getNombre() << endl;
    cout << "Fecha: "; obj.getFecha().Mostrar(); cout << endl;
    cout << "Estado Actual: " << (obj.getPresente() ? "PRESENTE" : "AUSENTE") << endl;
    cout << "-------------------------------------" << endl;


    int nuevaCondicion;
    while (true) {
        cout << "Ingrese EL CAMBIIO (1: PRESENTE / 0: AUSENTE): " << endl;
        if (cin >> nuevaCondicion && (nuevaCondicion == 0 || nuevaCondicion == 1)) break;
        cout << "*** ERROR: Debe ingresar 1 o 0. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    if (obj.getPresente() != (nuevaCondicion == 1)) {
        obj.setPresente(nuevaCondicion == 1);

        if (modificarRegistro(obj, pos)) {
            cout << "La asistencia ha sido rectificada exitosamente." << endl;
        } else {
            cout << "*** ERROR: No se pudo guardar el cambio. ***" << endl;
        }
    } else {
        cout << "La condicion ingresada es la misma que la actual. No se hicieron cambios." << endl;
    }
}

/// listados

void ArchivoAsistencia::listarPorCursoYFecha() {
    cout << "--- LISTAR ASISTENCIA POR CURSO Y FECHA ---" << endl;
    int idCurso;
    while (true) {
        cout << "Ingrese ID Curso: " << endl;
        if (cin >> idCurso) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    cout << "Ingrese Fecha: " << endl;
    Fecha f;
    f.Cargar();
    cin.ignore(10000, '\n');

    FILE *p = fopen("Asistencias.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir archivo de asistencias." << endl;
        return;
    }

    Asistencia obj;

    ArchivoAlumnos adminAlu("Alumnos.dat");

    bool encontro = false;
    cout << endl << "========== PLANILLA DE ASISTENCIA ==========" << endl << endl;

    int fila = 10;
    locate(1, fila); cout << "LEGAJO";
    locate(12, fila); cout << "APELLIDO";
    locate(33, fila); cout << "NOMBRE";
    locate(55, fila); cout << "CONDICION";
    fila++;
    locate(1, fila); cout << "----------------------------------------------------------------" << endl;
    fila++;

    while(fread(&obj, sizeof(Asistencia), 1, p)) {
        if(obj.getEstado() &&
           obj.getIdCurso() == idCurso &&
           obj.getFecha().getDia() == f.getDia() &&
           obj.getFecha().getMes() == f.getMes() &&
           obj.getFecha().getAnio() == f.getAnio()) {

               encontro = true;

               Alumno alu = adminAlu.buscarYLeerPorLegajo(obj.getLegajoAlumno());

               locate(1, fila);  cout << obj.getLegajoAlumno();
               locate(12, fila); cout << alu.getApellido();
               locate(33, fila); cout << alu.getNombre();

               if(obj.getPresente()) {
                   locate(55, fila); cout << "PRESENTE";
               } else {
                   locate(55, fila); cout << "AUSENTE";
               }
               fila++;
           }
    }
    fclose(p);

    locate(1, fila + 2);
    if (!encontro) {
        cout << "No hay registros de asistencia para esa fecha y curso." << endl;
    }
    cout << endl;
}

void ArchivoAsistencia::listarPorAlumnoYCurso() {
    cout << "--- HISTORIAL DE ALUMNO EN CURSO ---" << endl;
    int legajo, idCurso;

    while (true) {
        cout << "Ingrese Legajo Alumno: " << endl;
        if (cin >> legajo) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }
    while (true) {
        cout << "Ingrese ID Curso: " << endl;
        if (cin >> idCurso) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    FILE *p = fopen("Asistencias.dat", "rb");
    if (p == nullptr) return;

    Asistencia obj;
    bool encontro = false;
    int totalClases = 0;
    int totalPresentes = 0;

    cout << endl << "========== HISTORIAL DE ASISTENCIA ==========" << endl << endl;

    int fila = 10;
    locate(1, fila); cout << "FECHA";
    locate(20, fila); cout << "CONDICION";
    fila++;
    locate(1, fila); cout << "----------------------------------------" << endl;
    fila++;

    while(fread(&obj, sizeof(Asistencia), 1, p)) {
        if(obj.getEstado() && obj.getLegajoAlumno() == legajo && obj.getIdCurso() == idCurso) {
            encontro = true;
            totalClases++;
            if(obj.getPresente()) totalPresentes++;

            locate(1, fila);
            obj.getFecha().Mostrar();

            locate(20, fila);
            cout << (obj.getPresente() ? "PRESENTE" : "AUSENTE");

            fila++;
        }
    }
    fclose(p);

    locate(1, fila + 2);
    if (!encontro) {
        cout << "No hay registros de asistencia para este alumno en este curso." << endl;
    } else {
        cout << "Total Clases: " << totalClases << endl;
        cout << "Presentes: " << totalPresentes << endl;
        cout << "Ausentes: " << (totalClases - totalPresentes) << endl;
    }
    cout << endl;
}

void ArchivoAsistencia::listarPorAlumnoCursoYFecha() {
    cout << "--- CONSULTAR ASISTENCIA ESPECIFICA ---" << endl;
    int legajo, idCurso;

    while (true) {
        cout << "Ingrese Legajo Alumno: " << endl;
        if (cin >> legajo) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }
    while (true) {
        cout << "Ingrese ID Curso: " << endl;
        if (cin >> idCurso) break;
        cout << "*** ERROR: Ingrese numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    cout << "Ingrese Fecha: " << endl;
    Fecha f;
    f.Cargar();
    cin.ignore(10000, '\n');

    int pos = buscarAsistencia(legajo, idCurso, f);

    if (pos >= 0) {
        Asistencia obj = leerRegistro(pos);
        cout << endl << "========== REGISTRO ENCONTRADO ==========" << endl;
        cout << "Fecha: "; obj.getFecha().Mostrar(); cout << endl;
        cout << "Condicion: " << (obj.getPresente() ? "PRESENTE" : "AUSENTE") << endl;
        cout << "-----------------------------------------" << endl;
    } else {
        cout << endl << "No se encontro registro de asistencia para esos datos." << endl;
    }
    cout << endl;
}
