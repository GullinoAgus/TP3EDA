#include "Food.h"

static Bitmap foodText;

Food::Food()
{
	this->texture = &foodText;
	this->isNotEaten = 0;
	this->pos;
}

void Food::loadTexture() 
{
	foodText = Bitmap(FOOD_TEXTURE);
}

void Food::freeTextures()
{
	al_destroy_bitmap(foodText.bitmap);
}