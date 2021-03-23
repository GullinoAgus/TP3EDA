#include "allegro.h"


int initAllegro5(ALLEGRO_DISPLAY*& display) {


    if (!al_init()) {                   //Inicializacion del display y los addons de allegro
        return -1;
    }
    if (!al_init_font_addon()) {
        return -1;
    }
    if (!al_init_ttf_addon()) {
        return -1;
    }
    if (!al_init_image_addon()) {
        return -1;
    }
    if (!al_init_native_dialog_addon()) {
        return -1;
    }
    if (!al_install_keyboard()) {
        return -1;
    }
    if (!al_install_mouse()) {
        return -1;
    }
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (display == NULL) {
        return -1;
    }

    return 0;

}

void spritesInit() 
{


}
/*
void preGame(puntero a mode,puntero a blobs ammount)
{
    //antes de empezar la simulacion
    Begin("Blob World", &blob_world, ImGuiWindowFlags_MenuBar);
    //default bool mode = 1. mode1 = true, mode2 = false
    if (Button("Mode"))
    {
        mode ? false : true;
        if (mode)
            Text("Mode 1 selected");
        else
            Text("Mode 2 selected");
        Begin("Blob ammount.");
        if (Button("Increase Blob ammount"))
            blobsAmmount++;
        else if (Button("Decrease Blob ammount"))
            blobsAmmount--;
        Text("Blobs = %d", BlobsAmount);
        End();
        // despues de emp
    }
}

void gamePrint( puntero a los speeds,  probBILIDADES DE MUERTE, cantidad de comida )
{
ezar la simulacion

    Text("Maximum speed");
    SliderFloat("float", &MaxSpeed, 0.0f, 1.0f);//revisar &MaxSpeed
    Text("Speed percentage");
    SliderFloat("float", &PerSpeed, 0.0f, 1.0f);//revisar &PerSpeed
    Text("Smell radius");
    SliderFloat("float", &smellRadius, 0.0f, 1.0f);
    Text("Baby blob death probability");
    SliderFloat("float", &babyDeathProb, 0.0f, 1.0f);
    Text("Grown blob death probability");
    SliderFloat("float", &grownDeathProb, 0.0f, 1.0f);
    Text("Old blob death probability");
    SliderFloat("float", &oldDeathProb, 0.0f, 1.0f);


    Begin("Food count.");
    if (Button("Increase food count"))
        foodCount++;
    else if (Button("Decrease food count"))
        foodCount--;
    Text("Food count = %d", foodCount);
    End();
    //que es randomJiggleLimit?
    initAllegro5(display);//asumo
    printBlobs(puntero a la clase blob);
    printFood(puntero a Food)
}

void printBlobs(puntero a blobs)
{
    for (int i = 0; i < BLOBS_N; i++)
    {
        if (tipo de blob == baby)
            al_draw_bitmap(babyblob, blob[i].x, blob[i].y, 0);
        else if (tipo de blob == grown)
            al_draw_bitmap(grownblob, blob[i].x, blob[i].y, 0);
        else if (tipo de blob == old)
            al_draw_bitmap(oldblob, blob[i].x, blob[i].y, 0);
    }
}

void printFood(puntero a food)
{
    for()
}*/