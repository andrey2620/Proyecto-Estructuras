#include "ManaCSV.h"
#include "AVL.h"
#include <fstream>
#include <sstream>
#include <iostream>

void ManaCSV::cargarSedes(AVL& arbol, const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return;
    }

    std::string linea;
    std::getline(archivo, linea); // Leer encabezado y descartarlo

    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string campo;
        Sede sede;

        std::getline(ss, campo, ','); sede.codigoIATA = campo;
        std::getline(ss, campo, ','); sede.pais = campo;
        std::getline(ss, campo, ','); sede.ciudad = campo;
        std::getline(ss, campo, ','); sede.estadioFIFA = campo;
        std::getline(ss, campo, ','); sede.estadioOficial = campo;
        std::getline(ss, campo, ','); sede.capacidad = std::stoi(campo);
        std::getline(ss, campo, ','); sede.ani = std::stoi(campo);

        arbol.insertarSede(sede);
    }

    archivo.close();
}

void ManaCSV::guardarSedes(const AVL& arbol, const std::string& rutaArchivo) {
    std::ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir para escritura: " << rutaArchivo << std::endl;
        return;
    }

    archivo << "codigoIATA,pais,ciudad,estadioFIFA,estadioOficial,capacidad,anio\n";

    arbol.recorridoGuardarCSV(archivo);

    archivo.close();
}
