#include <iostream>     // Librería para entrada/salida estándar
#include <locale.h>     // Librería para configurar localización (acentos, caracteres especiales)
using namespace std;

// Estructura de un nodo del árbol genealógico
struct Nodo {
    int dato;           // ID del miembro
    string nombre;      // Nombre del miembro
    char genero;        // Género (M/F)
    int generacion;     // Número de generación
    Nodo *izq;          // Puntero al hijo izquierdo
    Nodo *der;          // Puntero al hijo derecho
};

// Prototipos de funciones
Nodo* crearNodo(int valor, string nombre, char genero, int generacion);
void insertarNodo(Nodo*& arbol, Nodo* nuevo);
Nodo* eliminarNodo(Nodo* arbol, int valor);
Nodo* buscarNodo(Nodo* arbol, int valor);
bool mostrarAncestros(Nodo* arbol, int valor);
void mostrarDescendientes(Nodo* nodo);
bool perteneceARama(Nodo* arbol, int raiz, int valor);
void recorridoInOrden(Nodo* arbol);
void recorridoPreOrden(Nodo* arbol);
void recorridoPostOrden(Nodo* arbol);
void mostrarArbol(Nodo* arbol, int cont = 0);
void menu();

// Función principal
int main() {
    setlocale(LC_ALL, "Spanish"); // Configura localización para caracteres en español
    menu();                        // Inicia el menú principal
    return 0;
}

// Crea y retorna un nuevo nodo con los datos dados
Nodo* crearNodo(int valor, string nombre, char genero, int generacion) {
    Nodo* nodo = new Nodo();
    nodo->dato = valor;
    nodo->nombre = nombre;
    nodo->genero = genero;
    nodo->generacion = generacion;
    nodo->izq = nodo->der = NULL; // Inicializa sin hijos
    return nodo;
}

// Inserta un nuevo nodo en el árbol binario de búsqueda
void insertarNodo(Nodo*& arbol, Nodo* nuevo) {
    if (!arbol)
        arbol = nuevo;
    else if (nuevo->dato < arbol->dato)
        insertarNodo(arbol->izq, nuevo);
    else
        insertarNodo(arbol->der, nuevo);
}

// Busca un nodo por su ID (dato)
Nodo* buscarNodo(Nodo* arbol, int valor) {
    if (!arbol) return NULL;
    if (arbol->dato == valor) return arbol;
    if (valor < arbol->dato)
        return buscarNodo(arbol->izq, valor);
    else
        return buscarNodo(arbol->der, valor);
}

// Muestra los ancestros de un nodo dado (de abajo hacia arriba)
bool mostrarAncestros(Nodo* arbol, int valor) {
    if (!arbol) return false;
    if (arbol->dato == valor) return true;

    if (mostrarAncestros(arbol->izq, valor) || mostrarAncestros(arbol->der, valor)) {
        cout << arbol->dato << " - " << arbol->nombre << endl;
        return true;
    }
    return false;
}

// Muestra todos los descendientes de un nodo
void mostrarDescendientes(Nodo* nodo) {
    if (!nodo) return;
    if (nodo->izq) {
        cout << nodo->izq->dato << " - " << nodo->izq->nombre << endl;
        mostrarDescendientes(nodo->izq);
    }
    if (nodo->der) {
        cout << nodo->der->dato << " - " << nodo->der->nombre << endl;
        mostrarDescendientes(nodo->der);
    }
}

// Elimina un nodo con cierto ID del árbol
Nodo* eliminarNodo(Nodo* arbol, int valor) {
    if (!arbol) return NULL;

    if (valor < arbol->dato)
        arbol->izq = eliminarNodo(arbol->izq, valor);
    else if (valor > arbol->dato)
        arbol->der = eliminarNodo(arbol->der, valor);
    else {
        // Caso 1: sin hijo izquierdo
        if (!arbol->izq) {
            Nodo* temp = arbol->der;
            delete arbol;
            return temp;
        }
        // Caso 2: sin hijo derecho
        else if (!arbol->der) {
            Nodo* temp = arbol->izq;
            delete arbol;
            return temp;
        }
        // Caso 3: con dos hijos, buscar sucesor
        Nodo* reemplazo = arbol->der;
        while (reemplazo->izq)
            reemplazo = reemplazo->izq;

        // Copiar datos del sucesor
        arbol->dato = reemplazo->dato;
        arbol->nombre = reemplazo->nombre;
        arbol->genero = reemplazo->genero;
        arbol->generacion = reemplazo->generacion;

        // Eliminar el sucesor
        arbol->der = eliminarNodo(arbol->der, reemplazo->dato);
    }
    return arbol;
}

// Verifica si un nodo pertenece a la subrama de otro nodo
bool perteneceARama(Nodo* arbol, int raiz, int valor) {
    Nodo* subraiz = buscarNodo(arbol, raiz); // Buscar la raíz de la rama
    if (!subraiz) return false;
    return buscarNodo(subraiz, valor) != NULL; // Buscar si el valor existe bajo esa subraíz
}

// Recorrido InOrden: Izquierda - Raíz - Derecha
void recorridoInOrden(Nodo* arbol) {
    if (arbol) {
        recorridoInOrden(arbol->izq);
        cout << arbol->dato << " - " << arbol->nombre << " (" << arbol->genero << ", Gen " << arbol->generacion << ")\n";
        recorridoInOrden(arbol->der);
    }
}

// Recorrido PreOrden: Raíz - Izquierda - Derecha
void recorridoPreOrden(Nodo* arbol) {
    if (arbol) {
        cout << arbol->dato << " - " << arbol->nombre << " (" << arbol->genero << ", Gen " << arbol->generacion << ")\n";
        recorridoPreOrden(arbol->izq);
        recorridoPreOrden(arbol->der);
    }
}

// Recorrido PostOrden: Izquierda - Derecha - Raíz
void recorridoPostOrden(Nodo* arbol) {
    if (arbol) {
        recorridoPostOrden(arbol->izq);
        recorridoPostOrden(arbol->der);
        cout << arbol->dato << " - " << arbol->nombre << " (" << arbol->genero << ", Gen " << arbol->generacion << ")\n";
    }
}

// Muestra el árbol en forma gráfica (gira 90° el árbol hacia la izquierda)
void mostrarArbol(Nodo* arbol, int cont) {
    if (arbol) {
        mostrarArbol(arbol->der, cont + 1);
        for (int i = 0; i < cont; i++) cout << "   ";
        cout << arbol->dato << " - " << arbol->nombre << endl;
        mostrarArbol(arbol->izq, cont + 1);
    }
}

// Menú interactivo para manipular el árbol genealógico
void menu() {
    Nodo* arbol = NULL;
    int opcion, dato, gen, idBusqueda, raiz;
    string nombre;
    char genero;

    do {
        cout << "\n--- MENÚ ÁRBOL GENEALÓGICO INKA ---\n";
        cout << "1. Insertar miembro\n";
        cout << "2. Eliminar miembro\n";
        cout << "3. Buscar miembro\n";
        cout << "4. Mostrar ancestros\n";
        cout << "5. Mostrar descendientes\n";
        cout << "6. Verificar pertenencia a rama\n";
        cout << "7. Mostrar árbol (vista gráfica)\n";
        cout << "8. Recorrido InOrden\n";
        cout << "9. Recorrido PreOrden\n";
        cout << "10. Recorrido PostOrden\n";
        cout << "11. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese ID: "; cin >> dato;
                cin.ignore();
                cout << "Nombre: "; getline(cin, nombre);
                cout << "Género (M/F): "; cin >> genero;
                cout << "Generación: "; cin >> gen;
                insertarNodo(arbol, crearNodo(dato, nombre, genero, gen));
                break;
            case 2:
                cout << "Ingrese ID a eliminar: ";
                cin >> dato;
                arbol = eliminarNodo(arbol, dato);
                break;
            case 3:
                cout << "Ingrese ID a buscar: ";
                cin >> dato;
                if (Nodo* res = buscarNodo(arbol, dato))
                    cout << res->dato << " - " << res->nombre << endl;
                else
                    cout << "No encontrado.\n";
                break;
            case 4:
                cout << "Ingrese ID para mostrar ancestros: ";
                cin >> dato;
                if (!mostrarAncestros(arbol, dato))
                    cout << "No se encontraron ancestros.\n";
                break;
            case 5:
                cout << "Ingrese ID para mostrar descendientes: ";
                cin >> dato;
                if (Nodo* n = buscarNodo(arbol, dato))
                    mostrarDescendientes(n);
                else
                    cout << "Nodo no encontrado.\n";
                break;
            case 6:
                cout << "Ingrese ID de la raíz de la rama: ";
                cin >> raiz;
                cout << "Ingrese ID del nodo a verificar: ";
                cin >> idBusqueda;
                if (perteneceARama(arbol, raiz, idBusqueda))
                    cout << "El nodo pertenece a la rama.\n";
                else
                    cout << "El nodo NO pertenece a la rama.\n";
                break;
            case 7:
                mostrarArbol(arbol);
                break;
            case 8:
                cout << "\nRecorrido InOrden:\n";
                recorridoInOrden(arbol);
                break;
            case 9:
                cout << "\nRecorrido PreOrden:\n";
                recorridoPreOrden(arbol);
                break;
            case 10:
                cout << "\nRecorrido PostOrden:\n";
                recorridoPostOrden(arbol);
                break;
            case 11:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opción inválida. Intente nuevamente.\n";
        }
    } while (opcion != 11);
}
