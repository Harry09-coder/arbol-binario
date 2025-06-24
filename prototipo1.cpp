#include <iostream>
#include <string>
using namespace std;

// Estructura Persona
struct Persona {
    int id;
    string nombre;
    char genero;
    int generacion;
    Persona* padre;
    Persona* madre;
};

// Prototipos
Persona* crearPersona(int id, string nombre, char genero, int generacion);
Persona* buscarPersona(Persona* raiz, int id);
void insertarPadreMadre(Persona* raiz, int hijoID, int id, string nombre, char genero);
void mostrarArbol(Persona* p, int espacio = 0);
void mostrarFamilia(Persona* p);
void inorden(Persona* p);
void preorden(Persona* p);
void postorden(Persona* p);
void mostrarAncestros(Persona* p);
bool eliminarPersona(Persona*& raiz, int id);
void liberarArbol(Persona*& raiz);
void menu();
int validarID(); // Nueva funcion para validar ID

// Funcion principal
int main() {
    setlocale(LC_ALL, "Spanish");
    menu();
    return 0;
}

// Crea una nueva persona
Persona* crearPersona(int id, string nombre, char genero, int generacion) {
    Persona* p = new Persona;
    p->id = id;
    p->nombre = nombre;
    p->genero = genero;
    p->generacion = generacion;
    p->padre = NULL;
    p->madre = NULL;
    return p;
}

// Busca una persona por ID
Persona* buscarPersona(Persona* raiz, int id) {
    if (raiz == NULL) return NULL;
    if (raiz->id == id) return raiz;
    
    Persona* encontrado = buscarPersona(raiz->padre, id);
    if (encontrado != NULL) return encontrado;
    
    return buscarPersona(raiz->madre, id);
}

// Inserta padre o madre a un hijo
void insertarPadreMadre(Persona* raiz, int hijoID, int id, string nombre, char genero) {
    Persona* hijo = buscarPersona(raiz, hijoID);
    if (hijo == NULL) {
        cout << "Error: el hijo con ID " << hijoID << " no existe.\n";
        return;
    }
    
    Persona* existe = buscarPersona(raiz, id);
    if (existe != NULL) {
        cout << "Error: ese ID ya existe.\n";
        return;
    }
    
    genero = toupper(genero);
    if (genero != 'M' && genero != 'F') {
        cout << "Error: genero invalido. Use M para masculino o F para femenino.\n";
        return;
    }
    
    Persona* nuevo = crearPersona(id, nombre, genero, hijo->generacion + 1);
    
    if (genero == 'M') {
        if (hijo->padre == NULL) {
            hijo->padre = nuevo;
        } else {
            cout << "Advertencia: el padre ya existe.\n";
            delete nuevo;
        }
    } else {
        if (hijo->madre == NULL) {
            hijo->madre = nuevo;
        } else {
            cout << "Advertencia: la madre ya existe.\n";
            delete nuevo;
        }
    }
}

// Muestra el arbol
void mostrarArbol(Persona* p, int espacio) {
    if (p == NULL) return;
    
    espacio += 5;
    mostrarArbol(p->madre, espacio);
    
    for (int i = 5; i < espacio; i++) 
        cout << " ";
    cout << p->id << " - " << p->nombre << " (G" << p->generacion << ")\n";
    
    mostrarArbol(p->padre, espacio);
}

// Muestra los datos de una persona
void mostrarFamilia(Persona* p) {
    if (p == NULL) {
        cout << "Persona no encontrada.\n";
        return;
    }
    
    cout << "\nID: " << p->id << ", Nombre: " << p->nombre 
         << ", Genero: " << p->genero << ", Generacion: " << p->generacion << "\n";
    cout << "Padre: " << (p->padre ? p->padre->nombre : "Desconocido") << "\n";
    cout << "Madre: " << (p->madre ? p->madre->nombre : "Desconocida") << "\n";
}

// Recorridos
void inorden(Persona* p) {
    if (p == NULL) return;
    inorden(p->padre);
    cout << p->id << " - " << p->nombre << "\n";
    inorden(p->madre);
}

void preorden(Persona* p) {
    if (p == NULL) return;
    cout << p->id << " - " << p->nombre << "\n";
    preorden(p->padre);
    preorden(p->madre);
}

void postorden(Persona* p) {
    if (p == NULL) return;
    postorden(p->padre);
    postorden(p->madre);
    cout << p->id << " - " << p->nombre << "\n";
}

// Muestra ancestros de una persona
void mostrarAncestros(Persona* p) {
    if (p == NULL) {
        cout << "Persona no encontrada.\n";
        return;
    }
    
    if (p->padre) {
        cout << "Padre: " << p->padre->nombre << "\n";
        mostrarAncestros(p->padre);
    }
    if (p->madre) {
        cout << "Madre: " << p->madre->nombre << "\n";
        mostrarAncestros(p->madre);
    }
}

// Elimina una persona y sus ancestros
bool eliminarPersona(Persona*& raiz, int id) {
    if (raiz == NULL) return false;

    if (raiz->id == id) {
        liberarArbol(raiz->padre);
        liberarArbol(raiz->madre);
        delete raiz;
        raiz = NULL;
        return true;
    }

    bool encontrado = eliminarPersona(raiz->padre, id);
    if (encontrado) return true;
    
    return eliminarPersona(raiz->madre, id);
}

// Libera memoria del arbol
void liberarArbol(Persona*& raiz) {
    if (raiz == NULL) return;
    liberarArbol(raiz->padre);
    liberarArbol(raiz->madre);
    delete raiz;
    raiz = NULL;
}

// Valida que el ID sea positivo
int validarID() {
    int id;
    do {
        cout << "Ingrese un ID (mayor a 0): ";
        cin >> id;
        if (id <= 0) {
            cout << "Error: El ID debe ser mayor a cero.\n";
        }
    } while (id <= 0);
    return id;
}

// Menu principal
void menu() {
    Persona* raiz = NULL;
    int opcion, id, hijoID;
    string nombre;
    char genero;

    do {
        cout << "\n--- MENU ARBOL GENEALOGICO ---\n";
        cout << "1. Agregar descendiente principal (raiz)\n";
        cout << "2. Agregar padre o madre\n";
        cout << "3. Mostrar arbol\n";
        cout << "4. Mostrar familia por ID\n";
        cout << "5. Mostrar ancestros\n";
        cout << "6. Recorrido inorden\n";
        cout << "7. Recorrido preorden\n";
        cout << "8. Recorrido postorden\n";
        cout << "9. Eliminar persona y ancestros\n";
        cout << "10. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                system("cls");
                if (raiz != NULL) {
                    cout << "Ya existe un descendiente principal (raiz).\n";
                    break;
                }
                id = validarID();
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Genero (M/F): "; cin >> genero;
                genero = toupper(genero);
                if (genero != 'M' && genero != 'F') {
                    cout << "Genero invalido. Use M o F.\n";
                    break;
                }
                raiz = crearPersona(id, nombre, genero, 1);
                cout << "Raiz agregada correctamente.\n";
                break;

            case 2:
                hijoID = validarID();
                id = validarID();
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Genero (M/F): "; cin >> genero;
                insertarPadreMadre(raiz, hijoID, id, nombre, genero);
                break;

            case 3:
                system("cls");
                mostrarArbol(raiz); 
                break;

            case 4:
                id = validarID();
                mostrarFamilia(buscarPersona(raiz, id));
                break;

            case 5:
                id = validarID();
                mostrarAncestros(buscarPersona(raiz, id));
                break;

            case 6:
                system("cls");
                inorden(raiz); 
                break;

            case 7:
                system("cls");
                preorden(raiz); 
                break;

            case 8:
                system("cls");
                postorden(raiz); 
                break;

            case 9:
                id = validarID();
                if (id == (raiz ? raiz->id : -1)) {
                    liberarArbol(raiz);
                    cout << "Arbol completo eliminado.\n";
                } else if (eliminarPersona(raiz, id)) {
                    cout << "Persona y sus ancestros eliminados.\n";
                } else {
                    cout << "Persona no encontrada.\n";
                }
                break;

            case 10:
                liberarArbol(raiz);
                cout << "Saliendo del programa arbol\n"; 
                break;

            default:
                cout << "Opcion invalida.\n";
        }
    } while (opcion != 10);
}
