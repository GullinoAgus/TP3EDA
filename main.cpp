#include <stdio.h>

int main()
{
	ALLEGRO_BITMAP* babyBlob = al_load_bitmap("Resources/babyblob.png");
	ALLEGRO_BITMAP* grownBlob = al_load_bitmap("Resources/grownblob.png");
	ALLEGRO_BITMAP* oldBlob = al_load_bitmap("Resources/goodoldblob.png");
	ALLEGRO_BITMAP* background = al_load_bitmap("Resources/background.jpg");
	ALLEGRO_BITMAP* food = al_load_bitmap("Resources/food.png");

	return 0;
}