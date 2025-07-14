#ifndef SEDE_H
#define SEDE_H

#include <string>

/*
 * Este documento define la estructura de la sede, y la infromacion acerda de la localizacion
*/
struct Sede
{
	std::string codigoIATA;
	std::string pais;
	std::string ciudad;
	std::string estadioFIFA;
	std::string estadioOficial;
	int capacidad;
	int ani;

	Sede(std::string iata, std::string p, std::string c, std::string estadioFIFA, std::string estadioOficial, int capacidad, int ani)
		: codigoIATA(iata), pais(p), ciudad(c), estadioFIFA(estadioFIFA), estadioOficial(estadioOficial), capacidad(capacidad), ani(ani) {
	}

	Sede() : capacidad(0), ani(0) {}
};

#endif 