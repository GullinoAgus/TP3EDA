#include "Food.h"

static const Bitmap foodText(FOOD_TEXTURE);

Food::Food()
{
	this->texture = &foodText;
	this->isNotEaten = 0;
	this->pos;
}