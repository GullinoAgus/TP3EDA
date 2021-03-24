#pragma once

#include "Position.h"
#include "Bitmap.h"

#define FOOD_TEXTURE ".\\Resources\\food.png"

class Food
{
public:
	Position pos;//Ubicacion (x y) en el mapa
	bool isNotEaten;//Para saber si esta comida o no "viva o muerta"
	const Bitmap *texture;//Textura

	Food();//Constructor y funciones asociadas a la inicailizacion y destruccion de la comida
	static void loadTexture();
	static void freeTextures();
};

