#include <iostream>
#include <cstdio>
#include <cstring>
#include "ArchivoAlumnos.h"
#include "fecha.h"
#include "direccion.h"
#include "rlutil.h"

using namespace std;
using namespace rlutil;

ArchivoAlumnos::ArchivoAlumnos(const char *n) {
    strcpy(nombre, n);
}

int ArchivoAlumnos::contarRegistros() {
    FILE *p = fopen("Alumnos.dat", "rb");
    if (p == nullptr) return 0;
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Alumno);
    fclose(p);
    return cant;
}

Alumno ArchivoAlumnos::leerRegistro(int pos) {
    Alumno obj;
    FILE *p = fopen("Alumnos.dat", "rb");
    if (p == nullptr) return obj;
    fseek(p, pos * sizeof(Alumno), SEEK_SET);
    fread(&obj, sizeof(Alumno), 1, p);
    fclose(p);
    return obj;
}

bool ArchivoAlumnos::grabarRegistro(Alumno obj) {
    FILE *p = fopen("Alumnos.dat", "ab");
    if (p == nullptr) return false;
    bool escribio = fwrite(&obj, sizeof(Alumno), 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoAlumnos::modificarRegistro(Alumno obj, int pos) {
    FILE *p = fopen("Alumnos.dat", "rb+");
    if (p == nullptr) return false;
    fseek(p, pos * sizeof(Alumno), SEEK_SET);
    bool escribio = fwrite(&obj, sizeof(Alumno), 1, p);
    fclose(p);
    return escribio;
}

<<<<<<< HEAD
// ========== BÚSQUEDAS ==========

int ArchivoAlumnos::buscarPorLegajo(int legajo) {
    FILE *p = fopen(nombre, "rb");
=======
int ArchivoAlumnos::generarNuevoLegajo() {
    int cant = contarRegistros();
    return cant + 100;
}


/// Busquedas

int ArchivoAlumnos::buscarPorLegajo(int legajo) {
    FILE *p = fopen("Alumnos.dat", "rb");
>>>>>>> origin/alex
    if (p == nullptr) return -1;
    Alumno obj;
    int pos = 0;
    while (fread(&obj, sizeof(Alumno), 1, p)) {
<<<<<<< HEAD
        if (obj.getLegajo() == legajo) {
=======


        if (obj.getLegajoAlumno() == legajo) {
>>>>>>> origin/alex
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
<<<<<<< HEAD
    return -2; // No encontrado
}

int ArchivoAlumnos::buscarPorDni(int dni) {
    FILE *p = fopen(nombre, "rb");
=======
    return -2;
}

int ArchivoAlumnos::buscarPorDni(int dni) {
    FILE *p = fopen("Alumnos.dat", "rb");
>>>>>>> origin/alex
    if (p == nullptr) return -1;
    Alumno obj;
    int pos = 0;
    while (fread(&obj, sizeof(Alumno), 1, p)) {
        if (obj.getDni() == dni) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
<<<<<<< HEAD
    return -2; // No encontrado
}

// ========== VALIDACIONES ==========
=======
    return -2;
}

Alumno ArchivoAlumnos::buscarYLeerPorLegajo(int legajo) {
    int pos = buscarPorLegajo(legajo);

    if (pos >= 0) {
        return leerRegistro(pos);
    }


    return leerRegistro(-1);
}

/// validaciones
>>>>>>> origin/alex

bool ArchivoAlumnos::existeLegajo(int legajo) {
    return buscarPorLegajo(legajo) >= 0;
}

bool ArchivoAlumnos::existeDni(int dni) {
    return buscarPorDni(dni) >= 0;
}

bool ArchivoAlumnos::validarLegajoUnico(int legajo) {
    if (existeLegajo(legajo)) {
<<<<<<< HEAD
        cout << "\n*** ERROR: Ya existe un alumno con el legajo " << legajo << " ***\n";
=======
        cout << endl << "*** ERROR: Ya existe un alumno con el legajo " << legajo << " ***" << endl;
>>>>>>> origin/alex
        return false;
    }
    return true;
}

bool ArchivoAlumnos::validarDniUnico(int dni) {
    if (existeDni(dni)) {
<<<<<<< HEAD
        cout << "\n*** ERROR: Ya existe un alumno con el DNI " << dni << " ***\n";
=======
        cout << endl << "*** ERROR: Ya existe un alumno con el DNI " << dni << " ***" << endl;
>>>>>>> origin/alex
        return false;
    }
    return true;
}

<<<<<<< HEAD
// ========== LISTADOS ==========

void ArchivoAlumnos::listar() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay registros de alumnos.\n";
=======
/// CONsultas
void ArchivoAlumnos::consultarPorLegajo() {
    cout << "--- CONSULTAR ALUMNO POR LEGAJO ---" << endl;
    int legajo;
    cout << "Ingrese el legajo del alumno a consultar: " << endl;
    cin >> legajo;

    int pos = buscarPorLegajo(legajo);

    if (pos == -1) {
        cout << "*** ERROR: No se pudo abrir o leer el archivo de alumnos. ***" << endl;
>>>>>>> origin/alex
        return;
    }
    if (pos == -2) {
        cout << "*** ERROR: No se encontro ningun alumno con el legajo " << legajo << ". ***" << endl;
        return;
    }

    cout << "Se encontro el siguiente registro:" << endl;
    Alumno obj = leerRegistro(pos);
    obj.Mostrar();
    cout << "--------------------------------" << endl;
}

//// LISTADOS
void ArchivoAlumnos::listar() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay registros de alumnos." << endl;
        return;
    }

    FILE *p = fopen("Alumnos.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    Alumno obj;
<<<<<<< HEAD
    bool hayRegistros = false;
    while (fread(&obj, sizeof(Alumno), 1, p)) {
        obj.Mostrar();
        cout << "--------------------------------\n";
        hayRegistros = true;
=======
    cout << endl << "========== LISTADO DE ALUMNOS ==========" << endl;
    for(int i=0; i<cant; i++){
        obj = leerRegistro(i);
        obj.Mostrar();
        cout << "--------------------------------" << endl;
>>>>>>> origin/alex
    }
    fclose(p);

    if (!hayRegistros) {
        cout << "No hay alumnos registrados.\n";
    }
}

void ArchivoAlumnos::listarActivos() {
    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "No hay registros de alumnos.\n";
        return;
    }
    Alumno obj;
    bool encontro = false;
    cout << "\n========== ALUMNOS ACTIVOS ==========\n";
    while (fread(&obj, sizeof(Alumno), 1, p)) {
        if (obj.getEstado()) {
            obj.Mostrar();
            cout << "--------------------------------\n";
            encontro = true;
        }
    }
    fclose(p);

    if (!encontro) {
        cout << "No hay alumnos activos.\n";
    }
}

void ArchivoAlumnos::listarPorApellido() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay alumnos registrados.\n";
        return;
    }

    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    // Leer todos los alumnos en un vector temporal
    Alumno registro;
    int indices[1000]; // Guardar orden de índices
    int leidos = 0;

    // Primero leer todo en memoria
    fseek(p, 0, SEEK_SET);
    while (leidos < 1000 && fread(&registro, sizeof(Alumno), 1, p) == 1) {
        indices[leidos] = leidos;
        leidos++;
    }

    // Ordenar los ÍNDICES (no los objetos completos)
    for (int i = 0; i < leidos - 1; i++) {
        for (int j = i + 1; j < leidos; j++) {
            // Leer objetos para comparar
            Alumno a1, a2;
            fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
            fread(&a1, sizeof(Alumno), 1, p);
            fseek(p, indices[j] * sizeof(Alumno), SEEK_SET);
            fread(&a2, sizeof(Alumno), 1, p);

            if (strcmp(a1.getApellido(), a2.getApellido()) > 0) {
                // Intercambiar índices
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Mostrar en orden
    cout << "\n========== ALUMNOS ORDENADOS POR APELLIDO ==========\n";
    for (int i = 0; i < leidos; i++) {
        Alumno obj;
        fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
        fread(&obj, sizeof(Alumno), 1, p);
        obj.Mostrar();
        cout << "--------------------------------\n";
    }

    fclose(p);
}

void ArchivoAlumnos::listarPorDni() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay alumnos registrados.\n";
        return;
    }

    FILE *p = fopen(nombre, "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    // Leer todos los alumnos en un vector temporal
    Alumno registro;
    int indices[1000]; // Guardar orden de índices
    int leidos = 0;

    // Primero leer todo en memoria
    fseek(p, 0, SEEK_SET);
    while (leidos < 1000 && fread(&registro, sizeof(Alumno), 1, p) == 1) {
        indices[leidos] = leidos;
        leidos++;
    }

    // Ordenar los ÍNDICES por DNI
    for (int i = 0; i < leidos - 1; i++) {
        for (int j = i + 1; j < leidos; j++) {
            // Leer objetos para comparar
            Alumno a1, a2;
            fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
            fread(&a1, sizeof(Alumno), 1, p);
            fseek(p, indices[j] * sizeof(Alumno), SEEK_SET);
            fread(&a2, sizeof(Alumno), 1, p);

            if (a1.getDni() > a2.getDni()) {
                // Intercambiar índices
                int temp = indices[i];
                indices[i] = indices[j];
                indices[j] = temp;
            }
        }
    }

    // Mostrar en orden
    cout << "\n========== ALUMNOS ORDENADOS POR DNI ==========\n";
    for (int i = 0; i < leidos; i++) {
        Alumno obj;
        fseek(p, indices[i] * sizeof(Alumno), SEEK_SET);
        fread(&obj, sizeof(Alumno), 1, p);
        obj.Mostrar();
        cout << "--------------------------------\n";
    }

    fclose(p);
}

void ArchivoAlumnos::compactarArchivo() { ///método para limpiar registros corruptos
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay registros para compactar.\n";
        return;
    }

    // Archivo temporal
    FILE *pOrig = fopen(nombre, "rb");
    FILE *pTemp = fopen("Alumnos_temp.dat", "wb");

    if (pOrig == nullptr || pTemp == nullptr) {
        cout << "Error al abrir archivos.\n";
        if (pOrig) fclose(pOrig);
        if (pTemp) fclose(pTemp);
        return;
    }

    Alumno obj;
    int validos = 0;
    int eliminados = 0;

    while (fread(&obj, sizeof(Alumno), 1, pOrig) == 1) {
        // Solo copiar registros válidos (con legajo > 0 y activos)
        if (obj.getLegajo() > 0 && obj.getEstado()) {
            fwrite(&obj, sizeof(Alumno), 1, pTemp);
            validos++;
        } else {
            eliminados++;
        }
    }

    fclose(pOrig);
    fclose(pTemp);

    // Reemplazar archivo original
    remove(nombre);
    rename("Alumnos_temp.dat", nombre);

    cout << "\n===== ARCHIVO COMPACTADO =====\n";
    cout << "Registros validos: " << validos << "\n";
    cout << "Registros eliminados: " << eliminados << "\n";
}

void ArchivoAlumnos::listarInactivos() {
    FILE *p = fopen("Alumnos.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Alumno obj;
    bool encontro = false;

    cout << "========== ALUMNOS INACTIVOS (DADOS DE BAJA) ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "LEGAJO";
    locate(12, fila); cout << "APELLIDO";
    locate(33, fila); cout << "NOMBRE";
    locate(54, fila); cout << "DNI";
    fila++;
    locate(1, fila); cout << "-----------------------------------------------------------------" << endl;
    fila++;


    while (fread(&obj, sizeof(Alumno), 1, p)) {

        if (!obj.getEstado()) {
            encontro = true;

            locate(1, fila);  cout << obj.getLegajoAlumno();
            locate(12, fila); cout << obj.getApellido();
            locate(33, fila); cout << obj.getNombre();
            locate(54, fila); cout << obj.getDni();

            fila++;
        }
    }
    fclose(p);

    locate(1, fila + 2);

    if (!encontro) {
        cout << "No hay alumnos inactivos para mostrar." << endl;
    }
    cout << endl;
}

void ArchivoAlumnos::listarPorApellido() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay alumnos registrados." << endl;
        return;
    }

    const int MAX_ALUMNOS = 1000;
    if(cant > MAX_ALUMNOS){
        cout << "Hay demasiados registros para este método de listado." << endl;
        return;
    }
    Alumno alumnos[MAX_ALUMNOS];

    FILE *p = fopen("Alumnos.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int leidos = 0;
    Alumno obj_temporal;

    while (leidos < cant && fread(&obj_temporal, sizeof(Alumno), 1, p) == 1) {
        if (obj_temporal.getEstado()) {
            alumnos[leidos] = obj_temporal;
            leidos++;
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay alumnos activos para ordenar." << endl;
        return;
    }


    for (int i = 0; i < leidos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < leidos; j++) {
            // strcmp compara strings. < 0 significa que j va antes que minIdx
            if (strcmp(alumnos[j].getApellido(), alumnos[minIdx].getApellido()) < 0) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Alumno temp = alumnos[i];
            alumnos[i] = alumnos[minIdx];
            alumnos[minIdx] = temp;
        }
    }

    cout << "========== ALUMNOS ACTIVOS ORDENADOS POR APELLIDO ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "APELLIDO";
    locate(22, fila); cout << "NOMBRE";
    locate(43, fila); cout << "LEGAJO";
    locate(54, fila); cout << "DNI";
    fila++;

    locate(1, fila); cout << "------------------------------------------------------------------" << endl;
    fila++;


    for (int i = 0; i < leidos; i++) {
        locate(1, fila);  cout << alumnos[i].getApellido();
        locate(22, fila); cout << alumnos[i].getNombre();
        locate(43, fila); cout << alumnos[i].getLegajoAlumno();
        locate(54, fila); cout << alumnos[i].getDni();
        fila++;
    }
    cout << endl << endl;
}

void ArchivoAlumnos::listarPorDni() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay alumnos registrados." << endl;
        return;
    }

    const int MAX_ALUMNOS = 1000;
    if(cant > MAX_ALUMNOS){
        cout << "Hay demasiados registros para este método de listado." << endl;
        return;
    }
    Alumno alumnos[MAX_ALUMNOS];

    FILE *p = fopen("Alumnos.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int leidos = 0;
    Alumno obj_temporal;

    while (leidos < cant && fread(&obj_temporal, sizeof(Alumno), 1, p) == 1) {
        if (obj_temporal.getEstado()) {
            alumnos[leidos] = obj_temporal;
            leidos++;
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay alumnos activos para ordenar." << endl;
        return;
    }


    for (int i = 0; i < leidos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < leidos; j++) {
            if (alumnos[j].getDni() < alumnos[minIdx].getDni()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Alumno temp = alumnos[i];
            alumnos[i] = alumnos[minIdx];
            alumnos[minIdx] = temp;
        }
    }


    cout << "========== ALUMNOS ACTIVOS ORDENADOS POR DNI ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "DNI";
    locate(14, fila); cout << "LEGAJO";
    locate(25, fila); cout << "APELLIDO";
    locate(46, fila); cout << "NOMBRE";
    fila++;

    locate(1, fila); cout << "------------------------------------------------------------------" << endl;
    fila++;

    for (int i = 0; i < leidos; i++) {
        locate(1, fila);  cout << alumnos[i].getDni();
        locate(14, fila); cout << alumnos[i].getLegajoAlumno();
        locate(25, fila); cout << alumnos[i].getApellido();
        locate(46, fila); cout << alumnos[i].getNombre();
        fila++;
    }
    cout << endl << endl;
}

void ArchivoAlumnos::listarPorLegajo() {
    FILE *p = fopen("Alumnos.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Alumno obj;
    bool encontro = false;

    cout << "========== ALUMNOS ACTIVOS (POR ORDEN DE LEGAJO) ==========" << endl << endl;


    int fila = 3;
    locate(1, fila);  cout << "LEGAJO";
    locate(12, fila); cout << "APELLIDO";
    locate(33, fila); cout << "NOMBRE";
    locate(54, fila); cout << "DNI";
    fila++;
    locate(1, fila); cout << "-----------------------------------------------------------------" << endl;
    fila++;


    while (fread(&obj, sizeof(Alumno), 1, p)) {


        if (obj.getEstado()) {
            encontro = true;


            locate(1, fila);  cout << obj.getLegajoAlumno();
            locate(12, fila); cout << obj.getApellido();
            locate(33, fila); cout << obj.getNombre();
            locate(54, fila); cout << obj.getDni();

            fila++;
        }
    }
    fclose(p);


    locate(1, fila + 2);

    if (!encontro) {
        cout << "No hay alumnos activos para mostrar." << endl;
    }
    cout << endl;
}

/// ALTA Y BAJA ALUMNO
void ArchivoAlumnos::altaAlumno() {
    cout << endl << "--- ALTA DE NUEVO ALUMNO ---" << endl;

    int proximoLegajo = generarNuevoLegajo();

    cout << "***********************************" << endl;
    cout << "  PROXIMO LEGAJO A ASIGNAR: " << proximoLegajo << endl;
    cout << "***********************************" << endl;
    cout << "Por favor, complete el resto de los datos:" << endl;

    Alumno nuevoAlumno;

    if (!nuevoAlumno.Cargar()) {
        cout << "Alta cancelada" << endl;
        return;
    }

    if (!validarDniUnico(nuevoAlumno.getDni())) {
        cout << "*** ERROR: Ya existe un alumno con ese DNI. ***" << endl;
        cout << "El alta fue cancelada." << endl;
        return;
    }

    nuevoAlumno.setLegajoAlumno(proximoLegajo);
    nuevoAlumno.setEstado(true);

    if (grabarRegistro(nuevoAlumno)) {
        cout << endl << "¡Alumno '" << nuevoAlumno.getApellido() << "' dado de alta exitosamente!" << endl;

    } else {
        cout << endl << "*** ERROR: No se pudo grabar el registro en el archivo. ***" << endl;
        cout << "El alta fue cancelada." << endl;
    }
}

void ArchivoAlumnos::bajaAlumno() {
    cout << endl << "--- BAJA DE ALUMNO ---" << endl;
    int legajo;
    cout << "Ingrese el legajo del alumno a dar de baja: ";
    cin >> legajo;


    int pos = buscarPorLegajo(legajo);


    if (pos == -1) {
        cout << endl << "*** ERROR: No se pudo abrir o leer el archivo de alumnos. ***" << endl;
        return;
    }
    if (pos == -2) {
        cout << endl << "*** ERROR: No se encontro ningun alumno con el legajo " << legajo << ". ***" << endl;
        return;
    }


    Alumno obj = leerRegistro(pos);

    cout << "Se encontro el siguiente registro:" << endl;
    obj.Mostrar();
    cout << "--------------------------------" << endl;


    if (!obj.getEstado()) {
        cout << "Este alumno ya se encuentra dado de baja (inactivo)." << endl;
        return;
    }


    int confirmacion;
    cout << "Esta seguro que desea dar de baja a este alumno? (1 - SI / 0 - NO): ";
    cin >> confirmacion;

    if (confirmacion == 1) {

        obj.setEstado(false);

        if (modificarRegistro(obj, pos)) {
            cout << "El alumno fue dado de baja exitosamente." << endl;
        } else {
            cout << endl << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }

    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void ArchivoAlumnos::reactivarAlumno() {
    cout << endl << "--- REACTIVAR ALUMNO ---" << endl;
    int legajo;
    cout << "Ingrese el legajo del alumno a reactivar: ";
    cin >> legajo;


    int pos = buscarPorLegajo(legajo);


    if (pos == -1) {
        cout << endl << "*** ERROR: No se pudo abrir o leer el archivo de alumnos. ***" << endl;
        return;
    }
    if (pos == -2) {
        cout << endl << "*** ERROR: No se encontro ningun alumno con el legajo " << legajo << ". ***" << endl;
        return;
    }


    Alumno obj = leerRegistro(pos);

    cout << "Se encontro el siguiente registro:" << endl;
    obj.Mostrar();
    cout << "--------------------------------" << endl;


    if (obj.getEstado()) {
        cout << "Este alumno ya se encuentra ACTIVO." << endl;
        return;
    }


    int confirmacion;
    cout << "El alumno esta INACTIVO. Desea reactivarlo? (1 - SI / 0 - NO): ";
    cin >> confirmacion;

    if (confirmacion == 1) {


        obj.setEstado(true);


        if (modificarRegistro(obj, pos)) {
            cout << "El alumno fue reactivado exitosamente." << endl;
        } else {
            cout << endl << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }

    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void ArchivoAlumnos::modificar() {
    cout << endl << "--- MODIFICAR ALUMNO ---" << endl;
    int legajo;
    cout << "Ingrese el legajo del alumno a modificar: ";
    cin >> legajo;

    int pos = buscarPorLegajo(legajo);

    if (pos == -1) {
        cout << endl << "*** ERROR: No se pudo abrir o leer el archivo de alumnos. ***" << endl;
        return;
    }
    if (pos == -2) {
        cout << endl << "*** ERROR: No se encontro ningun alumno con el legajo " << legajo << ". ***" << endl;
        return;
    }

    Alumno obj = leerRegistro(pos);
    int opcion;
    bool salir = false;

    while (!salir) {
        system("cls");
        cout << "--- MODIFICANDO ALUMNO ---" << endl;
        obj.Mostrar();
        cout << "--------------------------------" << endl;
        cout << "Que desea modificar?" << endl;
        cout << "1. Nombre" << endl;
        cout << "2. Apellido" << endl;
        cout << "3. DNI" << endl;
        cout << "4. Telefono" << endl;
        cout << "5. Email" << endl;
        cout << "6. Direccion" << endl;
        cout << "7. Fecha de Nacimiento" << endl;
        cout << "--------------------------------" << endl;
        cout << "0. GUARDAR Y SALIR" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        system("cls");

        if (cin.fail()) {
            cout << "Error: Debe ingresar solo numeros." << endl;
            cin.clear();
            cin.ignore(10000, '\n');

            system("pause");
            continue;
        }

        switch (opcion) {
            case 1: {
                char nuevoNombre[50];
                cout << "Ingrese el nuevo Nombre: ";
                cin.ignore();
                cin.getline(nuevoNombre, 50);
                obj.setNombre(nuevoNombre);
                cout << "Nombre actualizado." << endl;
                break;
            }
            case 2: {
                char nuevoApellido[50];
                cout << "Ingrese el nuevo Apellido: ";
                cin.ignore();
                cin.getline(nuevoApellido, 50);
                obj.setApellido(nuevoApellido);
                cout << "Apellido actualizado." << endl;
                break;
            }
            case 3: {

                int nuevoDni;
                cout << "Ingrese el nuevo DNI: ";
                cin >> nuevoDni;

                if (nuevoDni == obj.getDni()) {
                cout << "El DNI ingresado es el mismo que ya tenia." << endl;
                }

                else if (validarDniUnico(nuevoDni)) {

                if (obj.setDni(nuevoDni)) {
                    cout << "DNI actualizado." << endl;
                    } else {
                cout << "*** ERROR: DNI no valido (debe ser > 100000). ***" << endl;
                    }
                }
                break;
            }
            case 4: {
                int nuevoTel;
                cout << "Ingrese el nuevo Telefono: ";
                cin >> nuevoTel;
                obj.setTelefono(nuevoTel);
                cout << "Telefono actualizado." << endl;
                break;
            }
            case 5: {
                char nuevoEmail[100];
                cout << "Ingrese el nuevo Email: ";
                cin.ignore();
                cin.getline(nuevoEmail, 100); //
                obj.setEmail(nuevoEmail); //
                cout << "Email actualizado." << endl;
                    break;
            }



            case 6: {
                cout << "--- MODIFICAR DIRECCION ---" << endl;

                cin.ignore();
                Direccion nuevaDir;
                nuevaDir.Cargar();

                obj.setDireccion(nuevaDir);
                cout << "Direccion actualizada." << endl;
                break;
            }
            case 7: {
                cout << "--- MODIFICAR FECHA DE NACIMIENTO ---" << endl;

                cin.ignore();
                Fecha nuevaFecha;
                nuevaFecha.Cargar();

                obj.setFechaNacimiento(nuevaFecha);
                cout << "Fecha de Nacimiento actualizada." << endl;
                break;
            }

            case 0: {
                cout << "Guardando cambios..." << endl;
                if (modificarRegistro(obj, pos)) {
                    cout << "El alumno fue modificado exitosamente." << endl;
                } else {
                    cout << endl << "*** ERROR: No se pudo modificar el registro. ***" << endl;
                }
                salir = true;
                break;
            }
            default:
                cout << "Opcion no valida." << endl;
                break;
        }

        if (opcion != 0) {
            system("pause");
        }
    }
}


