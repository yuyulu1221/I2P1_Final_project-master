#include "scene.h"

ALLEGRO_FONT *font = NULL;
ALLEGRO_BITMAP *background = NULL;
ALLEGRO_BITMAP *needle = NULL;

ALLEGRO_BITMAP *rule = NULL;
ALLEGRO_SAMPLE *song=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_instance;

ALLEGRO_BITMAP *choosemap = NULL;
ALLEGRO_BITMAP *arrow = NULL;
ALLEGRO_SAMPLE *floatby=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_floatby_instance;
ALLEGRO_SAMPLE *wait=NULL;
ALLEGRO_SAMPLE_INSTANCE *sample_wait_instance;

int menu_dir;
// function of menu
void menu_init(){
    menu_dir = 0;
    font = al_load_ttf_font("./font/VarelaRound-Regular.ttf",20,0);
    background = al_load_bitmap("./pic/login1.png");
    rule = al_load_bitmap("./pic/RULE.png");
    // Load sound
    song = al_load_sample("./sound/login.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 1) ;
    al_play_sample_instance(sample_instance);
}
void menu_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A){
            if(menu_dir > -1)
                menu_dir--;
        }
        if( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D){
            if(menu_dir < 1)
                menu_dir++;
        }
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ){
            if(menu_dir == 0)
                judge_next_window = true;
            if(menu_dir == 1)
                game_results = -1;

        }
    }
    /*
    if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        if( ( (WIDTH/2 - 50) < event.mouse.x < (WIDTH/2 +50) ) && (560 < event.mouse.y < 590))
            judge_next_window = true;
    }
    */
}
void menu_draw(){
    //al_clear_to_color(al_map_rgb(100,100,100));
    al_draw_bitmap(background, 0, 0, 0);
    //al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2+220 , ALLEGRO_ALIGN_CENTRE, "Press 'Enter' to start");
    //al_draw_rectangle(WIDTH/2-150, 510, WIDTH/2+150, 550, al_map_rgb(255, 255, 255), 0);
    al_draw_filled_rectangle(WIDTH/2-48, 558, WIDTH/2+52, 588, al_map_rgb(26, 163, 241));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2, 563, ALLEGRO_ALIGN_CENTRE, "START");
    al_draw_filled_rectangle(WIDTH/2-158, 558, WIDTH/2-58, 588, al_map_rgb(26, 163, 241));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2-110, 563, ALLEGRO_ALIGN_CENTRE, "RULE");
    al_draw_filled_rectangle(WIDTH/2+60, 558, WIDTH/2+160, 588, al_map_rgb(26, 163, 241));
    al_draw_text(font, al_map_rgb(255,255,255), WIDTH/2+110, 563, ALLEGRO_ALIGN_CENTRE, "QUIT");

    if(menu_dir == -1){
        al_draw_bitmap(rule, 0, 50, 0);
        al_draw_rectangle(WIDTH/2-160, 555, WIDTH/2-56, 590, al_map_rgb(250, 50, 50), 5);
    }
    if(menu_dir == 0)
        al_draw_rectangle(WIDTH/2-50, 555, WIDTH/2+54, 590, al_map_rgb(250, 50, 50), 5);
    if(menu_dir == 1)
        al_draw_rectangle(WIDTH/2+58, 555, WIDTH/2+162, 590, al_map_rgb(250, 50, 50), 5);
}
void menu_destroy(){
    al_destroy_font(font);
    al_destroy_bitmap(background);
    al_destroy_sample_instance(sample_instance);
    al_destroy_bitmap(rule);
}

void choosemap_init(){
    map_dir = 0;
    choosemap = al_load_bitmap("./pic/choosemap.png");
    arrow = al_load_bitmap("./pic/arrow.png");
    floatby = al_load_sample("./sound/mousefloatby.mp3");
    sample_floatby_instance  = al_create_sample_instance(floatby);
    al_set_sample_instance_playmode(sample_floatby_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(sample_floatby_instance, al_get_default_mixer());
    wait = al_load_sample("./sound/wait.mp3");
    sample_wait_instance  = al_create_sample_instance(wait);
    al_set_sample_instance_playmode(sample_wait_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(sample_wait_instance, al_get_default_mixer());
    al_play_sample_instance(sample_wait_instance);
}
void choosemap_process(ALLEGRO_EVENT event){
    if( event.type == ALLEGRO_EVENT_KEY_UP ){
        if( event.keyboard.keycode == ALLEGRO_KEY_LEFT || event.keyboard.keycode == ALLEGRO_KEY_A){
            al_play_sample_instance(sample_floatby_instance);
            if(map_dir > 0)
                map_dir--;
        }
        if( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_D){
            al_play_sample_instance(sample_floatby_instance);
            if(map_dir < 1)
                map_dir++;
        }
        if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ){
            judge_next_window = true;
        }
    }
}

void choosemap_draw(){
    al_draw_bitmap(choosemap, 0, 0, 0);
    if(map_dir == 0) al_draw_bitmap(arrow, 200, 50, 0);
    else al_draw_bitmap(arrow, 600, 50, 0);

}

void choosemap_destroy(){
    al_destroy_bitmap(choosemap);
    al_destroy_bitmap(arrow);
    al_destroy_sample(floatby);
    al_destroy_sample_instance(sample_floatby_instance);
    al_destroy_sample(wait);
    al_destroy_sample_instance(sample_wait_instance);
}


// function of game_scene
void game_scene_init(){
    game_clock_init();
    character_init();
    bomb_init();
    barrier_init();
    tool_init();

    if(map_dir == 0) background = al_load_bitmap("./pic/map.png");
    else background = al_load_bitmap("./pic/village/blank.png");
    needle = al_load_bitmap("./pic/needle_big.png");
    // Load sound
    song = al_load_sample("./sound/BGM.mp3");
    al_reserve_samples(20);
    sample_instance = al_create_sample_instance(song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(sample_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(sample_instance, 1) ;
    al_play_sample_instance(sample_instance);
}

void game_scene_draw(){
    al_draw_bitmap(background, 0, 0, 0);
    if(tong_have_needle == true) al_draw_bitmap(needle, 660, 475, 0);
    if(bing_have_needle == true) al_draw_bitmap(needle, 725, 475, 0);
    //al_draw_rectangle(21, 42, 621, 562, al_map_rgb(250,220,120), 0); //find the edge
    al_flip_display();
}
void game_scene_destroy(){

    character_destory();
    bomb_destroy();
    barrier_destroy();
    tool_destroy();

    //al_destroy_font(font);
    al_destroy_bitmap(background);
    //al_destroy_bitmap(rule);
    //al_destroy_bitmap(battlefield);
    //al_destroy_sample(song);
    al_destroy_sample_instance(sample_instance);
}
