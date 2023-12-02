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
        cout << "No se puede borrar el elemento " << valor << " porque la lista est� vac�a" << endl;
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

int main() {
  
  return 0;
};
