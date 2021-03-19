#pragma once

#include "Position.h"
#include "Bitmap.h"

class Food
{
public:
	Position pos;
	Bitmap *texture;
	Food* next;

	Food(Bitmap* texture = NULL);
	void destroy(Food *&listaFood);

};

