// TP3EDA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "World.h"

using namespace std;


int main()
{

    ALLEGRO_DISPLAY* display;

    srand(time(NULL));

    if (initAllegro5(display) == -1)
    {
        return 0;
    }


    /*TESTEO*/
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_flip_display();
    while (1);

    al_destroy_display(display);
    return 0;
}
