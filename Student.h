#pragma once
#include "Tablica.h"

class Student
{
private:
	std::vector <Tablica> tablice;
	char* nazwa;
public:
	Student(char* _nazwa);
	~Student();
	Student(const Student& _student) = delete;
	Student& operator=(const Student& _prawy) = delete;

	void rozpocznijPrace();

	void utworzTablice();
	void utworzTablice(const char* _nazwa);
	void skopiujTablice(int _nrTablicy = 1);
	void usunTablice(int _nrTablicy = 1);
	void zarzadzajTablica(Tablica*& _tablica, bool& _powrot);
	void wczytajZPliku(bool& _powrot);

	void wyswietlTablice(int _nrTablicy = 1);
};

