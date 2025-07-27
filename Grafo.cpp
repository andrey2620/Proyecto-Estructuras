#include "Grafo.h"
#include <iostream>

const int MAX_INT = 2147483647;

Grafo::Grafo() : numVertices(0) {
    for (int i = 0; i < MAX_SEDES; ++i) {
        for (int j = 0; j < MAX_SEDES; ++j) {
            matrizAdyacencia[i][j] = (i == j) ? 0 : -1;
        }
    }
}

int Grafo::obtenerIndice(const std::string& codigoIATA) {
    for (int i = 0; i < numVertices; ++i) {
        if (vertices[i].codigoIATA == codigoIATA) {
            return i;
        }
    }
    return -1;
}

void Grafo::agregarVertice(const Sede& sede) {
    if (numVertices < MAX_SEDES) {
        if (obtenerIndice(sede.codigoIATA) == -1) {
            vertices[numVertices++] = sede;
        }
    }
}

void Grafo::agregarArista(const std::string& origenIATA, const std::string& destinoIATA, int peso) {
    int indiceOrigen = obtenerIndice(origenIATA);
    int indiceDestino = obtenerIndice(destinoIATA);

    if (indiceOrigen != -1 && indiceDestino != -1) {
        matrizAdyacencia[indiceOrigen][indiceDestino] = peso;
        matrizAdyacencia[indiceDestino][indiceOrigen] = peso;
    }
}

void inicializarGrafoRecursivo(AVL::Nodo* nodo, Grafo* grafo) {
  if (!nodo) return;
  grafo->agregarVertice(nodo->sede);
  inicializarGrafoRecursivo(nodo->izquierda, grafo);
  inicializarGrafoRecursivo(nodo->derecha, grafo);
}

void Grafo::inicializarDesdeAVL(AVL& arbol) {
    inicializarGrafoRecursivo(arbol.raiz, this);
}

// Lo ideal sería utilizar algún tipo de cola de prioridad o heap para optimizar este algoritmo.
// Para efectos del curso y teniendo en cuenta la restricción de no usar estructuras externas, se implementará 
// con un ciclo anidado, resultando en una complejidad de O(V^2), que para 16 ciudades no representa un problema 
// de rendimiento debido a la pequeña cantidad de operaciones (16 * 16 = 256).
void Grafo::dijkstra(const std::string& origenIATA) {
    int origenIndex = obtenerIndice(origenIATA);
    if (origenIndex == -1) {
        std::cout << "La sede de origen no existe." << std::endl;
        return;
    }

    int dist[MAX_SEDES];
    bool visitado[MAX_SEDES];
    int previo[MAX_SEDES];

    for (int i = 0; i < numVertices; ++i) {
        dist[i] = MAX_INT;
        visitado[i] = false;
        previo[i] = -1;
    }
    dist[origenIndex] = 0;

    for (int i = 0; i < numVertices - 1; ++i) {
        int u = -1;
        for (int j = 0; j < numVertices; ++j) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }
        if (dist[u] == MAX_INT) break;
        visitado[u] = true;

        for (int v = 0; v < numVertices; ++v) {
            if (matrizAdyacencia[u][v] != -1 && !visitado[v] && dist[u] + matrizAdyacencia[u][v] < dist[v]) {
                dist[v] = dist[u] + matrizAdyacencia[u][v];
                previo[v] = u;
            }
        }
    }

    std::cout << "Distancias mas cortas desde " << origenIATA << ":" << std::endl;
    for (int i = 0; i < numVertices; ++i) {
        if (i != origenIndex) {
            if (dist[i] == MAX_INT) {
                std::cout << "Hacia " << vertices[i].codigoIATA << ": No hay ruta disponible." << std::endl;
            }
            else {
                std::cout << "Hacia " << vertices[i].codigoIATA << ": " << dist[i] << " km. Ruta: ";
                int actual = i;
                std::string ruta = "";
                while (actual != -1) {
                    ruta = vertices[actual].codigoIATA + " " + ruta;
                    actual = previo[actual];
                    if (actual != -1) ruta = "<- " + ruta;
                }
                std::cout << ruta << std::endl;
            }
        }
    }
}

// Lo ideal sería utilizar algún tipo de cola de prioridad o heap para optimizar este algoritmo.
// Para efectos del curso y teniendo en cuenta la restricción de no usar estructuras externas, se implementará 
// con un ciclo anidado, resultando en una complejidad de O(V^2), que para 16 ciudades no representa un problema 
// de rendimiento debido a la pequeña cantidad de operaciones (16 * 16 = 256).
void Grafo::prim() {
    int padre[MAX_SEDES];
    int pesos[MAX_SEDES];
    bool enMST[MAX_SEDES];
    for (int i = 0; i < numVertices; i++) {
        pesos[i] = MAX_INT;
        enMST[i] = false;
        padre[i] = -1;
    }
    pesos[0] = 0;
    int total = 0;

    for (int count = 0; count < numVertices - 1; count++) {
        int u = -1;
        for (int v = 0; v < numVertices; v++)
            if (!enMST[v] && (u == -1 || pesos[v] < pesos[u]))
                u = v;
        enMST[u] = true;

        for (int v = 0; v < numVertices; v++)
            if (matrizAdyacencia[u][v] != -1 && !enMST[v] && matrizAdyacencia[u][v] < pesos[v])
                padre[v] = u, pesos[v] = matrizAdyacencia[u][v];
    }

    std::cout << "Arbol de Expansion Minima (Prim):" << std::endl;
    for (int i = 1; i < numVertices; i++) {
        if (padre[i] != -1) {
            std::cout << vertices[padre[i]].codigoIATA << " - " << vertices[i].codigoIATA << " \t" << matrizAdyacencia[i][padre[i]] << " km" << std::endl;
            total += matrizAdyacencia[i][padre[i]];
        }
    }
    std::cout << "Costo total del Arbol de Expansion Minima: " << total << " km" << std::endl;
} 