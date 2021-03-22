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

void preGame(puntero a mode,puntero a blobs ammount)
{
    //antes de empezar la simulacion
    ImGui::Begin("Blob World", &blob_world, ImGuiWindowFlags_MenuBar);
    //default bool mode = 1. mode1 = true, mode2 = false
    if (ImGui::Button("Mode"))
    {
        mode ? false : true;
        if (mode)
            ImGui::Text("Mode 1 selected");
        else
            ImGui::Text("Mode 2 selected");
        ImGui::Begin("Blob ammount.");
        if (ImGui::Button("Increase Blob ammount"))
            blobsAmmount++;
        else if (ImGui::Button("Decrease Blob ammount"))
            blobsAmmount--;
        ImGui::Text("Blobs = %d", BlobsAmount);
        ImGui::End();
        // despues de emp
    }
}

void gamePrint( puntero a los speeds,  probBILIDADES DE MUERTE, cantidad de comida )
{
ezar la simulacion

    ImGui::Text("Maximum speed");
    ImGui::SliderFloat("float", &MaxSpeed, 0.0f, 1.0f);//revisar &MaxSpeed
    ImGui::Text("Speed percentage");
    ImGui::SliderFloat("float", &PerSpeed, 0.0f, 1.0f);//revisar &PerSpeed
    ImGui::Text("Smell radius");
    ImGui::SliderFloat("float", &smellRadius, 0.0f, 1.0f);
    ImGui::Text("Baby blob death probability");
    ImGui::SliderFloat("float", &babyDeathProb, 0.0f, 1.0f);
    ImGui::Text("Grown blob death probability");
    ImGui::SliderFloat("float", &grownDeathProb, 0.0f, 1.0f);
    ImGui::Text("Old blob death probability");
    ImGui::SliderFloat("float", &oldDeathProb, 0.0f, 1.0f);


    ImGui::Begin("Food count.");
    if (ImGui::Button("Increase food count"))
        foodCount++;
    else if (ImGui::Button("Decrease food count"))
        foodCount--;
    ImGui::Text("Food count = %d", foodCount);
    ImGui::End();
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
}