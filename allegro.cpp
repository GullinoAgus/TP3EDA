#include "allegro.h"

  ///////////////////////////////////////////////////////////////////////////////////////////////
 //    Inicializa Allegro y lo prepara para ser usado. Ajusta algunos parámetros de ImGui     //
///////////////////////////////////////////////////////////////////////////////////////////////
int initAllegro5(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue, ALLEGRO_TIMER*& timer) {

    if (!al_init()) {                   //Inicializacion del display y los addons de allegro
        return -1;
    }
    if (!al_init_font_addon()) {        //Inicializa las fuentes de las letras
        return -1;
    }
    if (!al_init_image_addon()) {       //Inicializa la sobre puesta de imagenes
        return -1;
    }
    if (!al_init_native_dialog_addon()) {   //Inicializa la sobrepuesta de dialogo nativa
        return -1;
    }
    if (!al_init_primitives_addon()) {      //Inicializa las primitivas de Allegro 5
        return -1;
    }
    if (!al_install_keyboard()) {           //Inicializa el teclado
        return -1;
    }
    if (!al_install_mouse()) {              //Inicializa el mouse
        return -1;
    }
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT); //Crea el display de allegro5
    if (display == NULL) {
        return -1;
    }
    al_set_new_display_flags(ALLEGRO_RESIZABLE);            //permite cambiar el tamaño de la ventana
    al_set_window_title(display, "Blob Simulator");         //nombra la ventana
    timer = al_create_timer(1.0 / FPS);                       //genera un temporizador 
    queue = al_create_event_queue();                        //genera cola de eventos
    // registra como entrada de eventos al dsiplay, teclado, mouse, y timer
    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    // Ajusta el contexto de Dear ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Ajusta el estilo de Dear ImGui 
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Ajusta "backends" de la Platform/Renderer 
    ImGui_ImplAllegro5_Init(display);

    return 0;

}



