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
// Función para insertar elementos en el árbol
void insertarnodo(nodo *& arbol, int n) {
    if (arbol == NULL) { // si el arbol está vacío
        nodo *nuevo_nodo = crearnodo(n);
        arbol = nuevo_nodo;
    }
    else{ // si el árbol tiene un nodo o más
        int valorRaiz = arbol->dato; // obtenemos el valor de la raíz
        if (n < valorRaiz){ // si el elemento es menor a la raíz, insertamos en izq
            insertarnodo(arbol->izq, n);
        }
        else{// si el elemento es mayor a la raíz, insertamos en der
            insertarnodo(arbol->der, n);
        }
    }
}

//preorden

//inorden

//postorden

//mostrar
int main(){

return 0;
}
//Funcion para mostrar el arbol completo
void mostrarArbol(nodo *arbol, int cont){
    if(arbol == NULL){//Saber si el arbol esta vacio.
        return;
    }
    else{//Si no esta vacio.
        mostrarArbol(arbol->der,cont+1);//imprimiendo lado derecho.
        for(int i=0 ; i<cont ; i++){
            cout<<"   ";
        }
        cout<<arbol->dato<<endl;
        mostrarArbol(arbol->izq,cont+1);//imprimiendo lado izquierdo.
    }
}
//definicion
