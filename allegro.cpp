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
    if (!al_init_primitives_addon()) {
        return -1;
    }
    if (!al_install_keyboard()) {
        return -1;
    }
    if (!al_install_mouse()) {
        return -1;
    }
    al_set_new_display_flags(ALLEGRO_RESIZABLE);
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    if (display == NULL) {
        return -1;
    }

    return 0;

}



