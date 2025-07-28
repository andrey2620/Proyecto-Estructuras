#include "Menu.h"
#include "ManaCSV.h"
#include "Validaciones.h"
#include "iostream"
#include "limits"
#include "AVL.h"
#include "AVLAnio.h"
#include <string> 
#include <fstream> 

std::string leerTexto(const std::string& mensaje) {
	std::string entrada;
	std::cout << mensaje;
	std::getline(std::cin, entrada);
	return entrada;
}

int solicitarNumero(const std::string& mensaje, int minimo) {
	int valor;
	while (true) {
		std::cout << mensaje;
		std::cin >> valor;
		if (std::cin.fail() || valor < minimo) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Numero invalido. Intente nuevamente.\n";
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return valor;
		}
	}
}

Sede solicitarDatosSede() {
	std::string codigoIATA = leerTexto("Codigo IATA: ");
	std::string pais = leerTexto("Pais: ");
	std::string ciudad = leerTexto("Ciudad: ");
	std::string estadioFIFA = leerTexto("Estadio FIFA: ");
	std::string estadioOficial = leerTexto("Estadio Oficial: ");
	int capacidad = solicitarNumero("Capacidad: ", 1);
	int anio = solicitarNumero("Anio de inauguracion: ", 1800);

	return Sede(codigoIATA, pais, ciudad, estadioFIFA, estadioOficial, capacidad, anio);
}

std::string solicitarCodigoIATA() {
	return leerTexto("Ingrese el codigo IATA: ");
}


void opcionInsertar(AVL& arbol) {
	Sede sede = solicitarDatosSede();
	if (Validaciones::sedeValida(sede)) {
		arbol.insertarSede(sede);
		std::cout << "Sede insertada exitosamente.\n";
	}
	else {
		std::cout << "Datos invalidos. No se insertaron.\n";
	}
}

void opcionEliminar(AVL& arbol) {
	std::string codigo = solicitarCodigoIATA();
	arbol.eliminarSede(codigo);
}

void opcionModificar(AVL& arbol) {
	std::string codigo = solicitarCodigoIATA();
	arbol.modificar(codigo);
}

void opcionBuscar(const AVL& arbol) {
	std::string codigo = solicitarCodigoIATA();
	arbol.buscar(codigo);
}

void opcionMostrarOrdenado(const AVL& arbol) {
	arbol.mostrarOrdenadoPorIATA();
}

void opcionMostrarPorPais(const AVL& arbol) {
	arbol.mostrarPaisesDisponibles();
	std::string pais = leerTexto("Pais a buscar: ");
	arbol.mostrarPorPais(pais);
}


void opcionMostrarPorCapacidad(const AVL& arbol) {
	int min = solicitarNumero("Capacidad minima: ", 1);
	arbol.mostrarPorCapacidad(min);
}

void opcionMostrarPorAnio(const AVL& arbol) {
	AVLAnio arbolAnio;
	arbolAnio.insertarDesdeAVL(const_cast<AVL&>(arbol));
	std::cout << "\n--- Sedes ordenadas por anio de inauguracion ---\n";
	arbolAnio.mostrarOrdenadoPorAnio();
}

void opcionCalcularRutaMinima(Grafo& grafo) {
	std::string origen = solicitarCodigoIATA();
	grafo.dijkstra(origen);
}

void opcionCalcularMST(Grafo& grafo) {
	grafo.prim();
}


void AVL::modificar(const std::string& codigoIATA) {
	Nodo* nodo = buscar(raiz, codigoIATA);
	if (!nodo) {
		std::cout << "Sede no encontrada.\n";
		return;
	}

	mostrarSede(nodo->sede);

	std::string entrada;
	entrada = leerTexto("Nuevo pais (enter para no cambiar): ");
	if (!entrada.empty()) nodo->sede.pais = entrada;

	entrada = leerTexto("Nueva ciudad: ");
	if (!entrada.empty()) nodo->sede.ciudad = entrada;

	entrada = leerTexto("Nuevo estadio FIFA: ");
	if (!entrada.empty()) nodo->sede.estadioFIFA = entrada;

	entrada = leerTexto("Nuevo estadio oficial: ");
	if (!entrada.empty()) nodo->sede.estadioOficial = entrada;

	int capacidad = solicitarNumero("Nueva capacidad (0 para mantener): ");
	if (capacidad > 0) nodo->sede.capacidad = capacidad;

	int anio = solicitarNumero("Nuevo anio (0 para mantener): ");
	if (anio >= 1800) nodo->sede.ani = anio;
}

void AVL::mostrarPorPais(const std::string& pais) const {
	listarPorPais(raiz, pais);
}

void AVL::listarPorPais(Nodo* nodo, const std::string& pais) const {
	if (!nodo) return;
	listarPorPais(nodo->izquierda, pais);
	if (nodo->sede.pais == pais)
		mostrarSede(nodo->sede);
	listarPorPais(nodo->derecha, pais);
}

void AVL::mostrarPorCapacidad(int minCapacidad) const {
	listarPorCapacidad(raiz, minCapacidad);
}

void AVL::listarPorCapacidad(Nodo* nodo, int capacidadMinima) const {
	if (!nodo) return;
	listarPorCapacidad(nodo->izquierda, capacidadMinima);
	if (nodo->sede.capacidad >= capacidadMinima)
		mostrarSede(nodo->sede);
	listarPorCapacidad(nodo->derecha, capacidadMinima);
}


void AVL::mostrarPorAnio() const {

	listarPorAnio(raiz, 0);
}

void AVL::listarPorAnio(Nodo* nodo, int anioFiltro) const {
	if (!nodo) return;
	listarPorAnio(nodo->izquierda, anioFiltro);
	if (anioFiltro == 0 || nodo->sede.ani == anioFiltro)
		mostrarSede(nodo->sede);
	listarPorAnio(nodo->derecha, anioFiltro);
}

void AVL::mostrarOrdenadoPorIATA() const {
	inOrder(raiz);
}

void AVL::inOrder(Nodo* nodo) const {
	if (!nodo) return;
	inOrder(nodo->izquierda);
	mostrarSede(nodo->sede);
	inOrder(nodo->derecha);
}


bool Validaciones::sedeValida(const Sede& sede) {
	return camposTextoCompletos(sede) &&
		capacidadValida(sede.capacidad) &&
		anioValido(sede.ani);
}

bool Validaciones::camposTextoCompletos(const Sede& sede) {
	return !sede.codigoIATA.empty() && !sede.pais.empty() &&
		!sede.ciudad.empty() && !sede.estadioFIFA.empty() &&
		!sede.estadioOficial.empty();
}

bool Validaciones::capacidadValida(int capacidad) {
	return capacidad > 0;
}

bool Validaciones::anioValido(int anio) {
	return anio >= 1800 && anio <= 2026;
}



void mostrarMenuPrincipal(AVL& arbol, Grafo& grafo) {
	int opcion;
	do {
		std::cout << "\n--- Menu Mundial FIFA 2026 ---\n";
		std::cout << "1. Insertar sede\n";
		std::cout << "2. Eliminar sede\n";
		std::cout << "3. Modificar sede\n";
		std::cout << "4. Buscar sede\n";
		std::cout << "5. Mostrar sedes ordenadas por IATA\n";
		std::cout << "6. Mostrar sedes por pais\n";
		std::cout << "7. Mostrar sedes por capacidad\n";
		std::cout << "8. Mostrar sedes por anio de inauguracion\n";
		std::cout << "9. Calcular ruta mas corta entre sedes\n";
		std::cout << "10. Generar red de transporte minima\n";
		std::cout << "0. Salir\n";
		std::cout << "Seleccione una opcion: ";
		std::cin >> opcion;
		std::cin.ignore();

		switch (opcion) {
		case 1: opcionInsertar(arbol); break;
		case 2: opcionEliminar(arbol); break;
		case 3: opcionModificar(arbol); break;
		case 4: opcionBuscar(arbol); break;
		case 5: opcionMostrarOrdenado(arbol); break;
		case 6: opcionMostrarPorPais(arbol); break;
		case 7: opcionMostrarPorCapacidad(arbol); break;
		case 8: opcionMostrarPorAnio(arbol); break;
		case 9: opcionCalcularRutaMinima(grafo); break;
		case 10: opcionCalcularMST(grafo); break;
		case 0: std::cout << "Hasta pronto!\n"; break;
		default: std::cout << "Opcion invalida.\n";
		}
	} while (opcion != 0);
}

