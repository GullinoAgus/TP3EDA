#pragma once

#include "Position.h"
#include "Bitmap.h"

#define FOOD_TEXTURE ".\\Resources\\food.png"

class Food
{
public:
	Position pos;
	bool isNotEaten;
	const Bitmap *texture;

	Food();
	static void loadTexture();
	static void freeTextures();
};

