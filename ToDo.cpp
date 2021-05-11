#define _CRT_SECURE_NO_WARNINGS
#include "ToDo.h"


ToDo::ToDo()
	: Kolumna()
{
	strcpy(nazwa, "ToDo");
}

//										wyj¹tki try{podajZadanie()}
//										std::string temp
void ToDo::przypomnij(int _nrZadania) {
	int pozostaloDni, dzienLokalny, rokLokalny, dzienTermin, rokTermin;
	bool przestepny = false;
	time_t tempCzas, test;
	time(&tempCzas);
	tm *czasLokalny = localtime(&tempCzas);
	std::string temp;

	try {
		test = mktime(&(podajZadanie(_nrZadania).podajTermin()));//jeœli tu bêdzie dobrze to w reszcie miejsc te¿
	}
	catch (Zly_zakres& wyjatek) {
		std::cout << wyjatek.what();
		return;//wyjdŸ z metody
	}

	if (test == -1) { std::cout << '-'; }//nie ma terminu
	else if (podajZadanie(_nrZadania).podajPrzypomnienie() <= -1) { std::cout << '-'; }//nie ma przypomnienia
	else {//jest termin i jest przypomnienie
		rokTermin = podajZadanie(_nrZadania).podajTermin().tm_year + 1900;
		rokLokalny = czasLokalny->tm_year + 1900;
		dzienTermin = podajZadanie(_nrZadania).podajTermin().tm_yday;
		dzienLokalny = czasLokalny->tm_yday;
		if ( ( ((rokLokalny % 4) == 0) && ((rokLokalny % 100) != 0) ) || ((rokLokalny % 400) == 0) )
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
		if (pozostaloDni < 0)
			std::cout << "TERMIN MIN¥£!!!";
		else if(pozostaloDni == 0)
			std::cout << "Dziœ mija termin!!!";
		else {
			if (pozostaloDni > podajZadanie(_nrZadania).podajPrzypomnienie())
				std::cout << "Jeszcze jest czas...";
			else {
				temp.append("Termin minie za ");
				temp.append(std::to_string(pozostaloDni));
				if (pozostaloDni == 1)
					temp.append(" dzieñ.");
				else
					temp.append(" dni.");
				std::cout << temp;
			}
		}
	}
}