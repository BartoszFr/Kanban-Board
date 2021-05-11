#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include <vld.h>

/*
Do projektu doda�em pliki: decyzja.cpp, decyzja.h, Zly_zakres.cpp oraz Zly_zakres.h,
jak r�wnie� skorygowany diagram.
Klasa Zly_zakres dziedzicz�ca po exception zosta�a wzi�ta z projektu 3. R�wnaniaLiniowe
i dopasowana do obecnych potrzeb.

Mechanizmy:
1. Operatory:
	- Zadanie

2. Zarz�dzanie pami�ci�:
	- Zadanie
	- Student

3. Wyj�tki:
	- Zly_zakres
	- Kolumna
	- ToDo, Doing, Done
	- Tablica
	- Student

4. Kontenery/STL:
	- Kolumna
	- Student

5. String/Stringstream:
	- Zadanie
	- ToDo, Doing, Done
	- Zly_zakres
	- Tablica
	- Student

Przygotowa�em przyk�adowe dane do wczytania pod nazw� "plik".

Podczas pracy programu prosz� rozszerzy� okno konsoli tak, aby pomie�ci�a oko�o 150 znak�w.
Podobnie prosz� porozszerza� kom�rki w programie Excel, gdy� wpisane dane s� przewa�nie za d�ugie.
*/

int main(void) {
	char tab51[51];
	setlocale(LC_ALL, "polish");

	std::cout << "Podaj nazw� studenta (max 50 znak�w):" << std::endl;
	std::cin.get(tab51, 51);
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	Student student(tab51);
	student.rozpocznijPrace();

	return 0;
}