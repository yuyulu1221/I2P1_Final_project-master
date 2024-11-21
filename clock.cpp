#include "clock.h"
ALLEGRO_FONT *clock_font = NULL;

void game_clock_init(){
    clock_font = al_load_ttf_font("./font/pirulen.ttf",13,0);
    game_clock_start = al_get_time(); //gamestart time
}

void game_clock_update(){
    double game_clock_now = al_get_time();

    if((game_clock_now - game_clock_start) > 1){
        game_clock_start = game_clock_now;
        game_clock -= 1;
    }

    if(game_clock < 0) game_results = 1;
}

void game_clock_draw(){
    char temp[5];
    sprintf(temp, "%02d:%02d", game_clock/60, game_clock%60);
    if(game_clock/60 == 0 && game_clock%60<=30){
        al_draw_text(clock_font, al_map_rgb(255,0,0), WIDTH-60, 75, ALLEGRO_ALIGN_CENTRE, temp);
    }
    else{
        al_draw_text(clock_font, al_map_rgb(255,255,255), WIDTH-60, 75, ALLEGRO_ALIGN_CENTRE, temp);
    }
}
