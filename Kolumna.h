#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include "Zadanie.h"
#include "Zly_zakres.h"

class Kolumna
{
protected:
	std::vector<Zadanie> zadania;
	char nazwa[6];
public:
	void wstawZadanie(Zadanie& _zadanie);
	void usunZadanie(int _nrZadania);
//										std::sort()
	void sortuj() { std::sort(zadania.begin(), zadania.end()); }

	Zadanie& podajZadanie(int _nrZadania);
	char* podajNazwe() { return nazwa; }
	int podajRozmiar() { return zadania.size(); }
};
