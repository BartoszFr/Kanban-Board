#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <ctime>
#include <exception>
#include <algorithm>
class Zadanie
{
private:
	std::string nazwa;//max 40 znaków
	std::string opis;//max 200 znaków
	tm termin;
	char* terminTekst;//max 40 znaków
	int przypomnienie;//max 31
public:
	Zadanie();
	~Zadanie();
	Zadanie(const Zadanie& _prawy);

	Zadanie& operator=(const Zadanie& _prawy);
	bool operator<(Zadanie& _prawy);
	
	void nadajNazwe(std::string& _nazwa) { nazwa = _nazwa; }
	void nadajOpis(std::string& _opis) { opis = _opis; }
	void ustawPrzypomnienie(int& _przypomnienie) { przypomnienie = _przypomnienie; }/*weryfikacja wartoœci
																					przed wywo³aniem funkcji*/
	void nadajTermin(tm& _termin);

	std::string podajNazwe() { return nazwa; }
	std::string podajOpis() { return opis; }
	tm podajTermin() { return termin; }
	int podajPrzypomnienie() { return przypomnienie; }
	char* podajTerminTekst() { return terminTekst; }

	void wyswietl();
};

