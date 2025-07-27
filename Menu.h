#pragma once
#ifndef MENU_H
#define MENU_H

#include "AVL.h"
#include "Grafo.h"
#include <string>

// Función principal del menú interactivo
void mostrarMenuPrincipal(AVL& arbol, Grafo& grafo);

// Opciones específicas del menú  
void opcionInsertar(AVL& arbol);
void opcionEliminar(AVL& arbol);
void opcionModificar(AVL& arbol);
void opcionBuscar(const AVL& arbol);
void opcionMostrarOrdenado(const AVL& arbol);
void opcionMostrarPorPais(const AVL& arbol);
void opcionMostrarPorCapacidad(const AVL& arbol);
void opcionMostrarPorAnio(const AVL& arbol);
void opcionCalcularRutaMinima(Grafo& grafo);
void opcionCalcularMST(Grafo& grafo);


// Utilidades de ingreso
Sede solicitarDatosSede();
std::string solicitarCodigoIATA();
int solicitarNumero(const std::string& mensaje, int minimo = 0);

#endif
