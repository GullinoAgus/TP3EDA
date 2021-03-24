// TP3EDA.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "World.h"


using namespace std;



int main(int argc, char **argv)
{
    srand(time(NULL));

    bool simStarted = false;
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* queue;
    ALLEGRO_EVENT ev;
    ALLEGRO_TIMER* timer;
    initAllegro5(display, queue, timer);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    
    World world;
    // Main loop
    bool running = true;
    al_start_timer(timer);
    while (running)
    {
       
        while (al_get_next_event(queue, &ev))
        {
            ImGui_ImplAllegro5_ProcessEvent(&ev);
            switch (ev.type)
            {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                ImGui_ImplAllegro5_InvalidateDeviceObjects();
                al_acknowledge_resize(display);
                ImGui_ImplAllegro5_CreateDeviceObjects();
                break;
            case ALLEGRO_EVENT_TIMER:
                
                if (!simStarted)
                {
                    simStarted = world.preGame();
                    if (simStarted)
                    {
                        world.initBlobs();
                        world.initFood();
                    }
                }
                else
                {
                    world.Simulation();
                    world.gamePrint();
                }
                break;
            default:
                break;
            }

        }

        
        // Rendering

    }

    // Cleanup

    al_destroy_bitmap(world.texture.bitmap);
    Blob::freeTextures();
    Food::freeTextures();
    al_destroy_event_queue(queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    ImGui_ImplAllegro5_Shutdown();
    ImGui::DestroyContext();
    return 0;
}
