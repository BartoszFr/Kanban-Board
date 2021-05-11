#include "Zly_zakres.h"
#include <iostream>
#include <cstring>
#include <sstream>

//										std::ostringstream temp
Zly_zakres::Zly_zakres(int _numer, int _zakres)
	: exception()
	, numer(_numer)
	, zakres(_zakres)
{
	std::ostringstream temp;
	if (_zakres == 0)
		temp << "Brak elementów. Zarz¹dano: " << numer << ".";
	else if (numer < 1)
		temp << "Z³y zakres. Elementy numerowane s¹ od 1. Zarz¹dano: " << numer << ".";
	else
		temp << "Z³y zakres. Zarz¹dano: " << numer << ". Dostêpnych jest: " << zakres << ".";
	tekst = temp.str();
}

const char* Zly_zakres::what() const noexcept {
	return tekst.c_str();
}
