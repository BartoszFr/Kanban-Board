#define _CRT_SECURE_NO_WARNINGS
#include "Done.h"

Done::Done()
	: Kolumna()
{
	strcpy(nazwa, "Done");
}
//										wyj¹tki try{podajZadanie()}
//										std::string temp
void Done::ilePrzedCzasem(int _nrZadania) {
	int pozostaloDni, dzienLokalny, rokLokalny, dzienTermin, rokTermin;
	bool przestepny = false;
	time_t tempCzas, test;
	time(&tempCzas);
	tm* czasLokalny = localtime(&tempCzas);
	std::string temp;

	try {
		test = mktime(&(podajZadanie(_nrZadania).podajTermin()));
	}
	catch (Zly_zakres& wyjatek) {
		std::cout << wyjatek.what();
		return;//wyjdŸ z metody
	}

	if (test == -1) { std::cout << '-'; }//nie ma terminu
	else if (podajZadanie(_nrZadania).podajPrzypomnienie() == -1) { std::cout << '-'; }//nie ma przypomnienia
	else {//jest termin i jest przypomnienie
		rokTermin = podajZadanie(_nrZadania).podajTermin().tm_year + 1900;
		rokLokalny = czasLokalny->tm_year + 1900;
		dzienTermin = podajZadanie(_nrZadania).podajTermin().tm_yday;
		dzienLokalny = czasLokalny->tm_yday;
		if ((((rokLokalny % 4) == 0) && ((rokLokalny % 100) != 0)) || ((rokLokalny % 400) == 0))
			przestepny = true;
		if ((rokTermin - rokLokalny) != 0) {//termin przypada w nastêpnym roku
			if (przestepny)//rok przestepny
				pozostaloDni = 366 - dzienLokalny + dzienTermin;
			else//rok zwyk³y
				pozostaloDni = 365 - dzienLokalny + dzienTermin;
		}
		else {//termin w tym samym roku
			pozostaloDni = dzienTermin - dzienLokalny;
		}
		if (pozostaloDni < 0) {
			temp = "Zakoñczono ";
			temp.append(std::to_string((int)fabs(pozostaloDni)));
			if (pozostaloDni == -1)
				temp.append(" dzieñ po terminie :(");
			else
				temp.append(" dni po terminie :(");
			std::cout <<  temp;
			temp.clear();
		}
		else if (pozostaloDni == 0)
			std::cout << "Zakoñczono na czas.";
		else {
			if (pozostaloDni > podajZadanie(_nrZadania).podajPrzypomnienie()) {
				temp = "Zakoñczono ";
				temp.append(std::to_string((int)fabs(pozostaloDni)));
				if (pozostaloDni == 1)
					temp.append(" dzieñ przed terminem :)");
				else
					temp.append(" dni przed terminem :)");
				std::cout << temp;
			}
		}
	}
}
