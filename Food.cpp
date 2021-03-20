#include "Food.h"

static const Bitmap foodText(FOOD_TEXTURE);

Food::Food()
{
	this->texture = &foodText;
	this->isEaten = 0;
	this->pos = { 0, 0, 0 };
}