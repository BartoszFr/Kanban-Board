#define _CRT_SECURE_NO_WARNINGS
#include "Zadanie.h"

//										zarz¹dzanie pamiêci¹
//										wyj¹tki try{new}
Zadanie::Zadanie()
	: nazwa("Brak nazwy.")
	, opis("Brak opisu.")
	, terminTekst(nullptr)
	, przypomnienie(-1)
{	
	termin = { -1, -1, -1, -1, -1, -1, -1, -1, -1, };//brak terminu - domyœlnie
	try {
		terminTekst = new char[40];
		strcpy(terminTekst, "Brak terminu.");
	}
	catch (std::bad_alloc& wyjatek) {
		std::cout << "Zadanie, konstruktor: " << wyjatek.what() << std::endl;
		system("pause");
		system("cls");
		terminTekst = nullptr;//dla pewnoœci
	}
}

//										zarz¹dzanie pamiêci¹
Zadanie::~Zadanie() {
	nazwa.clear();
	opis.clear();
	if (terminTekst != nullptr)
		delete[] terminTekst;
}

//										zarz¹dzanie pamiêci¹
//										wyj¹tki try{new}
Zadanie::Zadanie(const Zadanie& _prawy)
	: nazwa(_prawy.nazwa)
	, opis(_prawy.opis)
	, termin(_prawy.termin)
	, terminTekst(nullptr)
	, przypomnienie(_prawy.przypomnienie)
	{
	try {
		terminTekst = new char[40];
		std::copy(_prawy.terminTekst, _prawy.terminTekst + 40, terminTekst);
	}
	catch (std::bad_alloc& wyjatek) {
		std::cout << "Zadanie, konstruktor kopiuj¹cy: " << wyjatek.what() << std::endl;
		system("pause");
		system("cls");
		terminTekst = nullptr;//dla pewnoœci
	}
}

//										zarz¹dzanie pamiêci¹
//										operator=
//										wyj¹tki try{new}
Zadanie& Zadanie::operator=(const Zadanie& _prawy) {
	if (this == &_prawy)
		return *this;
	nazwa = _prawy.nazwa;
	opis = _prawy.opis;
	termin = _prawy.termin;
	przypomnienie = _prawy.przypomnienie;
	if (terminTekst != nullptr) {
		delete[] terminTekst;
		terminTekst = nullptr;
	}
	try {
		terminTekst = new char[40];
		std::copy(_prawy.terminTekst, _prawy.terminTekst + 40, terminTekst);
	}
	catch (std::bad_alloc& wyjatek) {
		std::cout << "Zadanie, operator=: " << wyjatek.what() << std::endl;
		system("pause");
		system("cls");
		terminTekst = nullptr;//dla pewnoœci
	}
	return *this;
}

//										operator<
bool Zadanie::operator<(Zadanie& _prawy) {
	if (mktime(&termin) == -1)
		return false;//brak terminu traktowany zawsze jako d³u¿szy termin
	if (mktime(&(_prawy.termin)) == -1)
		return true;
	if (mktime(&termin) < mktime(&(_prawy.termin)))
		return true;
	else
		return false;
}

void Zadanie::nadajTermin(tm& _termin) { 
	if (mktime(&_termin) == -1) {
		termin = { -1, -1, -1, -1, -1, -1, -1, -1, -1, };
		przypomnienie = -1;
		strcpy(terminTekst, "Brak terminu.");
	}
	else {
		termin = _termin;
		strftime(terminTekst, 40, "%#c", &termin);
	}
}

//										std::string temp
void Zadanie::wyswietl() {
	std::string temp;
	if (przypomnienie == -1)
		temp = "Brak przypomnienia.";
	else if (przypomnienie == 0)
		temp = "Przypomnienie ustawione na dzieñ mijania terminu.";
	else {
		temp = "Przypomnienie ustawione na ";
		temp.append(std::to_string(przypomnienie));
		temp.append(" dni przed terminem.");
	}
	std::cout << nazwa << std::endl << opis << std::endl << terminTekst << std::endl
		<< temp << std::endl;
}