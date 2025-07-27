#ifndef GRAFO_H
#define GRAFO_H

#include "Sede.h"
#include "AVL.h" 
#include <string>

const int MAX_SEDES = 16;

class Grafo {
private:
    Sede vertices[MAX_SEDES];
    int matrizAdyacencia[MAX_SEDES][MAX_SEDES];
    int numVertices;

    int obtenerIndice(const std::string& codigoIATA);

public:
    Grafo();
    void agregarVertice(const Sede& sede);
    void agregarArista(const std::string& origenIATA, const std::string& destinoIATA, int peso);
    void inicializarDesdeAVL(AVL& arbol);

    void dijkstra(const std::string& origenIATA);
    void prim();
};

#endif 