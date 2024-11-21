#include "global.h"
#include "charater.h"
#include "clock.h"
#include "bomb.h"
#include "barrier.h"
#include "tool.h"

void menu_init();
void menu_process(ALLEGRO_EVENT event);
void menu_draw();
void menu_destroy();

void choosemap_init();
void choosemap_process(ALLEGRO_EVENT event);
void choosemap_draw();
void choosemap_destroy();

void game_scene_init();
void game_scene_draw();
void game_scene_destroy();
