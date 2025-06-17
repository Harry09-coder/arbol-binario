#include <iostream>
#include <string>
using namespace std;

// Estructura 
struct Persona {
    int id;
    string nombre;
    char genero;      // solo en'M' o 'F'
    int generacion;   //  0
    Persona* izquierdo;
    Persona* derecho;

    Persona(int _id, string _nombre, char _genero, int _generacion)
        : id(_id), nombre(_nombre), genero(_genero), generacion(_generacion),
          izquierdo(NULL), derecho(NULL) {}
};

// Prototipos de funciones
void insertar(Persona*& raiz, Persona* nuevo);
Persona* encontrarMinimo(Persona* nodo);
Persona* eliminar(Persona* raiz, string nombre);
Persona* buscar(Persona* raiz, string nombre);
void inorden(Persona* raiz);
void mostrarArbol(Persona* raiz);
void liberarArbol(Persona* raiz);

int main() {
    setlocale(LC_CTYPE, "Spanish");
    Persona* raiz = NULL;

    // Insertar
    insertar(raiz, new Persona(1, "Pachacutec", 'M', 0));
    insertar(raiz, new Persona(2, "Tupac Yupanqui", 'M', 1));
    insertar(raiz, new Persona(3, "Mama Anahuarque", 'F', 1));
    insertar(raiz, new Persona(4, "Amaru Yupanqui", 'M', 2));
    insertar(raiz, new Persona(5, "Cusi Coyllur", 'F', 2));
    insertar(raiz, new Persona(6, "Huayna Capac", 'M', 3));
    insertar(raiz, new Persona(7, "Rahua Ocllo", 'F', 3));
    insertar(raiz, new Persona(8, "Huascar", 'M', 4));
    insertar(raiz, new Persona(9, "Atahualpa", 'M', 4));
    insertar(raiz, new Persona(10, "Quispe Sisa", 'F', 4));

    // Ejemplo 1: Mostrar arbol completo
    cout << "1. Árbol completo:" << endl;
    mostrarArbol(raiz);

    // Ejemplo 2: Buscar persona existente
    cout << "\n2. Buscar a 'Huayna Capac':" << endl;
    Persona* encontrado = buscar(raiz, "Huayna Capac");
    if (encontrado) {
        cout << "Encontrado: " << encontrado->nombre << " (Gen " << encontrado->generacion << ")" << endl;
    }

    // Ejemplo 3: Buscar persona inexistente
    cout << "\n3. Buscar a 'Manco Capac':" << endl;
    encontrado = buscar(raiz, "Manco Capac");
    if (!encontrado) {
        cout << "No encontrado" << endl;
    }

    // Ejemplo 4: Eliminar persona sin hijos
    cout << "\n4. Eliminar a 'Quispe Sisa' (sin hijos):" << endl;
    raiz = eliminar(raiz, "Quispe Sisa");
    mostrarArbol(raiz);

    // Ejemplo 5: Eliminar persona con un hijo
    cout << "\n5. Eliminar a 'Rahua Ocllo' (con un hijo):" << endl;
    raiz = eliminar(raiz, "Rahua Ocllo");
    mostrarArbol(raiz);

    // Ejemplo 6: Eliminar persona con dos hijos
    cout << "\n6. Eliminar a 'Pachacutec' (con dos hijos):" << endl;
    raiz = eliminar(raiz, "Pachacutec");
    mostrarArbol(raiz);

    liberarArbol(raiz);
    return 0;
}

// Definiciones

void insertar(Persona*& raiz, Persona* nuevo) {
    if (!raiz) {
        raiz = nuevo;
    } else if (nuevo->nombre < raiz->nombre) {
        nuevo->generacion = raiz->generacion + 1;
        insertar(raiz->izquierdo, nuevo);
    } else {
        nuevo->generacion = raiz->generacion + 1;
        insertar(raiz->derecho, nuevo);
    }
}

Persona* encontrarMinimo(Persona* nodo) {
    while (nodo && nodo->izquierdo) {
        nodo = nodo->izquierdo;
    }
    return nodo;
}

Persona* eliminar(Persona* raiz, string nombre) {
    if (!raiz) return NULL;

    if (nombre < raiz->nombre) {
        raiz->izquierdo = eliminar(raiz->izquierdo, nombre);
    } else if (nombre > raiz->nombre) {
        raiz->derecho = eliminar(raiz->derecho, nombre);
    } else {
        if (!raiz->izquierdo && !raiz->derecho) {
            delete raiz;
            return NULL;
        }
        else if (!raiz->izquierdo) {
            Persona* temp = raiz->derecho;
            delete raiz;
            return temp;
        }
        else if (!raiz->derecho) {
            Persona* temp = raiz->izquierdo;
            delete raiz;
            return temp;
        }
        else {
            Persona* sucesor = encontrarMinimo(raiz->derecho);
            raiz->nombre = sucesor->nombre;
            raiz->id = sucesor->id;
            raiz->genero = sucesor->genero;
            raiz->generacion = sucesor->generacion;
            raiz->derecho = eliminar(raiz->derecho, sucesor->nombre);
        }
    }
    return raiz;
}

Persona* buscar(Persona* raiz, string nombre) {
    if (!raiz) return NULL;
    if (raiz->nombre == nombre) return raiz;
    else if (nombre < raiz->nombre)
        return buscar(raiz->izquierdo, nombre);
    else
        return buscar(raiz->derecho, nombre);
}

void inorden(Persona* raiz) {
    if (raiz) {
        inorden(raiz->izquierdo);
        cout << raiz->nombre << " (ID: " << raiz->id 
             << ", Género: " << raiz->genero 
             << ", Gen: " << raiz->generacion << ")" << endl;
        inorden(raiz->derecho);
    }
}

void mostrarArbol(Persona* raiz) {
    cout << "Contenido del árbol (inorden):" << endl;
    inorden(raiz);
}

void liberarArbol(Persona* raiz) {
    if (raiz) {
        liberarArbol(raiz->izquierdo);
        liberarArbol(raiz->derecho);
        delete raiz;
    }
}
