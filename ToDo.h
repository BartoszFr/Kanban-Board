#pragma once
#include <iostream>
#include <string.h>
#include "Kolumna.h"

class ToDo :
	public Kolumna
{
public:
	ToDo();
	void przypomnij(int _nrZadania);
};