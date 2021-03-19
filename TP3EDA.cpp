// TP3EDA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "World.h"

using namespace std;


int main()
{

    ALLEGRO_DISPLAY* display;

    if (initAllegro5(display) == -1)
    {
        return 0;
    }

    Bitmap textGOb(GOBTEXTURE);
    Bitmap textGb(GBTEXTURE);
    Bitmap textBb(BBTEXTURE);
    Bitmap textFood(FOODTEXTURE);
    Bitmap textWorld(WORLDTEXTURE);
    if (textGOb.bitmap == NULL || textGb.bitmap == NULL || textBb.bitmap == NULL || textFood.bitmap == NULL || textWorld.bitmap == NULL)
    {
        al_destroy_display(display);
        return 0;
    }

    EtaryGroup goodOldBlob(GOODOLDBLOB, &textGOb);
    EtaryGroup grownBlob(GROWNBLOB, &textGb);
    EtaryGroup babyBlob(BABYBLOB, &textBb);

    World world(&textWorld);
    world.initBlobList(&babyBlob);
    world.initFoodList(&textFood);


    /*TESTEO*/
    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(textWorld.bitmap, 0, 0, 0);
    al_draw_bitmap(textGOb.bitmap, 0, 0, 0);
    al_draw_bitmap(textGb.bitmap, textGOb.width, 0, 0);
    al_draw_bitmap(textBb.bitmap, textGb.width + textGOb.width, 0, 0);
    al_draw_bitmap(textFood.bitmap, textBb.width + textGOb.width + textGb.width, 0, 0);
    al_flip_display();
    while (1);

    al_destroy_display(display);
    return 0;
}
