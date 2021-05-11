#include "Kolumna.h"

//										std::vector
void Kolumna::wstawZadanie(Zadanie& _zadanie) {
	zadania.push_back(_zadanie);
	sortuj();
}

//										wyj¹tki throw Zly_zakres
//										std::vector
void Kolumna::usunZadanie(int _nrZadania) {
	if (_nrZadania > zadania.size() || _nrZadania < 1) {//numeracja zadañ od 1
		Zly_zakres wyjatek(_nrZadania, zadania.size());
		throw wyjatek;
	}
	--_nrZadania;
	std::vector<Zadanie>::iterator iter = zadania.begin();
	iter += (_nrZadania);
	zadania.erase(iter);
}

//										wyj¹tki throw Zly_zakres
//										std::vector
Zadanie& Kolumna::podajZadanie(int _nrZadania) {
	if (_nrZadania > zadania.size() || _nrZadania < 1) {//numeracja zadañ od 1
		Zly_zakres wyjatek(_nrZadania, zadania.size());
		throw wyjatek;
	}
	return zadania.at(_nrZadania - 1);
}