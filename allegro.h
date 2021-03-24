#pragma once

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include "imgui.h"
#include "imconfig.h"
#include "imgui_impl_allegro5.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"






#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

int initAllegro5(ALLEGRO_DISPLAY*& display);
