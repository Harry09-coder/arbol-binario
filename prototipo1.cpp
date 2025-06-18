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
void insertarnodo()

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
