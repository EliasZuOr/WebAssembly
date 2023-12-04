#include <iostream>
#include <emscripten.h>

using namespace std;

int N;

class Nodo {
public:
    Nodo* izq;
    int info;
    Nodo* der;
};

class DLL {
private:
    Nodo* inicio;
    Nodo* fin;

public:
    DLL();
    void agregar(int valor);
    void mostrarInicioFin();
    void mostrarFinInicio();
    void mostrarInicio();
    void mostrarFin();
    void borrarValor(int valor);
    void ordenar();
    void resultado();
    EMSCRIPTEN_KEEPALIVE
    int cotizar(int dias, int personas);
};

DLL lista;

DLL::DLL() : inicio(NULL), fin(NULL) {}

void DLL::agregar(int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->info = valor;
    if (inicio == NULL) {
        inicio = nuevo;
        fin = nuevo;
        nuevo->izq = NULL;
        nuevo->der = NULL;
    } else {
        nuevo->izq = fin;
        fin->der = nuevo;
        fin = fin->der;
        fin->der = NULL;
    }
}


void DLL::mostrarInicioFin() {
    Nodo* reco = inicio;
    while (reco != NULL) {
        cout << reco->info << endl;
        reco = reco->der;
    }
}

void DLL::mostrarFinInicio() {
    Nodo* reco = fin;
    while (reco != NULL) {
        cout << reco->info << endl;
        reco = reco->izq;
    }
}

void DLL::mostrarInicio() {
    cout << "Primer elemento: " << inicio->info << endl;
}

void DLL::mostrarFin() {
    cout << "Ultimo elemento: " << fin->info << endl;
}

void DLL::borrarValor(int valor) {
    if (inicio == NULL) {
        cout << "No se puede borrar el elemento " << valor << " porque la lista esta vacia" << endl;
    } else if (inicio->info == valor) {
        Nodo* borrarInicio = inicio;
        inicio = inicio->der;
        if (inicio != NULL) {
            inicio->izq = NULL;
        }
        delete borrarInicio;
    } else if (fin->info == valor) {
        Nodo* borrarFin = fin;
        fin = fin->izq;
        if (fin != NULL) {
            fin->der = NULL;
        }
        delete borrarFin;
    } else {
        Nodo* reco = inicio->der;
        while (reco != NULL) {
            if (reco->info == valor) {
                Nodo* anterior = reco->izq;
                Nodo* siguiente = reco->der;
                anterior->der = siguiente;
                if (siguiente != NULL) {
                    siguiente->izq = anterior;
                }
                delete reco;
                break;
            }
            reco = reco->der;
        }
    }
}

extern "C" {
EMSCRIPTEN_KEEPALIVE
int cotizar(int dias, int personas){
  N = dias * personas * 250;
  lista.agregar(N);
  return N;
};
  }

// Función para obtener el nodo medio de la lista
Nodo* obtenerMedio(Nodo* inicio, Nodo* fin) {
    if (!inicio)
        return nullptr;

    Nodo* lento = inicio;
    Nodo* rapido = inicio->der;

    while (rapido && rapido->der) {
        lento = lento->der;
        rapido = rapido->der->der;
    }

    return lento;
}

// Función para realizar la fusión de dos sublistas ordenadas
Nodo* fusionar(Nodo* izquierda, Nodo* derecha) {
    Nodo* resultado = nullptr;

    if (!izquierda)
        return derecha;
    if (!derecha)
        return izquierda;

    if (izquierda->info <= derecha->info) {
        resultado = izquierda;
        resultado->der = fusionar(izquierda->der, derecha);
        if (resultado->der)
            resultado->der->izq = resultado;
    } else {
        resultado = derecha;
        resultado->der = fusionar(izquierda, derecha->der);
        if (resultado->der)
            resultado->der->izq = resultado;
    }

    return resultado;
}

// Función principal de Merge Sort
Nodo* mergeSort(Nodo* inicio, Nodo* fin) {
    if (inicio == fin || !inicio)
        return inicio;

    Nodo* medio = obtenerMedio(inicio, fin);
    Nodo* siguienteDeMedio = medio->der;

    medio->izq = nullptr;
    medio->der = nullptr;

    Nodo* izquierda = mergeSort(inicio, medio);
    Nodo* derecha = mergeSort(siguienteDeMedio, fin);

    return fusionar(izquierda, derecha);
}

// Función para ordenar la lista usando Merge Sort
void ordenar() {
  Nodo* inicio;
  Nodo* fin;
  
    inicio = mergeSort(inicio, fin);
    Nodo* actual = inicio;
    while (actual->der) {
        actual = actual->der;
    }
    fin = actual;
}

void DLL::resultado() {
    Nodo* actual = inicio;
    while (actual != nullptr) {
        cout << actual->info << " ";
        actual = actual->der;
    }
    cout << endl;
}

  int main() {

    cout << "Lista antes de ordenar:" << endl;
      lista.mostrarInicioFin();

      // Llamada a cotizar que agrega elementos y ordena la lista
      lista.cotizar(2, 3);

      cout << "Lista después de ordenar:" << endl;
      lista.mostrarInicioFin();

      return 0;
  };
