#include "ArchivoCursos.h"
#include "ArchivoPersonal.h"
#include <cstring>
#include <iostream>
#include "rlutil.h"


using namespace std;
using namespace rlutil;


ArchivoCursos::ArchivoCursos(const char *n) {
    strncpy(nombre, n, 29);
    nombre[29] = '\0';
}

/// metodos bascios

int ArchivoCursos::contarRegistros() {
    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Curso);
}

Curso ArchivoCursos::leerRegistro(int pos) {
    Curso obj;
    obj.setIdCurso(-1);
    obj.setEstado(false);

    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        return obj;
    }

    fseek(p, pos * sizeof(Curso), SEEK_SET);
    fread(&obj, sizeof(Curso), 1, p);

    fclose(p);
    return obj;
}

bool ArchivoCursos::grabarRegistro(Curso obj) {
    FILE *p = fopen("Cursos.dat", "ab");
    if (p == nullptr) {
        return false;
    }
    bool escribio = fwrite(&obj, sizeof(Curso), 1, p);
    fclose(p);
    return escribio;
}

bool ArchivoCursos::modificarRegistro(Curso obj, int pos) {
    FILE *p = fopen("Cursos.dat", "rb+");
    if (p == nullptr) {
        return false;
    }

    fseek(p, pos * sizeof(Curso), SEEK_SET);
    bool escribio = fwrite(&obj, sizeof(Curso), 1, p);

    fclose(p);
    return escribio;
}

int ArchivoCursos::generarIdCurso() {
    return contarRegistros() + 101;
}

Curso ArchivoCursos::buscarYLeerPorId(int id) {
    int pos = buscarPorId(id);
    if (pos >= 0) {
        return leerRegistro(pos);
    }
    return leerRegistro(-1);
}

// --- BÚSQUEDAS ---

int ArchivoCursos::buscarPorId(int idCurso) {
    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        return -1;
    }
    Curso obj;
    int pos = 0;
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getIdCurso() == idCurso) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}

int ArchivoCursos::buscarPorAula(int aula) {
    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        return -1;
    }
    Curso obj;
    int pos = 0;
    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getNumAula() == aula) {
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -2;
}
//// alta baja modificar

void ArchivoCursos::darDeAlta() {
    cout << "--- ALTA DE NUEVO CURSO ---" << endl;

    Curso nuevoCurso;

    if (!nuevoCurso.Cargar()) {
        cout << "Alta cancelada por el usuario." << endl;
        return;
    }

    int legajoDoc;
    while (true) {
        cout << "Ingrese Legajo del Docente a cargo (ej. 5001): " << endl;
        if (cin >> legajoDoc) {

            ArchivoPersonal adminPersonal("personal.dat");
            int posDocente = adminPersonal.buscarPorLegajoDocente(legajoDoc);

            if (posDocente >= 0) {   //// aca validamos, xq te devuelve -1 o -2 si no se encontro el  legajo entonces si es >0 es que lo encontro y lo asignamos
                nuevoCurso.setLegajoDocente(legajoDoc);
                break;
            } else {
                cout << "*** ERROR: No se encontro un Docente con el legajo " << legajoDoc << ". ***" << endl;
            }
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int nuevoID = generarIdCurso();
    nuevoCurso.setIdCurso(nuevoID);
    nuevoCurso.setEstado(true);

    cout << "***********************************" << endl;
    cout << "  NUEVO ID DE CURSO ASIGNADO: " << nuevoID << endl;
    cout << "***********************************" << endl;

    if (grabarRegistro(nuevoCurso)) {
        cout << "¡Curso '" << nuevoCurso.getDescripcion() << "' dado de alta exitosamente!" << endl;
    } else {
        cout << "*** ERROR: No se pudo grabar el registro. ***" << endl;
    }
}

void ArchivoCursos::darDeBaja() {
    cout << "--- BAJA DE CURSO ---" << endl;
    int id;

    while (true) {
        cout << "Ingrese el ID del curso a dar de baja: " << endl;
        if (cin >> id) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorId(id);
    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro un curso con el ID " << id << ". ***" << endl;
        return;
    }

    Curso obj = leerRegistro(pos);
    if (!obj.getEstado()) {
        cout << "Este curso ya se encuentra INACTIVO." << endl;
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
            cout << "El curso fue dado de baja exitosamente." << endl;
        } else {
            cout << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void ArchivoCursos::reactivar() {
    cout << "--- REACTIVAR CURSO ---" << endl;
    int id;

    while (true) {
        cout << "Ingrese el ID del curso a reactivar: " << endl;
        if (cin >> id) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorId(id);
     if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro un curso con el ID " << id << ". ***" << endl;
        return;
    }

    Curso obj = leerRegistro(pos);
    if (obj.getEstado()) {
        cout << "Este curso ya se encuentra ACTIVO." << endl;
        return;
    }

    cout << "Se encontro el siguiente registro (INACTIVO):" << endl;
    obj.Mostrar();
    cout << "--------------------------------" << endl;

    int confirmacion;
    cout << "Desea reactivar este curso? (1 - SI / 0 - NO): " << endl;
    cin >> confirmacion;

    if (confirmacion == 1) {
        obj.setEstado(true);
        if (modificarRegistro(obj, pos)) {
            cout << "El curso fue reactivado exitosamente." << endl;
        } else {
            cout << "*** ERROR: No se pudo modificar el registro. ***" << endl;
        }
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

void ArchivoCursos::modificar() {
    cout << "--- MODIFICAR CURSO ---" << endl;
    int id;

    while (true) {
        cout << "Ingrese el ID del curso a modificar: " << endl;
        if (cin >> id) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorId(id);
    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro un curso con el ID " << id << ". ***" << endl;
        return;
    }

    Curso obj = leerRegistro(pos);
    int opcion;
    bool salir = false;

    while (!salir) {
        system("cls");
        cout << "--- MODIFICANDO CURSO ---" << endl;
        obj.Mostrar();
        cout << "--------------------------------" << endl;
        cout << "Que desea modificar?" << endl;
        cout << "1. Descripcion" << endl;
        cout << "2. Numero de Aula" << endl;
        cout << "3. Capacidad Maxima" << endl;
        cout << "4. Anio" << endl;
        cout << "5. Costo de Matricula" << endl;
        cout << "6. Reasignar Docente" << endl;
        cout << "--------------------------------" << endl;
        cout << "0. GUARDAR Y SALIR" << endl;
        cout << "Opcion: " << endl;
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
                char descTemporal[100];
                cout << "Ingrese Descripcion del Curso: " << endl;
                cin.ignore(10000, '\n');
                cin.getline(descTemporal, 100);
                obj.setDescripcion(descTemporal);
                cout << "Descripcion actualizada." << endl;
                break;
            }
            case 2: {
                int intTemporal;
                while (true) {
                    cout << "Ingrese Numero de Aula: " << endl;
                    if (cin >> intTemporal) {
                        if (obj.setNumAula(intTemporal)) {
                            cout << "Aula actualizada." << endl;
                            break;
                        } else {
                            cout << "*** ERROR: El numero de aula debe ser positivo. ***" << endl;
                        }
                    } else {
                        cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                break;
            }
            case 3: {
                int intTemporal;
                while (true) {
                    cout << "Ingrese Capacidad Maxima de Alumnos: " << endl;
                    if (cin >> intTemporal) {
                        if (obj.setMaxAlumnos(intTemporal)) {
                            cout << "Capacidad actualizada." << endl;
                            break;
                        } else {
                            cout << "*** ERROR: La capacidad debe ser positiva. ***" << endl;
                        }
                    } else {
                        cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                break;
            }
            case 4: {
                int intTemporal;
                while (true) {
                    cout << "Ingrese Anio (ej. 2024): " << endl;
                    if (cin >> intTemporal) {
                        if (obj.setAnio(intTemporal)) {
                            cout << "Anio actualizado." << endl;
                            break;
                        } else {
                            cout << "*** ERROR: El anio debe ser entre 2020 y 2030. ***" << endl;
                        }
                    } else {
                        cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                break;
            }
            case 5: {
                float floatTemporal;
                while (true) {
                    cout << "Ingrese Costo de Matricula: " << endl;
                    if (cin >> floatTemporal) {
                        if (obj.setCostoMatricula(floatTemporal)) {
                            cout << "Costo actualizado." << endl;
                            break;
                        } else {
                            cout << "*** ERROR: El costo no puede ser negativo. ***" << endl;
                        }
                    } else {
                        cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                break;
            }
            case 6: { // Reasignar Docente
                int legajoDoc;
                while (true) {
                    cout << "Ingrese NUEVO Legajo del Docente a cargo (ej. 5001): " << endl;
                    if (cin >> legajoDoc) {
                        ArchivoPersonal adminPersonal("personal.dat");
                        int posDocente = adminPersonal.buscarPorLegajoDocente(legajoDoc);

                        if (posDocente >= 0) {
                            obj.setLegajoDocente(legajoDoc);
                            cout << "Docente reasignado exitosamente." << endl;
                            break;
                        } else {
                            cout << "*** ERROR: No se encontro un Docente con el legajo " << legajoDoc << ". ***" << endl;
                        }
                    } else {
                        cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
                        cin.clear();
                        cin.ignore(10000, '\n');
                    }
                }
                break;
            }
            case 0: {
                cout << "Guardando cambios..." << endl;
                if (modificarRegistro(obj, pos)) {
                    cout << "El curso fue modificado exitosamente." << endl;
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

void ArchivoCursos::listarActivos() {
    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Curso obj;
    bool encontro = false;

    cout << "========== CURSOS ACTIVOS (POR ORDEN DE ID) ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "ID CURSO";
    locate(12, fila); cout << "DESCRIPCION";
    locate(43, fila); cout << "AULA";
    locate(50, fila); cout << "DOCENTE (Leg.)";
    locate(67, fila); cout << "MAX. ALUMNOS";
    locate(83, fila); cout << "$ MAT.";
    locate(93, fila); cout << "ANIO";
    fila++;
    locate(1, fila); cout << "-----------------------------------------------------------------------------" << endl;
    fila++;

    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getEstado()) {
            encontro = true;

            locate(1, fila);  cout << obj.getIdCurso();
            locate(12, fila); cout << obj.getDescripcion();
            locate(43, fila); cout << obj.getNumAula();
            locate(50, fila); cout << obj.getLegajoDocente();
            locate(67, fila); cout << obj.getMaxAlumnos();
            locate(83, fila); cout << obj.getCostoMatricula();
            locate(93, fila); cout << obj.getAnio();

            fila++;
        }
    }
    fclose(p);

    locate(1, fila + 2);

    if (!encontro) {
        cout << "No hay cursos activos para mostrar." << endl;
    }
    cout << endl;
}

/// listados
void ArchivoCursos::listarInactivos() {
    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Curso obj;
    bool encontro = false;

    cout << "========== CURSOS INACTIVOS (DADOS DE BAJA) ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "ID CURSO";
    locate(12, fila); cout << "DESCRIPCION";
    locate(43, fila); cout << "AULA";
    locate(50, fila); cout << "DOCENTE (Leg.)";
    fila++;
    locate(1, fila); cout << "------------------------------------------------------------------" << endl;
    fila++;

    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (!obj.getEstado()) {
            encontro = true;

            locate(1, fila);  cout << obj.getIdCurso();
            locate(12, fila); cout << obj.getDescripcion();
            locate(43, fila); cout << obj.getNumAula();
            locate(50, fila); cout << obj.getLegajoDocente();

            fila++;
        }
    }
    fclose(p);

    locate(1, fila + 2);

    if (!encontro) {
        cout << "No hay cursos inactivos para mostrar." << endl;
    }
    cout << endl;
}

void ArchivoCursos::listarPorIdCurso() {
    cout << "--- REDIRIGIENDO A LISTADO DE CURSOS ACTIVOS (ORDENADOS POR ID) ---" << endl;
    listarActivos();
}


void ArchivoCursos::listarPorMaxAlumnos() {
    int cant = contarRegistros();
    if (cant == 0) {
        cout << "No hay cursos registrados." << endl;
        return;
    }

    const int MAX_CURSOS = 1000;
    if(cant > MAX_CURSOS){
        cout << "Hay demasiados registros para este método." << endl;
        return;
    }
    Curso cursos[MAX_CURSOS];

    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }

    int leidos = 0;
    Curso obj_temporal;
    while (leidos < cant && fread(&obj_temporal, sizeof(Curso), 1, p) == 1) {
        if (obj_temporal.getEstado()) {
            cursos[leidos] = obj_temporal;
            leidos++;
        }
    }
    fclose(p);

    if (leidos == 0) {
        cout << "No hay cursos activos para ordenar." << endl;
        return;
    }


    for (int i = 0; i < leidos - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < leidos; j++) {

            if (cursos[j].getMaxAlumnos() > cursos[maxIdx].getMaxAlumnos()) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Curso temp = cursos[i];
            cursos[i] = cursos[maxIdx];
            cursos[maxIdx] = temp;
        }
    }

    cout << "========== CURSOS ACTIVOS ORDENADOS POR CAPACIDAD (MAYOR A MENOR) ==========" << endl << endl;

    int fila = 3;
    locate(1, fila);  cout << "MAX. ALUMNOS";
    locate(16, fila); cout << "ID CURSO";
    locate(27, fila); cout << "DESCRIPCION";
    locate(58, fila); cout << "AULA";
    fila++;
    locate(1, fila); cout << "------------------------------------------------------------------" << endl;
    fila++;

    for (int i = 0; i < leidos; i++) {
        locate(1, fila);  cout << cursos[i].getMaxAlumnos();
        locate(16, fila); cout << cursos[i].getIdCurso();
        locate(27, fila); cout << cursos[i].getDescripcion();
        locate(58, fila); cout << cursos[i].getNumAula();
        fila++;
    }
    cout << endl << endl;
}
/// consultas
void ArchivoCursos::consultarPorNumAula() {
    cout << "--- CONSULTAR CURSOS POR AULA ---" << endl;
    int numAula;

    while (true) {
        cout << "Ingrese el numero de aula a consultar: " << endl;
        if (cin >> numAula) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Curso obj;
    bool encontro = false;

    cout << "========== CURSOS ACTIVOS EN EL AULA " << numAula << " ==========" << endl;

    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getNumAula() == numAula && obj.getEstado()) {
            encontro = true;
            obj.Mostrar();
            cout << "--------------------------------" << endl;
        }
    }
    fclose(p);

    if (!encontro) {
        cout << "No se encontraron cursos activos en esa aula." << endl;
    }
    cout << endl;
}

void ArchivoCursos::consularPorLegajoDocente() {
    cout << "--- CONSULTAR CURSOS POR DOCENTE ---" << endl;
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

    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Curso obj;
    bool encontro = false;

    cout << "========== CURSOS ACTIVOS ASIGNADOS AL DOCENTE " << legajoDocente << " ==========" << endl;

    while (fread(&obj, sizeof(Curso), 1, p)) {
        if (obj.getLegajoDocente() == legajoDocente && obj.getEstado()) {
            encontro = true;
            obj.Mostrar();
            cout << "--------------------------------" << endl;
        }
    }
    fclose(p);

    if (!encontro) {
        cout << "No se encontraron cursos activos para ese docente." << endl;
    }
    cout << endl;
}

void ArchivoCursos::consultarPorCosto() {
    cout << "--- CONSULTAR CURSOS POR COSTO ---" << endl;

    int operador;
    float monto;


    while (true) {
        cout << "Seleccione el tipo de filtro:" << endl;
        cout << "1. Listar cursos con costo MAYOR A" << endl;
        cout << "2. Listar cursos con costo MENOR A" << endl;
        cout << "Opcion: " << endl;

        if (cin >> operador && (operador == 1 || operador == 2)) {
            break;
        } else {
            cout << "*** ERROR: Opcion no valida. Debe ser 1 o 2. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }


    while (true) {
        cout << "Ingrese el monto a comparar (ej. 5000): " << endl;
        if (cin >> monto && monto >= 0) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar un monto numerico positivo. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    FILE *p = fopen("Cursos.dat", "rb");
    if (p == nullptr) {
        cout << "No hay registros o error al abrir." << endl;
        return;
    }

    Curso obj;
    bool encontro = false;


    if (operador == 1) {
        cout << "========== CURSOS ACTIVOS CON COSTO MAYOR A $" << monto << " ==========" << endl;
    } else {
        cout << "========== CURSOS ACTIVOS CON COSTO MENOR A $" << monto << " ==========" << endl;
    }

    // 4. Leer el archivo y aplicar el filtro
    while (fread(&obj, sizeof(Curso), 1, p)) {

        // Siempre filtramos por cursos ACTIVOS
        if (obj.getEstado()) {

            // Aplicamos el filtro de costo seleccionado
            if (operador == 1 && obj.getCostoMatricula() > monto) {
                obj.Mostrar();
                cout << "--------------------------------" << endl;
                encontro = true;
            } else if (operador == 2 && obj.getCostoMatricula() < monto) {
                obj.Mostrar();
                cout << "--------------------------------" << endl;
                encontro = true;
            }
        }
    }
    fclose(p);

    if (!encontro) {
        cout << "No se encontraron cursos activos que cumplan ese criterio." << endl;
    }
    cout << endl;
}

void ArchivoCursos::consultarPorIdCurso() {
    cout << "--- CONSULTAR CURSO POR ID ---" << endl;
    int id;

    while (true) {
        cout << "Ingrese el ID del curso a consultar: " << endl;
        if (cin >> id) {
            break;
        } else {
            cout << "*** ERROR: Debe ingresar solo numeros. ***" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }

    int pos = buscarPorId(id);
    if (pos < 0) {
        if(pos == -1) cout << "*** ERROR: No se pudo abrir el archivo. ***" << endl;
        if(pos == -2) cout << "*** ERROR: No se encontro un curso con el ID " << id << ". ***" << endl;
        return;
    }

    cout << "Se encontro el siguiente registro:" << endl;
    Curso obj = leerRegistro(pos);
    obj.Mostrar();
    cout << "--------------------------------" << endl;
}
