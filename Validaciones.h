#include "Sede.h"
#include <string>

class Validaciones {
public:
	static bool camposTextoCompletos(const Sede& sede);
	static bool capacidadValida(int capacidad);
	static bool anioValido(int ani);
	static bool sedeValida(const Sede& sede);
};