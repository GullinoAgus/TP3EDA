#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "imgui.h"
#include "imconfig.h"
#include "imgui_impl_allegro5.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"



#define FPS 60.0

#define DISPLAY_WIDTH 900
#define DISPLAY_HEIGHT 650

int initAllegro5(ALLEGRO_DISPLAY*& display, ALLEGRO_EVENT_QUEUE*& queue, ALLEGRO_TIMER*& timer);
