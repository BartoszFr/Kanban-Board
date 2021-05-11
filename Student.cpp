#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"

//										zarz¹dzanie pamiêci¹
//										wyj¹tki try{new}
Student::Student(char* _nazwa)
	: nazwa(nullptr)
{
	try {
		nazwa = new char[51];
		strcpy(nazwa, _nazwa);
	}
	catch (std::bad_alloc& wyjatek) {
		std::cout << "Student, konstruktor: " << wyjatek.what() << std::endl;
		system("pause");
		system("cls");
		nazwa = nullptr;//dla pewnoœci
	}
}

//										zarz¹dzanie pamiêci¹
Student::~Student() {
	tablice.clear();
	if (nazwa != nullptr)
		delete[] nazwa;
}

//										std::string temp
//										wyj¹tki try{wyswietlTablice()}
//										try{skopiujTablice()}
//										try{usunTablice()}
//										try{tablice.at()}
void Student::rozpocznijPrace() {
	int i;
	bool powrot = true, podPowrot = true;
	std::string temp;
	Tablica* tablica= nullptr;

	std::cout << std::endl << "Witaj " << nazwa << std::endl << std::endl;

	do {
		system("pause");
		system("cls");
		std::cout << "1 -> Utwórz tablicê.\n2 -> Skopiuj tablicê.\n3 -> Usuñ tablicê.\n4 -> Zarz¹dzaj tablic¹.\n\
5 -> Zapisz do pliku.\n6 -> Wczytaj dane z pliku.\n7 -> Zakoñcz pracê." << std::endl;
		try {
			wyswietlTablice();
		}
		catch (std::out_of_range& wyjatek) {
			std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna istnieæ.\
Program zostanie wy³¹czony." << std::endl;
			powrot = false;
			continue;
		}

		switch (podejmijDecyzje(1, 7)) {
		case 1://utwórz tablice
			system("cls");
			utworzTablice();
			break;
		case 2://skopiuj tablice
			system("cls");
			if (tablice.size() == 0)
				std::cout << "Brak tablic." << std::endl;
			
			else if (tablice.size() == 1) {
				try {
					skopiujTablice();
					std::cout << "Skopiowano." << std::endl;
				}
				catch (std::out_of_range& wyjatek) {
					std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna istnieæ.\
Program zostanie wy³¹czony." << std::endl;
					powrot = false;
					continue;
				}
			}
			
			else {
				std::cout << "Któr¹ tablicê chcesz skopiowaæ? [1, " << tablice.size() << ']' << std::endl;
				i = podejmijDecyzje(1, tablice.size());
				try {
					skopiujTablice(i);
				}
				catch (std::out_of_range& wyjatek) {
					std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna istnieæ.\
Program zostanie wy³¹czony." << std::endl;
					powrot = false;
					continue;
				}
			}
			break;
		case 3://usuñ tablice
			system("cls");
			if (tablice.size() == 0)
				std::cout << "Brak tablic." << std::endl;
			
			else if (tablice.size() == 1) {
				std::cout << "Usuniêto." << std::endl;
				try {
					usunTablice();
				}
				catch (Zly_zakres& wyjatek) {
					std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna by³a istnieæ.\
Program zostanie wy³¹czony." << std::endl;
					powrot = false;
					continue;
				}
			}
			
			else {
				std::cout << "Któr¹ tablicê chcesz usun¹æ? [1, " << tablice.size() << ']' << std::endl;
				i = podejmijDecyzje(1, tablice.size());
				try {
					usunTablice(i);
				}
				catch (Zly_zakres& wyjatek) {
					std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna by³a istnieæ.\
Program zostanie wy³¹czony." << std::endl;
					powrot = false;
					continue;
				}
			}
			break;
		case 4://zarz¹dzaj tablic¹
			system("cls");
			if (tablice.size() == 0) {
				std::cout << "Brak tablic." << std::endl;
				tablica = nullptr;
			}
			
			else if (tablice.size() == 1) {
				i = 0;
				tablica = &tablice.at(i);
			}
			
			else {
				std::cout << "Któr¹ tablic¹ chcesz zarz¹dzaæ? [1, " << tablice.size() << "]." << std::endl;
				i = podejmijDecyzje(1, tablice.size());
				--i;
				tablica = &tablice.at(i);
			}

			if (tablica != nullptr)
				zarzadzajTablica(tablica, powrot);
			break;//to by³o zarz¹dzanie tablic¹
		case 5://zapisz
			system("cls");
			if (tablice.size() == 0) {
				std::cout << "Brak tablic." << std::endl;
				tablica = nullptr;
			}
			
			else if (tablice.size() == 1) {
				i = 0;
				try {
					tablica = &tablice.at(i);
				}
				catch (std::out_of_range& wyjatek) {
					std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna istnieæ.\
Program zostanie wy³¹czony." << std::endl;
					powrot = false;
					continue;
				}
			}
			
			else {
				std::cout << "Któr¹ tablicê chcesz zapisaæ? [1, " << tablice.size() << "]." << std::endl;
				i = podejmijDecyzje(1, tablice.size());
				--i;
				try {
					tablica = &tablice.at(i);
				}
				catch (std::out_of_range& wyjatek) {
					std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna istnieæ.\
Program zostanie wy³¹czony." << std::endl;
					powrot = false;
					continue;
				}
			}
			
			if (tablica != nullptr)
				tablica->zapiszDoPliku();
			break;
		case 6://wczytaj
			system("cls");
			wczytajZPliku(powrot);
			break;
		case 7://zakoñcz
			system("cls");
			powrot = false;
			break;
		}
	} while (powrot);
}

//										std::string temp
void Student::utworzTablice() {
	char tab51[51];
	std::string temp;
	Tablica nowa;

	std::cout << "Nadaj nazwê tablicy (max 50 znaków)." << std::endl;
	std::cin.get(tab51, 51);
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	temp = tab51;
	nowa.nadajNazwe(temp);
	temp.clear();
	tablice.push_back(nowa);
}

//										std::vector
//										std::string temp
void Student::utworzTablice(const char* _nazwa) {
	std::string temp;
	Tablica nowa;

	temp = _nazwa;
	nowa.nadajNazwe(temp);
	temp.clear();
	tablice.push_back(nowa);
}

//										std::vector
void Student::skopiujTablice(int _nrTablicy) {
	--_nrTablicy;
	Tablica nowa = tablice.at(_nrTablicy);
	tablice.push_back(nowa);
}

//										std::vector
//										wyj¹tki throw
void Student::usunTablice(int _nrTablicy) {
	if (_nrTablicy > tablice.size() || _nrTablicy < 1) {//numeracja zadañ od 1
		Zly_zakres wyjatek(_nrTablicy, tablice.size());
		throw wyjatek;
	}
	--_nrTablicy;
	std::vector<Tablica>::iterator iter = tablice.begin();
	iter += (_nrTablicy);
	tablice.erase(iter);
}

//										std::string temp
void Student::zarzadzajTablica(Tablica*& _tablica, bool& _powrot) {
	int i, j, k;
	bool podPowrot = true;
	std::string temp;
	char tab51[51];
	do {
		podPowrot = true;
		system("pause");
		system("cls");
	
		_tablica->wyswietl();

		std::cout << "\n1 -> Zmieñ nazwê tablicy.\n2 -> Dodaj zadanie.\n3 -> Skopiuj zadanie.\n\
4 -> Usuñ zadanie.\n5 -> Edytuj zadanie.\n6 -> Przenieœ zadanie.\n7 -> Zakoñcz." << std::endl;

		switch (podejmijDecyzje(1, 7)) {
		case 1://zmien nazwe tablicy
			std::cout << "Nadaj now¹ nazwê tablicy (max 50 znaków)." << std::endl;
			std::cin.get(tab51, 51);
			std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
			temp = tab51;
			_tablica->nadajNazwe(temp);
			temp.clear();
			break;
		case 2://dodaj zadanie
			_tablica->dodajZadanie();
			break;
		case 3://skopiuj zadanie
			std::cout << "Podaj numer kolumny, z której chcesz skopiowaæ zadanie [1, 3]:" << std::endl;
			i = podejmijDecyzje(1, 3);
			
			if (_tablica->podajRozmiarKolumny(i) == 0)
				std::cout << "Brak zadañ w wybranej kolumnie." << std::endl;
			
			else if (_tablica->podajRozmiarKolumny(i) == 1) 
				_tablica->skopiujZadanie(i, 1);

			else {
				std::cout << "Podaj numer zadania [1, " << _tablica->podajRozmiarKolumny(i) << "]:" << std::endl;
				j = podejmijDecyzje(1, _tablica->podajRozmiarKolumny(i));
				_tablica->skopiujZadanie(i, j);
			}
			break;
		case 4://usun zadanie
			std::cout << "Podaj numer kolumny, z której chcesz usun¹æ zadanie [1, 3]:" << std::endl;
			i = podejmijDecyzje(1, 3);
			
			if (_tablica->podajRozmiarKolumny(i) == 0)
				std::cout << "Brak zadañ w wybranej kolumnie." << std::endl;
			
			else if (_tablica->podajRozmiarKolumny(i) == 1)
				_tablica->usunZadanie(i, 1);
			
			else {
				std::cout << "Podaj numer zadania [1, " << _tablica->podajRozmiarKolumny(i) << "]:" << std::endl;
				j = podejmijDecyzje(1, _tablica->podajRozmiarKolumny(i));
				_tablica->usunZadanie(i, j);
			}
			break;
		case 5://edytuj zadanie
			std::cout << "Podaj numer kolumny, z której chcesz edytowaæ zadanie [1, 3]:" << std::endl;
			i = podejmijDecyzje(1, 3);
			
			if (_tablica->podajRozmiarKolumny(i) == 0)
				std::cout << "Brak zadañ w wybranej kolumnie." << std::endl;
			
			else if (_tablica->podajRozmiarKolumny(i) == 1)
				_tablica->edytujZadanie(i, 1);

			else {
				std::cout << "Podaj numer zadania [1, " << _tablica->podajRozmiarKolumny(i) << "]:" << std::endl;
				j = podejmijDecyzje(1, _tablica->podajRozmiarKolumny(i));
				_tablica->edytujZadanie(i, j);
			}
			break;
		case 6://przenieœ zadanie
			std::cout << "Podaj numer kolumny, z której chcesz przenieœæ zadanie [1, 3]:" << std::endl;
			i = podejmijDecyzje(1, 3);

			if (_tablica->podajRozmiarKolumny(i) == 0)
				std::cout << "Brak zadañ w wybranej kolumnie." << std::endl;

			else if (_tablica->podajRozmiarKolumny(i) == 1) {
				std::cout << "Podaj numer kolumny, do której chcesz przenieœæ zadanie [1, 3]:" << std::endl;
				k = podejmijDecyzje(1, 3);
				_tablica->przeniesZadanie(i, 1, k);
			}

			else {
				std::cout << "Podaj numer zadania [1, " << _tablica->podajRozmiarKolumny(i) << "]:" << std::endl;
				j = podejmijDecyzje(1, _tablica->podajRozmiarKolumny(i));
				std::cout << "Podaj numer kolumny, do której chcesz przenieœæ zadanie [1, 3]:" << std::endl;
				k = podejmijDecyzje(1, 3);
				_tablica->przeniesZadanie(i, j, k);
			}
			break;
		case 7://zakoñcz
			podPowrot = false; 
			break;
		}
	} while (podPowrot);
}

//										wyj¹tki try{at()}
//										wyj¹tki try{std::stoi()}
//										std::string temp
//										stringstream str, str1, str2, str3
void Student::wczytajZPliku(bool& _powrot) {
	int i, k;
	std::stringstream str, str1, str2, str3;
	char tab101[105];//.csv
	std::string temp;
	Tablica* tablica = nullptr;
	Zadanie nowe1, nowe2, nowe3;
	tm termin;
	int liczba;

	std::cout << "Podaj nazwê pliku (max 100 znaków, format .csv dopisywany automatycznie):" << std::endl;
	std::cin.get(tab101, 101);
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');

	i = strlen(tab101);
	strcpy(tab101 + i, ".csv");
	std::ifstream plik;
	plik.open(tab101, std::ifstream::in);
	if (plik.is_open()) {
		//nazwa tablicy
		std::getline(plik, temp);//';' + nazwa tablicy
		temp.erase(0, 1);
		utworzTablice(temp.c_str());

		try {
			tablica = &tablice.at(tablice.size() - 1);
		}
		catch (std::out_of_range& wyjatek) {
			std::cout << wyjatek.what() << "\nCoœ z³ego siê sta³o. Ta tablica powinna istnieæ.\
Program zostanie wy³¹czony." << std::endl;
			_powrot = false;
			return;
		}

		//nazwy kolumn - domyœlnie w konstruktorze
		std::getline(plik, temp);

		//zadania - potencjalny koniec pliku
		while(1) {
			std::getline(plik, temp);
			if (plik.eof())
				return;//koniec pliku

			//reset danych
			temp.clear();
			temp = "Brak nazwy.";
			nowe1.nadajNazwe(temp);
			nowe2.nadajNazwe(temp);
			nowe3.nadajNazwe(temp);
			temp.clear();

			//nazwy zadañ
			std::getline(plik, temp);
			str << temp;

			std::getline(str, temp, ';');
			if (!temp.empty())//coœ tam by³o
				nowe1.nadajNazwe(temp);

			std::getline(str, temp, ';');
			if (!temp.empty())//coœ tam by³o
				nowe2.nadajNazwe(temp);

			std::getline(str, temp);
			if (!temp.empty())//coœ tam by³o
				nowe3.nadajNazwe(temp);

			str.clear();
			str.str(std::string());
			temp.clear();

			//opisy
			for (i = 0; i < 5; ++i) {
				std::getline(plik, temp);
				while (1) {//usuñ '-'
					k = temp.find('-');
					if (k != std::string::npos) {
						temp.erase(k, 1);
					}
					else {
						break;
					}
				}
				str << temp;

				if (nowe1.podajNazwe() == "Brak nazwy.")//pusto
					str.seekg(1, std::ios_base::_Seekcur);//pomiñ ';'
				else {
					std::getline(str, temp, ';');
					str1 << temp;
				}

				if (nowe2.podajNazwe() == "Brak nazwy.")//pusto
					str.seekg(1, std::ios_base::_Seekcur);//pomiñ ';'
				else {
					std::getline(str, temp, ';');
					str2 << temp;
				}

				if (nowe3.podajNazwe() == "Brak nazwy.") {}//pusto
				else {
					std::getline(str, temp);
					str3 << temp;
				}
				str.clear();
				str.str(std::string());
				temp.clear();
			}
			//opisy skompletowane

			if (nowe1.podajNazwe() != "Brak nazwy.") {//zadanie istnieje
				std::getline(str1, temp);
				nowe1.nadajOpis(temp);
			}
			str1.clear();
			str1.str(std::string());
			temp.clear();

			if (nowe2.podajNazwe() != "Brak nazwy.") {//zadanie istnieje
				std::getline(str2, temp);
				nowe2.nadajOpis(temp);
			}
			str2.clear();
			str2.str(std::string());
			temp.clear();

			if (nowe3.podajNazwe() != "Brak nazwy.") {//zadanie istnieje
				std::getline(str3, temp);
				nowe3.nadajOpis(temp);
			}
			str3.clear();
			str3.str(std::string());
			temp.clear();

			//terminy
			std::getline(plik, temp);
			while (1) {//usuñ '\''
				k = temp.find('\'');
				if (k != std::string::npos) {
					temp.erase(k, 1);
				}
				else {
					break;
				}
			}
			str << temp;

			if (nowe1.podajNazwe() == "Brak nazwy.")//zadanie nie istnieje
				str.seekg(1, std::ios_base::_Seekcur);//pomiñ ';'
			else {
				std::getline(str, temp, ';');
				tablica->ustalTermin(termin, temp);
				nowe1.nadajTermin(termin);
			}

			if (nowe2.podajNazwe() == "Brak nazwy.")//zadanie nie istnieje
				str.seekg(1, std::ios_base::_Seekcur);//pomiñ ';'
			else {
				std::getline(str, temp, ';');
				tablica->ustalTermin(termin, temp);
				nowe2.nadajTermin(termin);
			}

			if (nowe3.podajNazwe() == "Brak nazwy.") {}//zadanie nie istnieje
			else {
				std::getline(str, temp);
				tablica->ustalTermin(termin, temp);
				nowe3.nadajTermin(termin);
			}

			str.clear();
			str.str(std::string());
			temp.clear();

			//przypomnienia
			std::getline(plik, temp);
			str << temp;

			if (nowe1.podajNazwe() == "Brak nazwy.")//zadanie nie istnieje
				str.seekg(1, std::ios_base::_Seekcur);//pomiñ ';'
			else {
				std::getline(str, temp, ';');
				try {
					liczba = std::stoi(temp);
				}
				catch (std::invalid_argument& wyjatek) {
					std::cout << wyjatek.what() << std::endl;
					std::cout << "B³¹d odczytu przypomnienia." << std::endl;
					liczba = -1;
				}
				nowe1.ustawPrzypomnienie(liczba);
			}

			if (nowe2.podajNazwe() == "Brak nazwy.")//zadanie nie istnieje
				str.seekg(1, std::ios_base::_Seekcur);//pomiñ ';'
			else {
				std::getline(str, temp, ';');
				try {
					liczba = std::stoi(temp);
				}
				catch (std::invalid_argument& wyjatek) {
					std::cout << wyjatek.what() << std::endl;
					std::cout << "B³¹d odczytu przypomnienia." << std::endl;
					liczba = -1;
				}
				nowe2.ustawPrzypomnienie(liczba);
			}

			if (nowe3.podajNazwe() == "Brak nazwy.") {}//zadanie nie istnieje
			else {
				std::getline(str, temp);
				try {
					liczba = std::stoi(temp);
				}
				catch (std::invalid_argument& wyjatek) {
					std::cout << wyjatek.what() << std::endl;
					std::cout << "B³¹d odczytu przypomnienia." << std::endl;
					liczba = -1;
				}
				nowe3.ustawPrzypomnienie(liczba);
			}

			str.clear();
			str.str(std::string());
			temp.clear();

			//dodanie istniej¹cych zadañ
			if (nowe1.podajNazwe() != "Brak nazwy.")//zadanie istnieje
				tablica->dodajZadanie(1, nowe1);

			if (nowe2.podajNazwe() != "Brak nazwy.")//zadanie istnieje
				tablica->dodajZadanie(2, nowe2);

			if (nowe3.podajNazwe() != "Brak nazwy.")//zadanie istnieje
				tablica->dodajZadanie(3, nowe3);

		}
	}
	else//otwarcie pliku nie powiod³o siê
		std::cout << "Nie uda³o siê otworzyæ pliku o nazwie: " << tab101 << std::endl;
}

void Student::wyswietlTablice(int _nrTablicy){
	int i, j;
	if (tablice.size() == 0)
		std::cout << std::endl << "Brak tablic." << std::endl;
	else {
		std::cout << std::endl << "Posiadane tablice:" << std::endl;
		for (i = 0; i < tablice.size(); ++i) {
			j = i + 1;
			std::cout << j << ". " << tablice.at(i).podajNazwe() << std::endl;
		}
	}
}