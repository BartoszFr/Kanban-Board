#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include <vld.h>

/*
Do projektu doda³em pliki: decyzja.cpp, decyzja.h, Zly_zakres.cpp oraz Zly_zakres.h,
jak równie¿ skorygowany diagram.
Klasa Zly_zakres dziedzicz¹ca po exception zosta³a wziêta z projektu 3. RównaniaLiniowe
i dopasowana do obecnych potrzeb.

Mechanizmy:
1. Operatory:
	- Zadanie

2. Zarz¹dzanie pamiêci¹:
	- Zadanie
	- Student

3. Wyj¹tki:
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

Przygotowa³em przyk³adowe dane do wczytania pod nazw¹ "plik".

Podczas pracy programu proszê rozszerzyæ okno konsoli tak, aby pomieœci³a oko³o 150 znaków.
Podobnie proszê porozszerzaæ komórki w programie Excel, gdy¿ wpisane dane s¹ przewa¿nie za d³ugie.
*/

int main(void) {
	char tab51[51];
	setlocale(LC_ALL, "polish");

	std::cout << "Podaj nazwê studenta (max 50 znaków):" << std::endl;
	std::cin.get(tab51, 51);
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	Student student(tab51);
	student.rozpocznijPrace();

	return 0;
}