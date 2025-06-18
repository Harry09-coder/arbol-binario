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
