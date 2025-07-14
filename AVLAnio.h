#ifndef AVL_ANIO_H
#define AVL_ANIO_H
#include "Sede.h"
#include <string>

class AVLAnio {
private:
    struct Nodo {
        Sede sede;
        Nodo* izquierda;
        Nodo* derecha;
        int altura;
        Nodo(Sede s) : sede(s), izquierda(nullptr), derecha(nullptr), altura(1) {}
    };
    Nodo* raiz;

    int altura(Nodo* nodo);
    int balance(Nodo* nodo);
    void actualizarAltura(Nodo* nodo);

    Nodo* rotacionDerecha(Nodo* y);
    Nodo* rotacionIzquierda(Nodo* x);

    Nodo* insertar(Nodo* nodo, Sede& sede);
    void inOrder(Nodo* nodo) const;
    void mostrarSede(const Sede& s) const;

public:
    AVLAnio();
    void insertarSede(Sede& sede);
    void mostrarOrdenadoPorAnio() const;
    void insertarDesdeAVL(class AVL& arbolOriginal);
};

#endif
