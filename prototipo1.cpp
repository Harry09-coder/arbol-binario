#include <iostream>
using namespace std;

struct Nodo {
    int dato;
    string nombre;
    char genero; // M y F
    int Generacion;
    Nodo *izq;
    Nodo *der;
};

Nodo *nuevoNodo(int valor) {
    Nodo *nodo = new Nodo();
    nodo->dato = valor;
    nodo->izq = NULL;
    nodo->der = NULL;
    return nodo;
}

//prototipos de funciones
void menu();
Nodo *CrearNodo(int);
void insertarNodo(Nodo *&,int);
void mostrarArbol(Nodo *,int);
bool busqueda(Nodo *,int);
void preOrden(Nodo *arbol);
//insertar
void insertarnodo(nodo *& arbol, int n)

//preorden
void PreOrden(nodo *arbol)
//inorden
void inOrden(Nodo *arbol)
//postorden
void PostOrden(nodo *arbol)
//mostrar
void mostrarArbol(nodo *arbol, int cont)

int main(){
    
return 0;
}
//definicion
//menu
void menu() {
    nodo* arbol = NULL;
    int opcion, dato;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Insertar nodo\n";
        cout << "2. Mostrar arbol \n";
        cout << "3. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese un numero: ";
                cin >> dato;
                
                break;
            case 2:
                cout << "Contenido del arbol (InOrden): ";
                
                cout << endl;
                break;
            case 3:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion invalida. Intente nuevamente.\n";
        }

    } while (opcion != 3);
}
