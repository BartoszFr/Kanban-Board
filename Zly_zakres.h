#pragma once
#include <iostream>
#include <exception>
#include <string>
#include <sstream>

class Zly_zakres :
	public std::exception
{
private:
	int numer;
	int zakres;
	std::string tekst;
public:
	Zly_zakres(int _numer, int _koniec);
	const char* what() const noexcept override;
};

