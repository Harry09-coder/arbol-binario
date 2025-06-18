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
// Definición de insertar elementos en un árbol
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
//definicion de in-Orden
void inOrden(Nodo *arbol){
 if(arbol == NULL){
  return;
 }
 else{
  inOrden(arbol->izq);
  cout<<arbol->dato<<" - ";
  inOrden(arbol->der);
 }
}
//definicion de Pre-Orden
void PreOrden(nodo *arbol){
	if(arbol == NULL){
		return ;
	}else{
		cout<<arbol->dato<<" - ";
		PreOrden(arbol->izq);
		PreOrden(arbol->der);
	}
}
//definicion de post-Orden
void PostOrden(nodo *arbol){
	if(arbol == NULL){
		return ;
	}else{
		PostOrden(arbol->izq);
		PostOrden(arbol->der);
		cout<<arbol->dato<<" - ";
	}
}
//definicion de mostrar
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

