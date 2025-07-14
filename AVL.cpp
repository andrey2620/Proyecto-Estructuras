#include "AVL.h"
#include <iostream>
#include <algorithm>
#include <fstream>

AVL::AVL() : raiz(nullptr) {}

int AVL::altura(Nodo* nodo) {
    return nodo ? nodo->altura : 0;
}

int AVL::balance(Nodo* nodo) {
    return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0;
}

void AVL::actualizarAltura(Nodo* nodo) {
    nodo->altura = 1 + std::max(altura(nodo->izquierda), altura(nodo->derecha));
}


AVL::Nodo* AVL::rotacionDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    Nodo* T2 = x->derecha;

    x->derecha = y;
    y->izquierda = T2;

    actualizarAltura(y);
    actualizarAltura(x);

    return x;
}

AVL::Nodo* AVL::rotacionIzquierda(Nodo* x) {
    Nodo* y = x->derecha;
    Nodo* T2 = y->izquierda;

    y->izquierda = x;
    x->derecha = T2;

    actualizarAltura(x);
    actualizarAltura(y);

    return y;
}
AVL::Nodo* AVL::insertar(Nodo* nodo, Sede& sede) {
    if (!nodo) return new Nodo(sede);
    if (sede.codigoIATA < nodo->sede.codigoIATA)
        nodo->izquierda = insertar(nodo->izquierda, sede);
    else if (sede.codigoIATA > nodo->sede.codigoIATA)
        nodo->derecha = insertar(nodo->derecha, sede);
    else return nodo;
    actualizarAltura(nodo);
    int bf = balance(nodo);
    if (bf > 1 && sede.codigoIATA < nodo->izquierda->sede.codigoIATA)
        return rotacionDerecha(nodo);
    if (bf < -1 && sede.codigoIATA > nodo->derecha->sede.codigoIATA)
        return rotacionIzquierda(nodo);
    if (bf > 1 && sede.codigoIATA > nodo->izquierda->sede.codigoIATA) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (bf < -1 && sede.codigoIATA < nodo->derecha->sede.codigoIATA) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }
    return nodo;
}

void AVL::insertarSede(Sede& sede) {
    raiz = insertar(raiz, sede);
}


AVL::Nodo* AVL::minimo(Nodo* nodo) {
    while (nodo->izquierda)
        nodo = nodo->izquierda;
    return nodo;
}

AVL::Nodo* AVL::eliminar(Nodo* nodo, const std::string& codigoIATA) {
    if (!nodo) return nullptr;

    if (codigoIATA < nodo->sede.codigoIATA)
        nodo->izquierda = eliminar(nodo->izquierda, codigoIATA);
    else if (codigoIATA > nodo->sede.codigoIATA)
        nodo->derecha = eliminar(nodo->derecha, codigoIATA);
    else {
        if (!nodo->izquierda || !nodo->derecha) {
            Nodo* temp = nodo->izquierda ? nodo->izquierda : nodo->derecha;
            delete nodo;
            return temp;
        }
        else {
            Nodo* sucesor = minimo(nodo->derecha);
            nodo->sede = sucesor->sede;
            nodo->derecha = eliminar(nodo->derecha, sucesor->sede.codigoIATA);
        }
    }

    actualizarAltura(nodo);
    int bf = balance(nodo);

    if (bf > 1 && balance(nodo->izquierda) >= 0)
        return rotacionDerecha(nodo);
    if (bf > 1 && balance(nodo->izquierda) < 0) {
        nodo->izquierda = rotacionIzquierda(nodo->izquierda);
        return rotacionDerecha(nodo);
    }
    if (bf < -1 && balance(nodo->derecha) <= 0)
        return rotacionIzquierda(nodo);
    if (bf < -1 && balance(nodo->derecha) > 0) {
        nodo->derecha = rotacionDerecha(nodo->derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

void AVL::eliminarSede(const std::string& codigoIATA) {
    raiz = eliminar(raiz, codigoIATA);
}

AVL::Nodo* AVL::buscar(Nodo* nodo, const std::string& codigoIATA) const {
    if (!nodo) return nullptr;
    if (codigoIATA == nodo->sede.codigoIATA)
        return nodo;
    if (codigoIATA < nodo->sede.codigoIATA)
        return buscar(nodo->izquierda, codigoIATA);
    else
        return buscar(nodo->derecha, codigoIATA);
}

void AVL::buscar(const std::string& codigoIATA) const {
    Nodo* nodo = buscar(raiz, codigoIATA);
    if (nodo)
        mostrarSede(nodo->sede);
    else
        std::cout << "Sede no encontrada.\n";
}


void AVL::guardarRecursivo(Nodo* nodo, std::ofstream& archivo) const {
    if (!nodo) return;
    guardarRecursivo(nodo->izquierda, archivo);
    const Sede& s = nodo->sede;
    archivo << s.codigoIATA << "," << s.pais << "," << s.ciudad << ","
        << s.estadioFIFA << "," << s.estadioOficial << ","
        << s.capacidad << "," << s.ani << "\n";
    guardarRecursivo(nodo->derecha, archivo);
}

void AVL::recorridoGuardarCSV(std::ofstream& archivo) const {
    guardarRecursivo(raiz, archivo);
}

void AVL::mostrarSede(const Sede& s) const {
    std::cout << "\nCódigo IATA: " << s.codigoIATA
        << "\nPaís: " << s.pais
        << "\nCiudad: " << s.ciudad
        << "\nEstadio FIFA: " << s.estadioFIFA
        << "\nEstadio Oficial: " << s.estadioOficial
        << "\nCapacidad: " << s.capacidad
        << "\nAño de inauguración: " << s.ani << "\n";
}