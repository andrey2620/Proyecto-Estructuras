#ifndef AVL_H
#define AVL_H
#include "Sede.h"
#include <string>

class AVL {
public:
    struct Nodo {
        Sede sede;
        Nodo* izquierda;
        Nodo* derecha;
        int altura;
        Nodo(Sede s) : sede(s), izquierda(nullptr), derecha(nullptr), altura(1) {}
    };
private:
    Nodo* raiz;
    int altura(Nodo* nodo);
    int balance(Nodo* nodo);
    void actualizarAltura(Nodo* nodo);

    Nodo* rotacionDerecha(Nodo* x);
    Nodo* rotacionIzquierda(Nodo* y);

    Nodo* insertar(Nodo* nodo, Sede& sede);
    Nodo* eliminar(Nodo* nodo, const std::string& codigoIATA);
    Nodo* buscar(Nodo* nodo, const std::string& codigoIATA) const;
    Nodo* minimo(Nodo* nodo);

    bool validarSede(const Sede& sede);

    void inOrder(Nodo* nodo) const;
    void listarPorPais(Nodo* nodo, const std::string& pais) const;
    void listarPorCapacidad(Nodo* nodo, int capacidadMinima) const;
    void listarPorAnio(Nodo* nodo, int anio) const;

    void mostrarSede(const Sede& sede) const;
    void guardarRecursivo(Nodo* nodo, std::ofstream& archivo) const;

	void listarTodasLasCiudades(Nodo* nodo) const;

    friend class AVLAnio;
    friend class Grafo;

public:
    AVL();

    void insertarSede(Sede& sede);
    void eliminarSede(const std::string& codigoIATA);
    void modificar(const std::string& codigoIATA);

    void buscar(const std::string& codigoIATA) const;

    void mostrarOrdenadoPorIATA() const;
    void mostrarPorPais(const std::string& pais) const;
    void mostrarPorCapacidad(int minCapacidad) const;
    void mostrarPorAnio() const;

    void mostrarPaisesDisponibles() const;

    void recorridoGuardarCSV(std::ofstream& archivo) const;

    void mostrarTodasLasCiudades() const;
};

#endif // AVL_H