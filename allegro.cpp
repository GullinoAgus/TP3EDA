#include "allegro.h"


int initAllegro5(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue) {


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
    if (!al_init_primitives_addon()) {
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
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    al_set_window_title(display, "Blob Simulator");
    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplAllegro5_Init(display);

    return 0;

}



