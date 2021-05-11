#pragma once
#include "ToDo.h"
#include "Doing.h"
#include "Done.h"
#include "Decyzja.h"
#include <fstream>

class Tablica
{
private:
	ToDo toDo;
	Doing doing;
	Done done;
	std::string nazwaTablicy;//50 znaków
public:
	int ustalTermin(tm& _termin, std::string& _tekst);

	void nadajNazwe(std::string& _nazwa) { nazwaTablicy = _nazwa; }
	void dodajZadanie();
	void dodajZadanie(int _nrKolumny, Zadanie& _zadanie);
	void skopiujZadanie(int _nrKolumny, int _nrZadania);
	void usunZadanie(int _nrKolumny, int _nrZadania);
	void edytujZadanie(int _nrKolumny, int _nrZadania);
	void przeniesZadanie(int _zrodloKolumna, int _nrZadania, int _celKolumna);

	int podajRozmiarKolumny(int _nrKolumny);
	std::string podajNazwe() { return nazwaTablicy; }

	void zapiszDoPliku();
	void wyswietl();
};

