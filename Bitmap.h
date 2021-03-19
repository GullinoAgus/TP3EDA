#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>


class Bitmap
{
public:
	unsigned int height;
	unsigned int width;
	ALLEGRO_BITMAP* bitmap;

	Bitmap(const char* directory);

};

