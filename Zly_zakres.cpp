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
		temp << "Brak element�w. Zarz�dano: " << numer << ".";
	else if (numer < 1)
		temp << "Z�y zakres. Elementy numerowane s� od 1. Zarz�dano: " << numer << ".";
	else
		temp << "Z�y zakres. Zarz�dano: " << numer << ". Dost�pnych jest: " << zakres << ".";
	tekst = temp.str();
}

const char* Zly_zakres::what() const noexcept {
	return tekst.c_str();
}
