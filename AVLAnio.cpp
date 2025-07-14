#include "AVLAnio.h"
#include "AVL.h"
#include <iostream>
#include <algorithm>

AVLAnio::AVLAnio() : raiz(nullptr) {}

int AVLAnio::altura(Nodo* nodo) { return nodo ? nodo->altura : 0; }
int AVLAnio::balance(Nodo* nodo) { return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0; }
void AVLAnio::actualizarAltura(Nodo* nodo) {
    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
}

AVLAnio::Nodo* AVLAnio::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;
    x->derecha = y;
    y->izquierda = T2;
    actualizarAltura(y);
    actualizarAltura(x);
    return x;
}

AVLAnio::Nodo* AVLAnio::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;
    y->izquierda = x;
    x->derecha = T2;
    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}

AVLAnio::Nodo* AVLAnio::insertar(Nodo* nodo, Sede& sede) {
    if (!nodo) return new Nodo(sede);
    if (sede.ani < nodo->sede.ani)
        nodo->izquierda = insertar(nodo->izquierda, sede);
    else if (sede.ani > nodo->sede.ani)
        nodo->derecha = insertar(nodo->derecha, sede);
    else 
        nodo->derecha = insertar(nodo->derecha, sede);
    actualizarAltura(nodo);
    int bf = balance(nodo);
    if (bf > 1 && sede.ani < nodo->izquierda->sede.ani)
        return rotacionDerecha(nodo);
    if (bf < -1 && sede.ani > nodo->derecha->sede.ani)
        return rotacionIzquierda(nodo);
    if (bf > 1 && sede.ani > nodo->izquierda->sede.ani) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (bf < -1 && sede.ani < nodo->derecha->sede.ani) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }
    return nodo;
}

void AVLAnio::insertarSede(Sede& sede) {
    raiz = insertar(raiz, sede);
}

void AVLAnio::mostrarSede(const Sede& s) const {
    std::cout << "\nCódigo IATA: " << s.codigoIATA
        << "\nPaís: " << s.pais
        << "\nCiudad: " << s.ciudad
        << "\nEstadio FIFA: " << s.estadioFIFA
        << "\nEstadio Oficial: " << s.estadioOficial
        << "\nCapacidad: " << s.capacidad
        << "\nAño de inauguración: " << s.ani << "\n";
}

void AVLAnio::inOrder(Nodo* nodo) const {
    if (!nodo) return;
    inOrder(nodo->izquierda);
    mostrarSede(nodo->sede);
    inOrder(nodo->derecha);
}

void AVLAnio::mostrarOrdenadoPorAnio() const {
    inOrder(raiz);
}

void insertarRecursivoPorAnio(AVL::Nodo* nodoOriginal, AVLAnio& arbolAnio) {
    if (!nodoOriginal) return;
    insertarRecursivoPorAnio(nodoOriginal->izquierda, arbolAnio);
    arbolAnio.insertarSede(nodoOriginal->sede);
    insertarRecursivoPorAnio(nodoOriginal->derecha, arbolAnio);
}

void AVLAnio::insertarDesdeAVL(AVL& arbolOriginal) {
    insertarRecursivoPorAnio(arbolOriginal.raiz, *this);
}
