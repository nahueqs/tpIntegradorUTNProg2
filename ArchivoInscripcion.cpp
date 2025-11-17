#include "ArchivoInscripcion.h"
#include "ArchivoAlumnos.h"
#include "ArchivoCursos.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "rlutil.h"

using namespace std;
using namespace rlutil;

ArchivoInscripcion::ArchivoInscripcion(const char* nombre) {
    strncpy(_nombre, nombre, 29);
    _nombre[29] = '\0';
}

int ArchivoInscripcion::contarRegistros() {
    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Inscripcion);
}

bool ArchivoInscripcion::grabarRegistro(Inscripcion obj) {
    FILE *p = fopen("Inscripciones.dat", "ab");
    if (p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof(Inscripcion), 1, p);
    fclose(p);
    return escribio;
}

Inscripcion ArchivoInscripcion::leerRegistro(int pos) {
    Inscripcion obj;
    obj.setIdInscripcion(-1);
    obj.setEstado(false);

    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        return obj;
    }

    fseek(p, pos * sizeof(Inscripcion), SEEK_SET);
    fread(&obj, sizeof(Inscripcion), 1, p);

    fclose(p);
    return obj;
}

bool ArchivoInscripcion::modificarRegistro(Inscripcion obj, int pos) {
    FILE *p = fopen("Inscripciones.dat", "rb+");
    if (p == nullptr) {
        return false;
    }

    fseek(p, pos * sizeof(Inscripcion), SEEK_SET);
    bool escribio = fwrite(&obj, sizeof(Inscripcion), 1, p);

    fclose(p);
    return escribio;
}



int ArchivoInscripcion::generarNuevoIdInscripcion() {
    return contarRegistros() + 1;
}

//// busquedas

int ArchivoInscripcion::buscarPorId(int id) {
    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        return -1;
    }
    Inscripcion obj;
    int pos = 0;
    while (fread(&obj, sizeof(Inscripcion), 1, p)) {
        if (obj.getIdInscripcion() == id) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}

int ArchivoInscripcion::buscarInscripcionDuplicada(int legajoAlumno, int idCurso) {
    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        return -1;
    }
    Inscripcion obj;
    int pos = 0;
    while (fread(&obj, sizeof(Inscripcion), 1, p)) {
        if (obj.getLegajoAlumno() == legajoAlumno && obj.getIdCurso() == idCurso && obj.getEstado() == true) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}


int ArchivoInscripcion::contarInscriptos(int idCurso) {
    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        return 0;
    }

    Inscripcion obj;
    int contador = 0;
    while (fread(&obj, sizeof(Inscripcion), 1, p)) {
        if (obj.getIdCurso() == idCurso && obj.getEstado() == true) {
            contador++;
        }
    }
    fclose(p);
    return contador;
}


 /// alta baja cancelar deuda

void ArchivoInscripcion::inscribirAlumno() {
    cout << "--- NUEVA INSCRIPCION DE ALUMNO ---" << endl;

    Inscripcion nuevaInscripcion;

    if (!nuevaInscripcion.Cargar()) {
        cout << "Inscripcion cancelada por el usuario." << endl;
        return;
    }

    int legajoAlumno = nuevaInscripcion.getLegajoAlumno();
    int idCurso = nuevaInscripcion.getIdCurso();


    // 1. Validar que no exista ya una inscripción duplicada
    if (buscarInscripcionDuplicada(legajoAlumno, idCurso) >= 0) {
        cout << "*** ERROR: El alumno ya se encuentra inscripto en este curso. ***" << endl;
        return;
    }

    /// aca validamos que exista el alumno con ese legajo y que este activo
    ArchivoAlumnos adminAlumnos("Alumnos.dat");
    int posAlumno = adminAlumnos.buscarPorLegajo(legajoAlumno);
    if (posAlumno < 0) {
        cout << "*** ERROR: No se encontro un Alumno con el legajo " << legajoAlumno << ". ***" << endl;
        return;
    }
    Alumno alu = adminAlumnos.leerRegistro(posAlumno);
    if (!alu.getEstado()) {
        cout << "*** ERROR: El Alumno con legajo " << legajoAlumno << " se encuentra inactivo. ***" << endl;
        return;
    }

    /// aca validamos que este el curso y este activo
    ArchivoCursos adminCursos("Cursos.dat");
    int posCurso = adminCursos.buscarPorId(idCurso);
    if (posCurso < 0) {
        cout << "*** ERROR: No se encontro un Curso con el ID " << idCurso << ". ***" << endl;
        return;
    }
    Curso cur = adminCursos.leerRegistro(posCurso);
    if (!cur.getEstado()) {
        cout << "*** ERROR: El Curso con ID " << idCurso << " se encuentra inactivo. ***" << endl;
        return;
    }

    // aca validamos si es que hay espacio para inscribirse
    int cupoMaximo = cur.getMaxAlumnos();
    int inscriptosActuales = contarInscriptos(idCurso);

    if (inscriptosActuales >= cupoMaximo) {
        cout << "*** ERROR: El Curso '" << cur.getDescripcion() << "' no tiene mas cupo. ***" << endl;
        cout << "Inscriptos: " << inscriptosActuales << " / Maximo: " << cupoMaximo << endl;
        return;
    }

    /// aca ingresa el monto para pgar

    float costoReal = cur.getCostoMatricula();
    float montoPagado;

    cout << "--- PAGO DE MATRICULA ---" << endl;
    cout << "El costo total de la matricula es: $" << costoReal << endl;

    while (true) {
        cout << "Ingrese el monto a pagar ahora: " << endl;
        if (cin >> montoPagado && montoPagado >= 0) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar un monto numerico positivo. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    /// aca seteamos si pago todo o no
    if (montoPagado >= costoReal) {
        nuevaInscripcion.setMatriculaPaga(true);
        nuevaInscripcion.setTotalPagado(costoReal);
        cout << "Pago completo registrado." << endl;

    } else {
        nuevaInscripcion.setMatriculaPaga(false);
        nuevaInscripcion.setTotalPagado(montoPagado);
        cout << "Se ha registrado un pago parcial." << endl;
        cout << "Saldo restante: $" << (costoReal - montoPagado) << endl;
    }

    //// ahora ya con todo validado todo clean aca solo es rellenar
    nuevaInscripcion.setIdInscripcion(generarNuevoIdInscripcion());
    nuevaInscripcion.setImporteMatricula(costoReal);
    nuevaInscripcion.setEstado(true);

    cout << "--- RESUMEN DE INSCRIPCION ---" << endl;
    cout << "Alumno: " << alu.getApellido() << ", " << alu.getNombre() << endl;
    cout << "Curso: " << cur.getDescripcion() << endl;
    cout << "Importe de Matricula (Costo Total): $" << costoReal << endl;
    cout << "Importe abonado: $" << nuevaInscripcion.getTotalPagado() << endl;
    cout << "Estado de Pago: " << (nuevaInscripcion.getMatriculaPaga() ? "PAGADO" : "PENDIENTE") << endl;
    cout << "--------------------------------" << endl;

    int confirmacion;
    cout << "Confirma la inscripcion? (1: SI / 0: NO): " << endl;
    cin >> confirmacion;

    if (confirmacion != 1) {
        cout << "Inscripcion cancelada." << endl;
        return;
    }

    if (grabarRegistro(nuevaInscripcion)) {
        cout << "¡Alumno inscripto exitosamente!" << endl;
    } else {
        cout << "*** ERROR: No se pudo grabar la inscripcion. ***" << endl;
    }
}

void ArchivoInscripcion::anularInscripcion() {
    cout << "--- ANULAR INSCRIPCION ---" << endl;
    int legajoAlumno, idCurso;

    while (true) {
        cout << "Ingrese Legajo del Alumno: " << endl;
        if (cin >> legajoAlumno && legajoAlumno > 0){
            break;
        }else {
        cout << "*** ERROR: Legajo invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
        }
    }
    while (true) {
        cout << "Ingrese ID del Curso: " << endl;
        if (cin >> idCurso && idCurso > 0){
            break;
        }
        else{
        cout << "*** ERROR: ID invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
        }
    }


    int pos = buscarInscripcionDuplicada(legajoAlumno, idCurso);

    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro una inscripcion ACTIVA para ese alumno en ese curso. ***" << endl;
        return;
    }

    Inscripcion obj = leerRegistro(pos);
    cout << "Se encontro la siguiente inscripcion activa:" << endl;
    obj.Mostrar();
    cout << "--------------------------------" << endl;

    int confirmacion;
    cout << "Esta seguro que desea ANULAR esta inscripcion? (1 - SI / 0 - NO): " << endl;
    cin >> confirmacion;

    if (confirmacion == 1) {
        obj.setEstado(false);
        if (modificarRegistro(obj, pos)) {
            cout << "La inscripcion fue anulada exitosamente." << endl;
        } else {
            cout << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void ArchivoInscripcion::cancelarDeuda() {
    cout << "--- REGISTRAR PAGO DE MATRICULA ---" << endl;
    int legajoAlumno, idCurso;

    while (true) {
        cout << "Ingrese Legajo del Alumno: " << endl;
        if (cin >> legajoAlumno && legajoAlumno > 0){
            break;
        }else {
        cout << "*** ERROR: Legajo invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
        }
    }
    while (true) {
        cout << "Ingrese ID del Curso: " << endl;
        if (cin >> idCurso && idCurso > 0){
            break;
        }
        else{
        cout << "*** ERROR: ID invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
        }
    }

    int pos = buscarInscripcionDuplicada(legajoAlumno, idCurso);

    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro una inscripcion ACTIVA para ese alumno en ese curso. ***" << endl;
        return;
    }

    Inscripcion obj = leerRegistro(pos);
    cout << "Se encontro la siguiente inscripcion activa:" << endl;
    obj.Mostrar();
    cout << "--------------------------------" << endl;

    if (obj.getMatriculaPaga()) {
        cout << "Esta matricula ya se encuentra pagada." << endl;
        return;
    }

    int confirmacion;
    cout << "Desea marcar esta matricula como PAGADA? (1 - SI / 0 - NO): " << endl;
    cin >> confirmacion;

    if (confirmacion == 1) {
        obj.setMatriculaPaga(true);
        if (modificarRegistro(obj, pos)) {
            cout << "El pago fue registrado exitosamente." << endl;
        } else {
            cout << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

/// consultas

void ArchivoInscripcion::consultarPorId() {
    cout << "--- CONSULTAR INSCRIPCION POR ID ---" << endl;
    int id;
    while (true) {
        cout << "Ingrese el ID de la Inscripcion: " << endl;
        if (cin >> id) break;
        cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    int pos = buscarPorId(id);
    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro una inscripcion con el ID " << id << ". ***" << endl;
        return;
    }

    cout << "Se encontro el siguiente registro:" << endl;
    Inscripcion obj = leerRegistro(pos);
    obj.Mostrar();
    cout << "--------------------------------" << endl;
}

void ArchivoInscripcion::consultarPorAlumnoYCurso() {
    cout << "--- CONSULTAR INSCRIPCION (ALUMNO + CURSO) ---" << endl;
    int legajoAlumno, idCurso;

    while (true) {
        cout << "Ingrese Legajo del Alumno: " << endl;
        if (cin >> legajoAlumno && legajoAlumno > 0) break;
        cout << "*** ERROR: Legajo invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }
    while (true) {
        cout << "Ingrese ID del Curso: " << endl;
        if (cin >> idCurso && idCurso > 0) break;
        cout << "*** ERROR: ID invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    // Usamos la búsqueda de duplicados que solo trae activos
    int pos = buscarInscripcionDuplicada(legajoAlumno, idCurso);

    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro una inscripcion ACTIVA para ese alumno en ese curso. ***" << endl;
        return;
    }

    cout << "Se encontro la siguiente inscripcion activa:" << endl;
    Inscripcion obj = leerRegistro(pos);
    obj.Mostrar();
    cout << "--------------------------------" << endl;
}


/// listados

void ArchivoInscripcion::listarActivas() {
    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    ArchivoAlumnos adminAlumnos("Alumnos.dat");
    ArchivoCursos adminCursos("Cursos.dat");

    Inscripcion obj;
    bool encontro = false;

    cout << "========== LISTADO DE INSCRIPCIONES ACTIVAS ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "ID INSC.";
    locate(11, fila); cout << "ALUMNO (Legajo)";
    locate(28, fila); cout << "CURSO (ID)";
    locate(40, fila); cout << "DESCRIPCION CURSO";
    locate(65, fila); cout << "PAGO";
    locate(70, fila);cout << "$ PAGADO";
    fila++;
    locate(1, fila); cout << "-----------------------------------------------------------------------------" << endl;
    fila++;

    while (fread(&obj, sizeof(Inscripcion), 1, p)) {
        if (obj.getEstado()) {
            encontro = true;

            Curso cur = adminCursos.buscarYLeerPorId(obj.getIdCurso());

            locate(1, fila);  cout << obj.getIdInscripcion();
            locate(11, fila); cout << obj.getLegajoAlumno();
            locate(28, fila); cout << obj.getIdCurso();
            locate(40, fila); cout << cur.getDescripcion();
            locate(65, fila); cout << (obj.getMatriculaPaga() ? "SI" : "NO");
            locate(70, fila); cout << (obj.getTotalPagado());
            fila++;
        }
    }
    fclose(p);
    locate(1, fila + 2);

    if (!encontro) {
        cout << "No hay inscripciones activas para mostrar." << endl;
    }
    cout << endl;
}

void ArchivoInscripcion::listarInactivas() {
    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    ArchivoCursos adminCursos("Cursos.dat");
    Inscripcion obj;
    bool encontro = false;

    cout << "========== LISTADO DE INSCRIPCIONES INACTIVAS (ANULADAS) ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "ID INSC.";
    locate(11, fila); cout << "ALUMNO (Legajo)";
    locate(28, fila); cout << "CURSO (ID)";
    locate(40, fila); cout << "DESCRIPCION CURSO";
    fila++;
    locate(1, fila); cout << "-----------------------------------------------------------------------------" << endl;
    fila++;

    while (fread(&obj, sizeof(Inscripcion), 1, p)) {
        if (!obj.getEstado()) {
            encontro = true;
            Curso cur = adminCursos.buscarYLeerPorId(obj.getIdCurso());

            locate(1, fila);  cout << obj.getIdInscripcion();
            locate(11, fila); cout << obj.getLegajoAlumno();
            locate(28, fila); cout << obj.getIdCurso();
            locate(40, fila); cout << cur.getDescripcion();

            fila++;
        }
    }
    fclose(p);
    locate(1, fila + 2);

    if (!encontro) {
        cout << "No hay inscripciones inactivas para mostrar." << endl;
    }
    cout << endl;
}

void ArchivoInscripcion::listarPorCurso() {
    cout << "--- LISTAR INSCRIPTOS POR CURSO ---" << endl;
    int idCurso;
    while (true) {
        cout << "Ingrese ID del Curso: " << endl;
        if (cin >> idCurso && idCurso > 0) break;
        cout << "*** ERROR: ID invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }

    ArchivoCursos adminCursos("Cursos.dat");
    Curso cur = adminCursos.buscarYLeerPorId(idCurso);
    if (cur.getIdCurso() == -1) {
        cout << "*** ERROR: No existe un curso con ese ID. ***" << endl;
        return;
    }

    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    ArchivoAlumnos adminAlumnos("Alumnos.dat");
    Inscripcion obj;
    bool encontro = false;

    cout << "========== INSCRIPTOS ACTIVOS EN: " << cur.getDescripcion() << " ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "LEGAJO";
    locate(10, fila); cout << "APELLIDO";
    locate(30, fila); cout << "NOMBRE";
    locate(50, fila); cout << "PAGO";
    locate(55, fila);cout << "$ PAGADO";
    fila++;
    locate(1, fila); cout << "------------------------------------------------------------------" << endl;
    fila++;

    while (fread(&obj, sizeof(Inscripcion), 1, p)) {

        if (obj.getIdCurso() == idCurso && obj.getEstado()) {
            encontro = true;

            Alumno alu = adminAlumnos.buscarYLeerPorLegajo(obj.getLegajoAlumno());

            locate(1, fila);  cout << alu.getLegajoAlumno();
            locate(10, fila); cout << alu.getApellido();
            locate(30, fila); cout << alu.getNombre();
            locate(50, fila); cout << (obj.getMatriculaPaga() ? "SI" : "NO");
            locate(55, fila); cout << obj.getTotalPagado();
            fila++;
        }
    }
    fclose(p);
    locate(1, fila + 2);

    if (!encontro) {
        cout << "No se encontraron alumnos inscriptos en este curso." << endl;
    }
    cout << endl;
}

void ArchivoInscripcion::listarPorAlumno() {
    cout << "--- LISTAR CURSOS POR ALUMNO ---" << endl;
    int legajoAlumno;
    while (true) {
        cout << "Ingrese Legajo del Alumno: " << endl;
        if (cin >> legajoAlumno && legajoAlumno > 0) break;
        cout << "*** ERROR: Legajo invalido. ***" << endl;
        cin.clear(); cin.ignore(10000, '\n');
    }


    ArchivoAlumnos adminAlumnos("Alumnos.dat");
    Alumno alu = adminAlumnos.buscarYLeerPorLegajo(legajoAlumno);
    if (alu.getLegajoAlumno() == 0) {
        cout << "*** ERROR: No existe un alumno con ese legajo. ***" << endl;
        return;
    }

    FILE *p = fopen("Inscripciones.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    ArchivoCursos adminCursos("Cursos.dat");
    Inscripcion obj;
    bool encontro = false;

    cout << "========== CURSOS ACTIVOS DE: " << alu.getApellido() << ", " << alu.getNombre() << " ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "ID CURSO";
    locate(11, fila); cout << "DESCRIPCION";
    locate(41, fila); cout << "AULA";
    locate(48, fila); cout << "PAGO";
    locate(55, fila); cout << "$ PAGADO";

    fila++;
    locate(1, fila); cout << "------------------------------------------------------------" << endl;
    fila++;

    while (fread(&obj, sizeof(Inscripcion), 1, p)) {
        // Filtra por Legajo de Alumno y Estado
        if (obj.getLegajoAlumno() == legajoAlumno && obj.getEstado()) {
            encontro = true;

            Curso cur = adminCursos.buscarYLeerPorId(obj.getIdCurso());

            locate(1, fila);  cout << cur.getIdCurso();
            locate(11, fila); cout << cur.getDescripcion();
            locate(41, fila); cout << cur.getNumAula();
            locate(48, fila); cout << (obj.getMatriculaPaga() ? "SI" : "NO");
            locate(55, fila); cout << (obj.getTotalPagado());

            fila++;
        }
    }
    fclose(p);
    locate(1, fila + 2);

    if (!encontro) {
        cout << "No se encontro al alumno inscripto en ningun curso." << endl;
    }
    cout << endl;
}

void ArchivoInscripcion::listarArrayOrdenadoPorCurso(Inscripcion inscripciones[], int cantidad) {

    if (cantidad < 0) {
        cout << "No existen inscripciones registradas"<<endl;
        return;
    }

    int fila = 3;
    locate(1, fila);  cout << "CURSO";
    locate(12, fila); cout << "LEGAJO";
    locate(22, fila); cout << "$ PAGADO";
    locate(32, fila); cout << "$ ADEUDADO";
    fila++;
    locate(1, fila); cout << "------------------------------------------------------------------" << endl;
    fila++;

    int i = 0;
    while (i < cantidad) {
            float adeudado = (inscripciones[i].getImporteMatricula() - inscripciones[i].getTotalPagado());
            locate(1, fila);  cout << inscripciones[i].getIdCurso();
            locate(12, fila); cout << inscripciones[i].getLegajoAlumno();
            locate(22, fila); cout << inscripciones[i].getTotalPagado();
            locate(32, fila); cout << adeudado;
            fila++;
            locate(1, fila); cout << "------------------------------------------------------------";
            fila++;

            i++;
    }
        cout << endl;
}



