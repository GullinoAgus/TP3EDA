#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>


#define WORLDTEXTURE ".\\Resources\\background.jpg"
#define GOBTEXTURE ".\\Resources\\goodoldblob.png"
#define GBTEXTURE ".\\Resources\\grownblob.png"
#define BBTEXTURE ".\\Resources\\babyblob.png"
#define FOODTEXTURE ".\\Resources\\food.png"

#define DISPLAYWIDTH 1280
#define DISPLAYHEIGHT 720

int initAllegro5(ALLEGRO_DISPLAY*& display);
