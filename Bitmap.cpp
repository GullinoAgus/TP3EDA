#include "Bitmap.h"


Bitmap::Bitmap(const char* directory = NULL)
{
	this->bitmap = al_load_bitmap(directory);
}