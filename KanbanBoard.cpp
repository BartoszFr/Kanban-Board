#define _CRT_SECURE_NO_WARNINGS
#include "Student.h"
#include <vld.h>

/*
Mechanizmy:
1. Operatory:
	- Zadanie

2. Zarządzanie pamięcią:
	- Zadanie
	- Student

3. Wyjątki:
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

Przykładowe dane do wczytania znajdują się pod nazwą "plik.csv".

Podczas pracy programu proszę rozszerzyć okno konsoli tak, aby pomieściła około 150 znaków.
Podobnie proszę porozszerzać komórki w programie Excel, gdyż wpisane dane są przeważnie zbyt długie.
*/

int main(void) {
	char tab51[51];
	setlocale(LC_ALL, "polish");

	std::cout << "Podaj nazwę studenta (max 50 znaków):" << std::endl;
	std::cin.get(tab51, 51);
	std::cin.ignore(std::numeric_limits <std::streamsize>::max(), '\n');
	Student student(tab51);
	student.rozpocznijPrace();

	return 0;
}
