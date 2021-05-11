#include "Decyzja.h"
int intLepszyScanf(void) {
	int liczba;
	unsigned char a, wartoscLogiczna;
	while (1) {
		if (!scanf("%d", &liczba)) {
			printf("Spr�buj ponownie poda� liczb�: ");
			while ('\n' != getchar()) {}
		}
		else if ((a = getchar()) != '\n') {
			do {
				if (a == ' ' || a == '\t') {
					wartoscLogiczna = 1;
					a = getchar();
				}
				else
					wartoscLogiczna = 0;
			} while (wartoscLogiczna);
			if (a == '\n')
				return liczba;
			else {
				printf("Spr�buj ponownie poda� liczb�: ");
				while ('\n' != getchar()) {}
			}

		}
		else
			return liczba;
	}
}
//intLepszyStdCin na podstawie http://cpp0x.pl/kursy/Kurs-C++/Poziom-1/Obsluga-strumienia-wejsciowego/12
int intLepszyStdCin(void) {
	int odczyt;
	bool blad;
	std::cin >> odczyt;
	blad = std::cin.fail();//czy jest ustawiona flaga b��du
	while (blad == true) {
		std::cout << "Spr�buj ponownie." << std::endl;
		std::cin.clear();//usuwa flagi b��d�w, kt�re powoduj�, �e nic ju� nie b�dzie odczytane
		std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');//scanf(%[^\n]\n)
		std::cin >> odczyt;
		blad = std::cin.fail();
	}
	std::cin.ignore(std::numeric_limits < std::streamsize >::max(), '\n');//scanf(%[^\n]\n)
	return odczyt;
}
int podejmijDecyzje(int granica1, int granica2) {
	int decyzja;
	do {
		decyzja = intLepszyScanf();
		if (decyzja > granica2 || decyzja < granica1) {
			printf("Spr�buj jeszcze raz: ");
		}
	} while (decyzja > granica2 || decyzja < granica1);
	return decyzja;
}