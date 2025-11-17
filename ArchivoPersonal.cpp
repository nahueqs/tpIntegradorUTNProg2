#include "ArchivoPersonal.h"
#include <cstdio>
#include <cstring>
#include <iostream>
#include "rlutil.h"

using namespace std;
using namespace rlutil;

ArchivoPersonal::ArchivoPersonal(const char* nombre) {
    strncpy(_nombre, nombre, 29);
    _nombre[29] = '\0';
}

int ArchivoPersonal::contarRegistros() {
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p) / sizeof(Personal);
    fclose(p);
    return bytes;
}

bool ArchivoPersonal::grabarRegistro(Personal obj) {
    bool grabar;
    FILE *p = fopen("personal.dat", "ab");
    if (p == nullptr) {
        return false;
    }
    grabar = fwrite(&obj, sizeof(Personal), 1, p);
    fclose(p);
    return grabar;
}

Personal ArchivoPersonal::leerRegistro(int pos) {
    Personal obj;

    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        return obj;
    }

    fseek(p, pos * sizeof(Personal), SEEK_SET);
    fread(&obj, sizeof(Personal), 1, p);

    fclose(p);
    return obj;
}

bool ArchivoPersonal::modificarRegistro(Personal obj, int pos) {
    FILE *p = fopen("personal.dat", "rb+");
    if (p == nullptr) {
        return false;
    }

    fseek(p, pos * sizeof(Personal), SEEK_SET);
    bool escribio = fwrite(&obj, sizeof(Personal), 1, p);

    fclose(p);
    return escribio;
}

/// generar legajos

int ArchivoPersonal::generarNuevoLegajo() {
    return contarRegistros() + 1000;
}

int ArchivoPersonal::generarNuevoLegajoDocente() {
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        return 5000;
    }

    Personal obj;
    int contadorDocentes = 0;
    while (fread(&obj, sizeof(Personal), 1, p)) {
        if (obj.getCargo() == 4) {
            contadorDocentes++;
        }
    }
    fclose(p);
    return contadorDocentes + 5000;
}

//// busquedas

int ArchivoPersonal::buscarPorLegajo(int legajo) {
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        return -1;
    }
    Personal obj;
    int pos = 0;
    while (fread(&obj, sizeof(Personal), 1, p)) {
        if (obj.getLegajo() == legajo) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}

int ArchivoPersonal::buscarPorDni(int dni) {
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        return -1;
    }
    Personal obj;
    int pos = 0;
    while (fread(&obj, sizeof(Personal), 1, p)) {
        if (obj.getDni() == dni) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}

int ArchivoPersonal::buscarPorLegajoDocente(int legajoDocente) {
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        return -1;
    }
    Personal obj;
    int pos = 0;
    while (fread(&obj, sizeof(Personal), 1, p)) {
        if (obj.getCargo() == 4 && obj.getLegajoDocente() == legajoDocente) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}

/// ALTA BAJA MODIFICACIONES Y reactivar

void ArchivoPersonal::darDeAlta() {
    cout << "--- ALTA DE NUEVO PERSONAL ---" << endl;
    Personal nuevoPersonal;

    if (!nuevoPersonal.Cargar()) {
        cout << "Alta cancelada por el usuario." << endl;
        return;
    }

    int legajoGeneral = generarNuevoLegajo();
    nuevoPersonal.setLegajo(legajoGeneral);
    cout << "***********************************" << endl;
    cout << "  LEGAJO GENERAL ASIGNADO: " << legajoGeneral << endl;

    if (nuevoPersonal.getCargo() == 4) {
        int legajoDoc = generarNuevoLegajoDocente();
        nuevoPersonal.setLegajoDocente(legajoDoc);
        cout << "  LEGAJO DOCENTE ASIGNADO: " << legajoDoc << endl;
    }
    cout << "***********************************" << endl;

    nuevoPersonal.setEstado(true);

    if (grabarRegistro(nuevoPersonal)) {
        cout << "¡Personal '" << nuevoPersonal.getApellido() << "' dado de alta exitosamente!" << endl;
    } else {
        cout << "*** ERROR: No se pudo grabar el registro. ***" << endl;
    }
}

void ArchivoPersonal::darDeBaja() {
    cout << "--- BAJA DE PERSONAL ---" << endl;
    int legajo;

    while (true) {
        cout << "Ingrese el legajo (general) del empleado a dar de baja: " << endl;
        if (cin >> legajo) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorLegajo(legajo);
    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro personal con el legajo " << legajo << ". ***" << endl;
        return;
    }

    Personal obj = leerRegistro(pos);
    if (!obj.getEstado()) {
        cout << "Este empleado ya se encuentra INACTIVO." << endl;
        return;
    }

    cout << "Se encontro el siguiente registro:" << endl;
    obj.Mostrar();
    cout << "--------------------------------" << endl;

    int confirmacion;
    cout << "Esta seguro que desea dar de baja? (1 - SI / 0 - NO): " << endl;
    cin >> confirmacion;

    if (confirmacion == 1) {
        obj.setEstado(false);
        if (modificarRegistro(obj, pos)) {
            cout << "El empleado fue dado de baja exitosamente." << endl;
        } else {
            cout << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void ArchivoPersonal::reactivar() {
    cout << "--- REACTIVAR PERSONAL ---" << endl;
    int legajo;

    while (true) {
        cout << "Ingrese el legajo (general) del empleado a reactivar: " << endl;
        if (cin >> legajo) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorLegajo(legajo);
     if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro personal con el legajo " << legajo << ". ***" << endl;
        return;
    }

    Personal obj = leerRegistro(pos);
    if (obj.getEstado()) {
        cout << "Este empleado ya se encuentra ACTIVO." << endl;
        return;
    }

    cout << "Se encontro el siguiente registro (INACTIVO):" << endl;
    obj.Mostrar();
    cout << "--------------------------------" << endl;

    int confirmacion;
    cout << "Desea reactivar a este empleado? (1 - SI / 0 - NO): " << endl;
    cin >> confirmacion;

    if (confirmacion == 1) {
        obj.setEstado(true);
        if (modificarRegistro(obj, pos)) {
            cout << "El empleado fue reactivado exitosamente." << endl;
        } else {
            cout << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void ArchivoPersonal::modificar() {
    cout << "--- MODIFICAR PERSONAL ---" << endl;
    int legajo;


    while (true) {
        cout << "Ingrese el legajo (general) del empleado a modificar: " << endl;
        if (cin >> legajo) { //// pd : acuerdense que esto retorna true/ false x si no lo entienden, en persona.cpp lo explique
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorLegajo(legajo);

    if (pos == -1) {
        cout << "*** ERROR: No se pudo abrir o leer el archivo de personal. ***" << endl;
        return;
    }
    if (pos == -2) {
        cout << "*** ERROR: No se encontro personal con el legajo " << legajo << ". ***" << endl;
        return;
    }

    Personal obj = leerRegistro(pos);
    int opcion;
    bool salir = false;

    while (!salir) {
        system("cls");
        cout << "--- MODIFICANDO PERSONAL ---" << endl;
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
        cout << "8. Turnos" << endl;
        cout << "9. Cargo" << endl;
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

                else if (obj.setDni(nuevoDni)) {
                     cout << "DNI actualizado." << endl;
                } else {
                     cout << "*** ERROR: DNI no valido (debe ser > 100000). ***" << endl;
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
                cin.getline(nuevoEmail, 100);
                obj.setEmail(nuevoEmail);
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

            case 8: {
                cout << "--- MODIFICAR TURNOS ---" << endl;
                int opt;
                cout << "Trabaja en el turno Maniana? (1: SI / 0: NO): ";
                cin >> opt;
                obj.setTurno(0, (opt == 1));

                cout << "Trabaja en el turno Tarde? (1: SI / 0: NO): ";
                cin >> opt;
                obj.setTurno(1, (opt == 1));

                cout << "Trabaja en el turno Noche? (1: SI / 0: NO): ";
                cin >> opt;
                obj.setTurno(2, (opt == 1));

                cout << "Turnos actualizados." << endl;
                break;
            }
            case 9: {
                cout << "--- MODIFICAR CARGO ---" << endl;
                int cargoIngresado;
                while (true) {
                    cout << "1: Director" << endl;
                    cout << "2: Preceptor" << endl;
                    cout << "3: Limpieza" << endl;
                    cout << "4. Docente" << endl;
                    cout << "Ingrese el nro de cargo: ";

                    if (cin >> cargoIngresado && cargoIngresado >= 1 && cargoIngresado <= 4) {

                        // Lógica para manejar el Legajo Docente
                        if (obj.getCargo() == 4 && cargoIngresado != 4) {
                            cout << "Cambiando de Docente a No-Docente. Se borrara el Legajo Docente." << endl;
                            obj.setLegajoDocente(0); // Borra el legajo específico
                        }

                        if (obj.getCargo() != 4 && cargoIngresado == 4) {
                            cout << "Cambiando a Docente. Se generara un nuevo Legajo Docente." << endl;
                            int nuevoLegajoDoc = generarNuevoLegajoDocente();
                            obj.setLegajoDocente(nuevoLegajoDoc);
                            cout << "Nuevo Legajo Docente asignado: " << nuevoLegajoDoc << endl;
                        }

                        obj.setCargo(cargoIngresado);
                        cout << "Cargo actualizado." << endl;
                        break;
                    } else {
                        cout << "*** ERROR: Opcion no valida. ***" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                break;
            }


            case 0: {
                cout << "Guardando cambios..." << endl;
                if (modificarRegistro(obj, pos)) {
                    cout << "El empleado fue modificado exitosamente." << endl;
                } else {
                    cout << "*** ERROR: No se pudo modificar el registro. ***" << endl;
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

/// CONSULTAS

void ArchivoPersonal::consultarPorLegajo() {
    cout << "--- CONSULTAR POR LEGAJO GENERAL ---" << endl;
    int legajo;

    while (true) {
        cout << "Ingrese el legajo (general) a consultar: " << endl;
        if (cin >> legajo) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorLegajo(legajo);
    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro personal con el legajo " << legajo << ". ***" << endl;
        return;
    }

    cout << "Se encontro el siguiente registro:" << endl;
    Personal obj = leerRegistro(pos);
    obj.Mostrar();
    cout << "--------------------------------" << endl;
}


void ArchivoPersonal::consultarPorLegajoDocente() {
    cout << "--- CONSULTAR POR LEGAJO DOCENTE ---" << endl;
    int legajoDocente;

    while (true) {
        cout << "Ingrese el legajo (docente) a consultar: " << endl;
        if (cin >> legajoDocente) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorLegajoDocente(legajoDocente);
    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro docente con el legajo " << legajoDocente << ". ***" << endl;
        return;
    }

    cout << "Se encontro el siguiente registro:" << endl;
    Personal obj = leerRegistro(pos);
    obj.Mostrar();
    cout << "--------------------------------" << endl;
}

/// LIstados

void ArchivoPersonal::listarPorLegajo() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay personal registrado." << endl;
        return;
    }

    const int MAX_PERSONAL = 1000;
    if(cant > MAX_PERSONAL){
        cout << "Hay demasiados registros para este método." << endl;
        return;
    }
    Personal empleados[MAX_PERSONAL];

    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }


    int leidos = 0;
    Personal obj_temporal;
    while (leidos < cant && fread(&obj_temporal, sizeof(Personal), 1, p) == 1) {

        if (obj_temporal.getEstado()) {
            empleados[leidos] = obj_temporal;
            leidos++;
        }
    }
    fclose(p);


    if (leidos == 0) {

        cout << "No hay personal activo para mostrar." << endl;
        return;
    }

    for (int i = 0; i < leidos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < leidos; j++) {
            if (empleados[j].getLegajo() < empleados[minIdx].getLegajo()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Personal temp = empleados[i];
            empleados[i] = empleados[minIdx];
            empleados[minIdx] = temp;
        }
    }


    cout << "========== PERSONAL ACTIVO ORDENADO POR LEGAJO GENERAL ==========" << endl << endl;

    int fila = 3;
    locate(1, fila); cout << "LEGAJO";
    locate(12, fila); cout << "APELLIDO";
    locate(33, fila); cout << "NOMBRE";
    locate(54, fila); cout << "DNI";
    fila++;

    locate(1, fila); cout << "------------------------------------------------------------------" << endl;
    fila++;


    for (int i = 0; i < leidos; i++) {
        locate(1, fila);  cout << empleados[i].getLegajo();
        locate(12, fila); cout << empleados[i].getApellido();
        locate(33, fila); cout << empleados[i].getNombre();
        locate(54, fila); cout << empleados[i].getDni();

        fila++;
    }
    cout << endl << endl;
}

void ArchivoPersonal::listarPorLegajoDocente() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay personal registrado." << endl;
        return;
    }
    const int MAX_PERSONAL = 1000;
    Personal empleados[MAX_PERSONAL];
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int leidos = 0;
    Personal obj_temporal;

    while (leidos < cant && fread(&obj_temporal, sizeof(Personal), 1, p) == 1) {
        if (obj_temporal.getEstado() && obj_temporal.getCargo() == 4) { // 4 = Docente
            empleados[leidos] = obj_temporal;
            leidos++;
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay docentes activos para ordenar." << endl;
        return;
    }

    // aca ordenamos x2
    for (int i = 0; i < leidos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < leidos; j++) {
            if (empleados[j].getLegajoDocente() < empleados[minIdx].getLegajoDocente()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Personal temp = empleados[i];
            empleados[i] = empleados[minIdx];
            empleados[minIdx] = temp;
        }
    }

    // --- Impresión con rlutil ---
    cout << "========== DOCENTES ACTIVOS ORDENADOS POR LEGAJO DOCENTE ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "L. DOCENTE";
    locate(14, fila); cout << "L. GENERAL";
    locate(27, fila); cout << "APELLIDO";
    locate(48, fila); cout << "NOMBRE";
    fila++;

    locate(1, fila); cout << "---------------------------------------------------------------------" << endl;
    fila++;

    for (int i = 0; i < leidos; i++) {
        locate(1, fila);  cout << empleados[i].getLegajoDocente();
        locate(14, fila); cout << empleados[i].getLegajo();
        locate(27, fila); cout << empleados[i].getApellido();
        locate(48, fila); cout << empleados[i].getNombre();
        fila++;
    }
    cout << endl << endl;
}

void ArchivoPersonal::listarPorCargo() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay personal registrado." << endl;
        return;
    }
    const int MAX_PERSONAL = 1000;
    Personal empleados[MAX_PERSONAL];
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    // aca listamos solo los activos
    int leidos = 0;
    Personal obj_temporal;
    while (leidos < cant && fread(&obj_temporal, sizeof(Personal), 1, p) == 1) {

        if (obj_temporal.getEstado()) {
            empleados[leidos] = obj_temporal;
            leidos++;
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay personal activo para ordenar." << endl;
        return;
    }

    /// aca lo ordenamos
    for (int i = 0; i < leidos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < leidos; j++) {
            if (empleados[j].getCargo() < empleados[minIdx].getCargo()) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Personal temp = empleados[i];
            empleados[i] = empleados[minIdx];
            empleados[minIdx] = temp;
        }
    }


    cout << "========== PERSONAL ACTIVO ORDENADO POR CARGO ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "CARGO";
    locate(27, fila); cout << "LEGAJO";
    locate(38, fila); cout << "APELLIDO";
    locate(59, fila); cout << "NOMBRE";
    fila++;

    locate(1, fila); cout << "--------------------------------------------------------------------------" << endl;
    fila++;

    for (int i = 0; i < leidos; i++) {
        locate(1, fila);  cout << empleados[i].getCargoComoTexto();
        locate(27, fila); cout << empleados[i].getLegajo();
        locate(38, fila); cout << empleados[i].getApellido();
        locate(59, fila); cout << empleados[i].getNombre();
        fila++;
    }
    cout << endl << endl;
}


int getTurnoScore(Personal p) {
    if (p.getTurno(0)) return 1; // Mañana
    if (p.getTurno(1)) return 2; // Tarde
    if (p.getTurno(2)) return 3; // Noche
    return 4;
}

void ArchivoPersonal::listarPorTurno() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay personal registrado." << endl;
        return;
    }
    const int MAX_PERSONAL = 1000;
    Personal empleados[MAX_PERSONAL];
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }


    int leidos = 0;

    Personal obj_temporal;

    while (leidos < cant && fread(&obj_temporal, sizeof(Personal), 1, p) == 1) {
        if (obj_temporal.getEstado()) {
            empleados[leidos] = obj_temporal;
            leidos++;
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay personal activo para ordenar." << endl;
        return;
    }

    for (int i = 0; i < leidos - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < leidos; j++) {
            if (getTurnoScore(empleados[j]) < getTurnoScore(empleados[minIdx])) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Personal temp = empleados[i];
            empleados[i] = empleados[minIdx];
            empleados[minIdx] = temp;
        }
    }

    cout << "========== PERSONAL ORDENADO POR TURNO (M, T, N) ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "TURNOS";
    locate(27, fila); cout << "LEGAJO";
    locate(38, fila); cout << "APELLIDO";
    locate(59, fila); cout << "NOMBRE";
    fila++;

    locate(1, fila); cout << "--------------------------------------------------------------------------" << endl;
    fila++;

    for (int i = 0; i < leidos; i++) {
        locate(1, fila);  cout << empleados[i].getTurnosComoTexto();
        locate(27, fila); cout << empleados[i].getLegajo();
        locate(38, fila); cout << empleados[i].getApellido();
        locate(59, fila); cout << empleados[i].getNombre();
        fila++;
    }
    cout << endl << endl;
}

void ArchivoPersonal::listarInactivos() {
    FILE *p = fopen("personal.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Personal obj;
    bool encontro = false;

    cout << "========== PERSONAL INACTIVO (DADOS DE BAJA) ==========" << endl << endl;


    int fila = 3;
    locate(1, fila);  cout << "LEGAJO";
    locate(12, fila); cout << "APELLIDO";
    locate(33, fila); cout << "NOMBRE";
    locate(54, fila); cout << "DNI";
    locate(67, fila); cout << "CARGO";
    fila++;
    locate(1, fila); cout << "-----------------------------------------------------------------------------" << endl;
    fila++;


    while (fread(&obj, sizeof(Personal), 1, p)) {

        if (!obj.getEstado()) {
            encontro = true;

            locate(1, fila);  cout << obj.getLegajo();
            locate(12, fila); cout << obj.getApellido();
            locate(33, fila); cout << obj.getNombre();
            locate(54, fila); cout << obj.getDni();
            locate(67, fila); cout << obj.getCargoComoTexto();

            fila++;
        }
    }
    fclose(p);

    locate(1, fila + 2);

    if (!encontro) {
        cout << "No hay personal inactivo para mostrar." << endl;
    }
    cout << endl;
}


