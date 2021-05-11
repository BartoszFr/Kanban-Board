#pragma once
#include "Kolumna.h"
#include <math.h>

class Done :
	public Kolumna
{
public:
	Done();
	void ilePrzedCzasem(int _nrZadania);
};