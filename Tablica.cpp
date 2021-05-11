#define _CRT_SECURE_NO_WARNINGS
#include "Tablica.h"

//										std::stringstream str
int Tablica::ustalTermin(tm& _termin, std::string& _tekst) {
	int liczba, i, j, k, dni, rok, tydzien;
	std::stringstream str;
	char c;
	bool przestepny = false;

	if (_tekst.find("-1") != std::string::npos) {//brak terminu
		_termin = { -1, -1, -1, -1, -1, -1, -1, -1, -1, };
		return 0;
	}

	if (_tekst.find("Brak terminu.") != std::string::npos) {//brak terminu - odczyt z pliku
		_termin = { -1, -1, -1, -1, -1, -1, -1, -1, -1, };
		return 0;
	}

	str << _tekst;
	str >> _termin.tm_mday;
	if (str.fail()) {
		std::cout << "B³êdne dane." << std::endl;
		return 1;
	}

	do {//pozbycie siê ewentualnych wtr¹ceñ przed kropk¹
		str.get(c);
	} while (c == ' ' || c == '\t');
	str >> liczba;
	if (str.fail()) {
		std::cout << "B³êdne dane." << std::endl;
		return 1;
	}
	_termin.tm_mon = liczba - 1;

	do {//pozbycie siê ewentualnych wtr¹ceñ przed kropk¹
		str.get(c);
	} while (c == ' ' || c == '\t');
	str >> liczba;
	if (str.fail()) {
		std::cout << "B³êdne dane." << std::endl;
		return 1;
	}
	if (liczba <= 99)//skrócony zapis roku
		liczba = 100 + liczba;
	else
		liczba -= 1900;
	_termin.tm_year = liczba;

	//kontrola roku miesi¹ca i dnia
	if (_termin.tm_year < 0) {
		std::cout << "B³êdnie podany rok. Niedozwolona jest data sprzed 1900 roku." << std::endl;
		return 1;
	}

// na podstawie http://www.algorytm.org/przetwarzanie-dat/wyznaczanie-lat-przestepnych.html
	rok = _termin.tm_year + 1900;//poprawnie podany rok
	if ((((rok % 4) == 0) && ((rok % 100) != 0)) || ((rok % 400) == 0))
		przestepny = true;

	if (_termin.tm_mon < 0 || _termin.tm_mon > 11) {
		std::cout << "B³êdnie podany miesi¹c." << std::endl;
		return 1;
	}

	if (_termin.tm_mday < 1) {
		std::cout << "B³êdnie podany dzieñ miesi¹ca (za ma³o)." << std::endl;
		return 1;
	}
	if (_termin.tm_mday > 29 && _termin.tm_mon == 1 && przestepny == true) {
		std::cout << "B³êdnie podany dzieñ miesi¹ca. W roku przestêpnym luty ma 29 dni." << std::endl;
		return 1;
	}
	if (_termin.tm_mday > 28 && _termin.tm_mon == 1 && przestepny == false) {
		std::cout << "B³êdnie podany dzieñ miesi¹ca. Luty w roku nieprzestêpnym ma 28 dni." << std::endl;
		return 1;
	}
	if (_termin.tm_mday > 31 && (_termin.tm_mon == 0 || _termin.tm_mon == 2 || _termin.tm_mon == 4\
		|| _termin.tm_mon == 6 || _termin.tm_mon == 7 || _termin.tm_mon == 9 || _termin.tm_mon == 11)) {
		std::cout << "B³êdnie podany dzieñ miesi¹ca (za du¿o)." << std::endl;
		return 1;
	}
	if (_termin.tm_mday > 31 && (_termin.tm_mon == 1 || _termin.tm_mon == 3 || _termin.tm_mon == 5\
		|| _termin.tm_mon == 8 || _termin.tm_mon == 10)) {
		std::cout << "B³êdnie podany dzieñ miesi¹ca (za du¿o)." << std::endl;
		return 1;
	}
	//koniec kontroli roku, miesi¹ca i dnia

	str >> _termin.tm_hour;
	if (str.fail()) {
		std::cout << "B³êdne dane." << std::endl;
		return 1;
	}
	if (_termin.tm_hour < 0 || _termin.tm_hour > 23) {
		std::cout << "B³êdnie podana godzina." << std::endl;
		return 1;
	}

	do {//pozbycie siê ewentualnych wtr¹ceñ przed dwukropkiem
		str.get(c);
	} while (c == ' ' || c == '\t');
	str >> _termin.tm_min;
	if (str.fail()) {
		std::cout << "B³êdne dane." << std::endl;
		return 1;
	}
	if (_termin.tm_min < 0 || _termin.tm_min > 59) {
		std::cout << "B³êdnie podana minuta." << std::endl;
		return 1;
	}

	do {//pozbycie siê ewentualnych wtr¹ceñ przed dwukropkiem
		str.get(c);
	} while (c == ' ' || c == '\t');
	str >> _termin.tm_sec;
	if (str.fail()) {
		std::cout << "B³êdne dane." << std::endl;
		return 1;
	}
	if (_termin.tm_sec < 0 || _termin.tm_sec > 60) {
		std::cout << "B³êdnie podana sekunda." << std::endl;
		return 1;
	}

	_termin.tm_isdst = 1;

	i = 0;
	dni = 0;
	if (_termin.tm_mon == 0)//styczeñ
		_termin.tm_yday = _termin.tm_mday - 1;
	else {
		do {
			k = i % 2;//parzyste miesi¹ce 31 (numerowane od zera)
			dni += (31 - k);
			++i;
		} while (i < _termin.tm_mon && i < 7);//przerwanie na sierpniu -> 31
		if (i < _termin.tm_mon) {//od sierpnia w górê
			++i;
			do {
				k = i % 2;//nieparzyste miesi¹ce 31
				dni += (31 - k);
				++i;
			} while (i <= _termin.tm_mon);
		}
	}
	if (_termin.tm_mon > 1) {//dalej ni¿ luty
		if (przestepny)//rok przestêpny
			dni -= 1;
		else//rok zwyk³y
			dni -= 2;
	}
	dni += (_termin.tm_mday - 1);//numerowanie od 0
	_termin.tm_yday = dni;

	// na podstawie http://www.algorytm.org/przetwarzanie-dat/wyznaczanie-dnia-tygodnia.html
	i = (rok - 1) % 100;
	j = (rok - 1) - i;
	k = i + i / 4;
	tydzien = (((((j / 100) % 4) * 5) + k + 1) % 7);//( k + 1 ) bo u nas zero to niedziela
	_termin.tm_wday = (tydzien + _termin.tm_yday) % 7;

	return 0;
}

//										std::string temp
void Tablica::dodajZadanie(){
	system("cls");
	Zadanie nowe;
	char tab41[41];
	char tab301[301];
	std::string temp;
	tm termin;
	int liczba;
	bool powrot = false;
	
	std::cout << "Podaj nazwê zadania (max 40 znaków):" << std::endl;
	std::cin.get(tab41, 41);
	temp = tab41;
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	nowe.nadajNazwe(temp);
	temp.clear();

	std::cout << "\nPodaj opis zadania (max 200 znaków):" << std::endl;
	std::cin.get(tab301, 301);
	temp = tab301;
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	nowe.nadajOpis(temp);
	temp.clear();

	std::cout << "\nPodaj termin zadania (max 40 znaków).\n\
Preferowana forma: 15.06.2020 15:03:09\n-1 -> Brak terminu." << std::endl;
	do {
		if (powrot)
			std::cout << "Spróbuj ponownie." << std::endl;
		powrot = false;
		temp.clear();
		std::cin.get(tab41, 41);
		temp = tab41;
		std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
		if (ustalTermin(termin, temp))//gdy b³¹d
			powrot = true;
	} while (powrot);
	temp.clear();

	nowe.nadajTermin(termin);

	if (mktime(&termin) != -1) {//jest termin
		std::cout << "\nPodaj przypomnienie:\n-1 -> Brak przypomnienia.\n0 -> Przypomnij w dniu mijania terminu.\n";
		std::cout << "[1, 31] -> Przypomnij \"x\" dni przed terminem." << std::endl;
		liczba = podejmijDecyzje(-1, 31);
	}
	else
		liczba = -1;
	nowe.ustawPrzypomnienie(liczba);

	toDo.wstawZadanie(nowe);
}

void Tablica::dodajZadanie(int _nrKolumny, Zadanie& _zadanie) {
	switch (_nrKolumny) {
	case 1:
		toDo.wstawZadanie(_zadanie);
		break;
	case 2:
		doing.wstawZadanie(_zadanie);
		break;
	case 3:
		done.wstawZadanie(_zadanie);
		break;
	}
}

//										wyj¹tki try{podajZadanie()}
void Tablica::skopiujZadanie(int _nrKolumny, int _nrZadania){
	Zadanie kopia;
	switch (_nrKolumny) {//z za³o¿enia nowe zadania pojawiaj¹ siê tylko w kolumnie ToDo
	case 1:
		try {
			kopia = toDo.podajZadanie(_nrZadania);
			toDo.wstawZadanie(kopia);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 2:
		try {
			kopia = doing.podajZadanie(_nrZadania);
			toDo.wstawZadanie(kopia);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 3:
		try {
			kopia = done.podajZadanie(_nrZadania);
			toDo.wstawZadanie(kopia);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	}
	std::cout << "Skopiowano." << std::endl;
}

//										wyj¹tki try{usunZadanie()}
void Tablica::usunZadanie(int _nrKolumny, int _nrZadania){
	switch (_nrKolumny) {
	case 1:
		try {
			toDo.usunZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 2:
		try {
			doing.usunZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 3:
		try {
			done.usunZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	}
}

//										std::string temp
//										wyj¹tki try{podajZadanie()}
void Tablica::edytujZadanie(int _nrKolumny, int _nrZadania){
	system("cls");
	Zadanie *doZmiany = nullptr;
	char tab41[41];
	char tab301[301];
	std::string temp;
	bool podPowrot = false, powrot = true;
	tm termin;
	int liczba;

	switch (_nrKolumny) {
	case 1:
		try {
			doZmiany = &toDo.podajZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 2:
		try {
			doZmiany = &doing.podajZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 3:
		try {
			doZmiany = &done.podajZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	}
	do {
		system("pause");
		system("cls");
		doZmiany->wyswietl();
		std::cout << "\n1 -> Zmieñ nazwê.\n2 -> Zmieñ opis.\n3 -> Zmieñ termin.\n\
4 -> Edytuj przypomnienie.\n5 -> Zakoñcz edycjê." << std::endl;
		switch (podejmijDecyzje(1, 5)) {
		case 1://nazwa
			std::cout << "Podaj now¹ nazwê:" << std::endl;
			std::cin.get(tab41, 41);
			temp = tab41;
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			doZmiany->nadajNazwe(temp);
			temp.clear();
			break;
		case 2://opis
			std::cout << "Podaj nowy opis:" << std::endl;
			std::cin.get(tab301, 301);
			temp = tab301;
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			doZmiany->nadajOpis(temp);
			temp.clear();
			break;
		case 3://termin
			std::cout << "\nPodaj termin zadania (max 40 znaków).\n\
Preferowana forma: 15.06.2020 15:03:09\n-1 -> Brak terminu." << std::endl;
			do {
				if (podPowrot)
					std::cout << "Spróbuj ponownie." << std::endl;
				podPowrot = false;
				temp.clear();
				std::cin.get(tab41, 41);
				temp = tab41;
				std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
				if (ustalTermin(termin, temp))//gdy b³¹d
					podPowrot = true;
			} while (podPowrot);
			doZmiany->nadajTermin(termin);
			break;
		case 4://przypomnienie
			if (mktime(&doZmiany->podajTermin()) == -1)//brak terminu
				std::cout << "Najpierw ustaw termin." << std::endl;
			else {
				std::cout << "Podaj nowe przypomnienie:\n-1 -> Brak przypomnienia.\n0 -> Przypomnij w dniu mijania terminu.\n";
				std::cout << "[1, 31] -> Przypomnij \"x\" dni przed terminem." << std::endl;
				liczba = podejmijDecyzje(-1, 31);
				doZmiany->ustawPrzypomnienie(liczba);
			}
			break;
		case 5://zakoñcz
			powrot = false;
		}
	} while (powrot);
}

//										wyj¹tki try{podajZadanie()}
//										wyj¹tki try{usunZadanie()}
void Tablica::przeniesZadanie(int _zrodloKolumna, int _nrZadania, int _celKolumna){
	Zadanie* doPrzeniesienia = nullptr;

	switch (_zrodloKolumna) {//wybór zadania
	case 1:
		try {
			doPrzeniesienia = &toDo.podajZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 2:
		try {
			doPrzeniesienia = &doing.podajZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 3:
		try {
			doPrzeniesienia = &done.podajZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	}
	if (doPrzeniesienia != nullptr) {
		switch (_celKolumna) {//skopiowanie zadania do nowego miejsca
		case 1:
			toDo.wstawZadanie(*doPrzeniesienia);
			break;
		case 2:
			doing.wstawZadanie(*doPrzeniesienia);
			break;
		case 3:
			done.wstawZadanie(*doPrzeniesienia);
			break;
		}
	}

	switch (_zrodloKolumna) {//usuwanie zadania ze starego miejsca
	case 1:
		try {
			toDo.usunZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 2:
		try {
			doing.usunZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	case 3:
		try {
			done.usunZadanie(_nrZadania);
		}
		catch (Zly_zakres& wyjatek) {
			std::cout << wyjatek.what() << std::endl;
			return;//wyjdŸ z metody
		}
		break;
	}
}

int Tablica::podajRozmiarKolumny(int _nrKolumny) {
	switch (_nrKolumny) {
	case 1:
		return toDo.podajRozmiar();
		break;
	case 2:
		return doing.podajRozmiar();
		break;
	case 3:
		return done.podajRozmiar();
		break;
	}
}

//										stringstream str1, str2, str3
//										std::string temp
//										wyj¹tki try{podajZadanie()}
void Tablica::zapiszDoPliku() {
	int rozmiarMax, i, j, k;
	std::stringstream str1, str2, str3;
	char tab42[42];
	char tab101[105];//.csv
	char tab30[30];
	std::string temp;

	std::cout << "Podaj nazwê pliku (max 100 znaków, format .csv dopisywany automatycznie):" << std::endl;
	std::cin.get(tab101, 101);
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');

	i = strlen(tab101);
	strcpy(tab101 + i, ".csv");
	std::ofstream plik;
	plik.open(tab101, std::ofstream::out);
	if (plik.is_open()) {

		rozmiarMax = toDo.podajRozmiar();
		if (doing.podajRozmiar() > rozmiarMax) rozmiarMax = doing.podajRozmiar();
		if (done.podajRozmiar() > rozmiarMax) rozmiarMax = done.podajRozmiar();

		//nazwa tablicy
		plik << ';' << nazwaTablicy << std::endl;

		//nazwy kolumn
		plik << toDo.podajNazwe();
		plik << ';' << doing.podajNazwe();
		plik << ';' << done.podajNazwe() << std::endl;

		//wypis zadañ
		for (i = 0; i < rozmiarMax; i++) {
			plik << std::endl;//zadania rozdzielone dodatkow¹ przerw¹
			j = i + 1;

			//nazwy zadañ
			if (i < toDo.podajRozmiar()) {
				try {
					plik << toDo.podajZadanie(j).podajNazwe();
				}
				catch (Zly_zakres& wyjatek) {
					std::cout << wyjatek.what() << std::endl;
					plik.close();
					return;//wyjdŸ z metody
				}
			}
			plik << ';';
			if (i < doing.podajRozmiar()) {
				try {
					plik << doing.podajZadanie(j).podajNazwe();
				}
				catch (Zly_zakres& wyjatek) {
					std::cout << wyjatek.what() << std::endl;
					plik.close();
					return;//wyjdŸ z metody
				}
			}
			plik << ';';
			if (i < done.podajRozmiar()) {
				try {
					plik << done.podajZadanie(j).podajNazwe();
				}
				catch (Zly_zakres& wyjatek) {
					std::cout << wyjatek.what() << std::endl;
					plik.close();
					return;//wyjdŸ z metody
				}
			}
			plik << std::endl;

			//					zmienna j zabezpieczona przed wywo³aniem rzucenia wyj¹tku

			//opisy zadañ
			if (i < toDo.podajRozmiar()) {
				str1.clear();//czyszczenie
				str1.str(std::string());//czyszczenie
				str1 << toDo.podajZadanie(j).podajOpis();
			}

			if (i < doing.podajRozmiar()) {
				str2.clear();//czyszczenie
				str2.str(std::string());//czyszczenie
				str2 << doing.podajZadanie(j).podajOpis();
			}

			if (i < done.podajRozmiar()) {
				str3.clear();//czyszczenie
				str3.str(std::string());//czyszczenie
				str3 << done.podajZadanie(j).podajOpis();
			}

			for (k = 0; k < 5; ++k) {
				temp.clear();
				if (i < toDo.podajRozmiar()) {
					str1.get(tab42, 42);
					temp = tab42;
					if (strlen(tab42) == 41) {//odczyt 41 znaków
						temp.pop_back();
						str1.seekg(-1, std::ios_base::_Seekcur);
					}
					if (tab42[39] != ' ' && tab42[40] != ' ' && strlen(tab42) == 41)//uciêty wyraz
						temp.push_back('-');
					plik << temp;
				}
				plik << ';';

				temp.clear();
				if (i < doing.podajRozmiar()) {
					str2.get(tab42, 42);
					temp = tab42;
					if (strlen(tab42) == 41) {//odczyt 41 znaków
						temp.pop_back();
						str2.seekg(-1, std::ios_base::_Seekcur);
					}
					if (tab42[39] != ' ' && tab42[40] != ' ' && strlen(tab42) == 41)//uciêty wyraz
						temp.push_back('-');
					plik << temp;
				}
				plik << ';';

				temp.clear();
				if (i < done.podajRozmiar()) {
					str3.get(tab42, 42);
					temp = tab42;
					if (strlen(tab42) == 41) {//odczyt 41 znaków
						temp.pop_back();
						str3.seekg(-1, std::ios_base::_Seekcur);
					}
					if (tab42[39] != ' ' && tab42[40] != ' ' && strlen(tab42) == 41)//uciêty wyraz
						temp.push_back('-');
					plik << temp;
				}
				plik << std::endl;
			}

			//wypis terminów
			if (i < toDo.podajRozmiar()) {
				if (mktime(&toDo.podajZadanie(j).podajTermin()) == -1)
					strcpy(tab30, "Brak terminu.");
				else
					strftime(tab30, 30, "'%c", &toDo.podajZadanie(j).podajTermin());
				plik << tab30;
			}
			plik << ';';

			if (i < doing.podajRozmiar()) {
				if (mktime(&doing.podajZadanie(j).podajTermin()) == -1)
					strcpy(tab30, "Brak terminu.");
				else
					strftime(tab30, 30, "'%c", &doing.podajZadanie(j).podajTermin());
				plik << tab30;
			}
			plik << ';';

			if (i < done.podajRozmiar()) {
				if (mktime(&done.podajZadanie(j).podajTermin()) == -1)
					strcpy(tab30, "Brak terminu.");
				else
					strftime(tab30, 30, "'%c", &done.podajZadanie(j).podajTermin());
				plik << tab30;
			}
			plik << std::endl;

			//wypis przypomnieñ
			if (i < toDo.podajRozmiar())
				plik << toDo.podajZadanie(j).podajPrzypomnienie();
			plik << ';';

			if (i < doing.podajRozmiar())
				plik << doing.podajZadanie(j).podajPrzypomnienie();
			plik << ';';

			if (i < done.podajRozmiar())
				plik << done.podajZadanie(j).podajPrzypomnienie();
			plik << std::endl;
		}
	}
	else//otwarcie pliku nie powiod³o siê
		std::cout << "Nie uda³o siê otworzyæ pliku o nazwie: " << tab101 << std::endl;
}

//										stringstream str1, str2, str3
//										std::string temp
//										wyj¹tki try{podajZadanie()}
void Tablica::wyswietl(){
	int rozmiarMax, i, j, k;
	std::stringstream str1, str2, str3;
	char tab42[42];
	std::string temp;

	rozmiarMax = toDo.podajRozmiar();
	if (doing.podajRozmiar() > rozmiarMax) rozmiarMax = doing.podajRozmiar();
	if (done.podajRozmiar() > rozmiarMax) rozmiarMax = done.podajRozmiar();

	//nazwa tablicy
	i = (142 - nazwaTablicy.size()) / 2;
	i += nazwaTablicy.size();
	std::cout.width(i);
	std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
	std::cout << nazwaTablicy << std::endl << std::endl;

	//nazwy kolumn
	std::cout.width(20);
	std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
	std::cout << "1. " << toDo.podajNazwe();
	std::cout.width(46);
	std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
	std::cout << "2. " << doing.podajNazwe();
	std::cout.width(45);
	std::cout.setf(std::ios_base::right, std::ios_base::adjustfield);
	std::cout << "3. " << done.podajNazwe() << std::endl;

	//wypis zadañ
	for (i = 0; i < rozmiarMax; i++) {
		std::cout << std::endl;
		j = i + 1;

		//nazwy zadañ
		if (i < toDo.podajRozmiar()) {
			try {
				str1 << j << ". " << toDo.podajZadanie(j).podajNazwe();
			}
			catch (Zly_zakres& wyjatek) {
				std::cout << wyjatek.what() << std::endl;
				return;//wyjdŸ z metody
			}
		}
		else
			str1 << '-';
		std::cout.width(43);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		std::cout << str1.str();
		std::cout.width(7);
		std::cout << ' ';//zatwierdzenie nastawienia szerokoœci
		str1.clear();//czyszczenie
		str1.str(std::string());//czyszczenie

		if (i < doing.podajRozmiar()) {
			try {
				str2 << j << ". " << doing.podajZadanie(j).podajNazwe();
			}
			catch (Zly_zakres& wyjatek) {
				std::cout << wyjatek.what() << std::endl;
				return;//wyjdŸ z metody
			}
		}
		else
			str2 << '-';
		std::cout.width(43);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		std::cout << str2.str();
		std::cout.width(7);
		std::cout << ' ';//zatwierdzenie nastawienia szerokoœci
		str2.clear();//czyszczenie
		str2.str(std::string());//czyszczenie

		if (i < done.podajRozmiar()) {
			try {
				str3 << j << ". " << done.podajZadanie(j).podajNazwe();
			}
			catch (Zly_zakres& wyjatek) {
				std::cout << wyjatek.what() << std::endl;
				return;//wyjdŸ z metody
			}
		}
		else
			str3 << '-';
		std::cout.width(43);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		std::cout << str3.str();
		std::cout << std::endl;
		str3.clear();//czyszczenie
		str3.str(std::string());//czyszczenie

		//					zmienna j zabezpieczona przed wywo³aniem rzucenia wyj¹tku

		//opisy zadañ
		if (i < toDo.podajRozmiar())
			str1 << toDo.podajZadanie(j).podajOpis();

		if (i < doing.podajRozmiar()) 
			str2 << doing.podajZadanie(j).podajOpis();
		
		if (i < done.podajRozmiar()) 
			str3 << done.podajZadanie(j).podajOpis();

		for (k = 0; k < 5; ++k) {
			temp.clear();
			std::cout.width(41);
			std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
			if (i < toDo.podajRozmiar()) {
				str1.get(tab42, 42);
				temp = tab42;
				if (strlen(tab42) == 41) {//odczyt 41 znaków
					temp.pop_back();
					str1.seekg(-1, std::ios_base::_Seekcur);
				}
				if (tab42[39] != ' ' && tab42[40] != ' ' && strlen(tab42) == 41 && k != 4)//uciêty wyraz
					temp.push_back('-');
				if (tab42[39] != ' ' && tab42[40] == ' ' && strlen(tab42) == 41)//nastêpna jest spacja
					str1.seekg(1, std::ios_base::_Seekcur);
				if (strlen(tab42) == 0)//nic nie wczyta³
					temp.push_back('-');
				std::cout << temp;
			}
			else
				std::cout << '-';
			std::cout.width(9);
			std::cout << ' ';//zatwierdzenie nastawienia szerokoœci

			temp.clear();
			std::cout.width(41);
			std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
			if (i < doing.podajRozmiar()) {
				str2.get(tab42, 42);
				temp = tab42;
				if (strlen(tab42) == 41) {//odczyt 41 znaków
					temp.pop_back();
					str2.seekg(-1, std::ios_base::_Seekcur);
				}
				if (tab42[39] != ' ' && tab42[40] != ' ' && strlen(tab42) == 41 && k != 4)//uciêty wyraz
					temp.push_back('-');
				if (tab42[39] != ' ' && tab42[40] == ' ' && strlen(tab42) == 41)//nastêpna jest spacja
					str2.seekg(1, std::ios_base::_Seekcur);
				if (strlen(tab42) == 0)//nic nie wczyta³
					temp.push_back('-');
				std::cout << temp;
			}
			else
				std::cout << '-';
			std::cout.width(9);
			std::cout << ' ';//zatwierdzenie nastawienia szerokoœci

			temp.clear();
			std::cout.width(41);
			std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
			if (i < done.podajRozmiar()) {
				str3.get(tab42, 42);
				temp = tab42;
				if (strlen(tab42) == 41) {//odczyt 41 znaków
					temp.pop_back();
					str3.seekg(-1, std::ios_base::_Seekcur);
				}
				if (tab42[39] != ' ' && tab42[40] != ' ' && strlen(tab42) == 41 && k != 4)//uciêty wyraz
					temp.push_back('-');
				if (tab42[39] != ' ' && tab42[40] == ' ' && strlen(tab42) == 41)//nastêpna jest spacja
					str3.seekg(1, std::ios_base::_Seekcur);
				if (strlen(tab42) == 0)//nic nie wczyta³
					temp.push_back('-');
				std::cout << temp;
			}
			else
				std::cout << '-';
			std::cout << std::endl;
		}
		str1.clear();//czyszczenie
		str1.str(std::string());//czyszczenie
		str2.clear();//czyszczenie
		str2.str(std::string());//czyszczenie
		str3.clear();//czyszczenie
		str3.str(std::string());//czyszczenie

		//wypis terminów
		std::cout.width(40);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		if (i < toDo.podajRozmiar())
			std::cout << toDo.podajZadanie(j).podajTerminTekst();
		else
			std::cout << '-';
		std::cout.width(10);
		std::cout << ' ';//zatwierdzenie nastawienia szerokoœci

		std::cout.width(40);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		if (i < doing.podajRozmiar())
			std::cout << doing.podajZadanie(j).podajTerminTekst();
		else
			std::cout << '-';
		std::cout.width(10);
		std::cout << ' ';//zatwierdzenie nastawienia szerokoœci

		std::cout.width(40);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		if (i < done.podajRozmiar())
			std::cout << done.podajZadanie(j).podajTerminTekst();
		else
			std::cout << '-';
		std::cout << std::endl;

		//wypis przypomnieñ
		std::cout.width(40);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		if (i < toDo.podajRozmiar())
			toDo.przypomnij(j);
		else
			std::cout << '-';
		std::cout.width(10);
		std::cout << ' ';//zatwierdzenie nastawienia szerokoœci

		std::cout.width(40);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		if (i < doing.podajRozmiar())
			doing.przypomnij(j);
		else
			std::cout << '-';
		std::cout.width(10);
		std::cout << ' ';//zatwierdzenie nastawienia szerokoœci

		std::cout.width(40);
		std::cout.setf(std::ios_base::left, std::ios_base::adjustfield);
		if (i < done.podajRozmiar())
			done.ilePrzedCzasem(j);
		else
			std::cout << '-';
		std::cout << std::endl;
	}
}
