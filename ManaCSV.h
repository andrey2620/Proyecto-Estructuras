#ifndef MANACSV_H
#endif MANACSV_
#include <string>

class AVL;

class ManaCSV {

public:
    static void cargarSedes(AVL& arbol, const std::string& rutaArchivo);
    static void guardarSedes(const AVL& arbol, const std::string& rutaArchivo);
};