#include "charater.h"

// the state of character
enum {STOP = 0, MOVE, ATK, PLACE, DEAD, STUCK};
typedef struct NODE
{
    int x, y; // the position of image
    int width, height; // the width and height of image
    int dir; // 0: down, 1: left, 2: up, 3: right
    int state; // the state of character
    int movespeed;
    ALLEGRO_BITMAP *img_move[4];
}Character;

Character tong, bing;
ALLEGRO_BITMAP *stuck_tong = NULL;
ALLEGRO_BITMAP *stuck_bing = NULL;

ALLEGRO_SAMPLE *useneedleT = NULL;
ALLEGRO_SAMPLE_INSTANCE *useneedleT_instance = NULL;
ALLEGRO_SAMPLE *useneedleB = NULL;
ALLEGRO_SAMPLE_INSTANCE *useneedleB_instance = NULL;

ALLEGRO_SAMPLE *bubblein = NULL;
ALLEGRO_SAMPLE_INSTANCE *bubbleinT_instance = NULL;
ALLEGRO_SAMPLE_INSTANCE *bubbleinB_instance = NULL;

ALLEGRO_SAMPLE *bubbleout = NULL;
ALLEGRO_SAMPLE_INSTANCE *bubbleoutT_instance = NULL;
ALLEGRO_SAMPLE_INSTANCE *bubbleoutB_instance = NULL;

double space_press;
double enter_press;
double tong_stuck_time;
double bing_stuck_time;

void character_init(){

    // load effective sound
    useneedleT = al_load_sample("./sound/tong/tong_useneedle.mp3");
    useneedleT_instance  = al_create_sample_instance(useneedleT);
    al_set_sample_instance_playmode(useneedleT_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(useneedleT_instance, al_get_default_mixer());

    useneedleB = al_load_sample("./sound/bing/bing_useneedle.mp3");
    useneedleB_instance  = al_create_sample_instance(useneedleB);
    al_set_sample_instance_playmode(useneedleB_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(useneedleB_instance, al_get_default_mixer());

    bubblein= al_load_sample("./sound/bubblein.wav");
    bubbleinT_instance  = al_create_sample_instance(bubblein);
    al_set_sample_instance_playmode(bubbleinT_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(bubbleinT_instance, al_get_default_mixer());
    bubbleinB_instance  = al_create_sample_instance(bubblein);
    al_set_sample_instance_playmode(bubbleinB_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(bubbleinB_instance, al_get_default_mixer());

    bubbleout = al_load_sample("./sound/bubbleout.wav");
    bubbleoutT_instance  = al_create_sample_instance(bubbleout);
    al_set_sample_instance_playmode(bubbleoutT_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(bubbleoutT_instance, al_get_default_mixer());
    bubbleoutB_instance  = al_create_sample_instance(bubbleout);
    al_set_sample_instance_playmode(bubbleoutB_instance, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(bubbleoutB_instance, al_get_default_mixer());

    // load character images
    for(int i = 1 ; i <= 4 ; i++){
        char temp[50];
        sprintf( temp, "./pic/c1.1_move%d.png", i );
        tong.img_move[i-1] = al_load_bitmap(temp);
    }
    stuck_tong = al_load_bitmap("./pic/stuck_tong.png");


    // initial the geometric information of character
    tong.state = MOVE;
    tong.width = al_get_bitmap_width(tong.img_move[0]);
    tong.height = al_get_bitmap_height(tong.img_move[0]);
    tong.x = 42;
    tong.y = 63;
    tong.dir = 0;
    tong.movespeed = tong_movespeed;


    // load character images
    for(int i = 1 ; i <= 4 ; i++){
        char temp[50];
        sprintf( temp, "./pic/c2.1_move%d.png", i );
        bing.img_move[i-1] = al_load_bitmap(temp);
    }
    stuck_bing = al_load_bitmap("./pic/stuck_bing.png");

    // initial the geometric information of character 2
    bing.state = MOVE;
    bing.width = al_get_bitmap_width(bing.img_move[0]);
    bing.height = al_get_bitmap_height(bing.img_move[0]);
    bing.x = 602;
    bing.y = 544;
    bing.dir = 0;
    bing.movespeed = bing_movespeed;
}

void charater_process(ALLEGRO_EVENT event){
    // process the keyboard event
    if( event.type == ALLEGRO_EVENT_KEY_DOWN ){
        key_state[event.keyboard.keycode] = true;

    }else if( event.type == ALLEGRO_EVENT_KEY_UP ){
        key_state[event.keyboard.keycode] = false;
    }
}
void character_update(){

    //Globalize Tong's location
    tongX = tong.x;
    tongY = tong.y;

    //Globalize Bing's location
    bingX = bing.x;
    bingY = bing.y;

    int XToBlock_tongX = XToBlock(tongX);
    int YToBlock_tongY = YToBlock(tongY);
    int XToBlock_bingX = XToBlock(bingX);
    int YToBlock_bingY = YToBlock(bingY);

    //Get tool -> Enhance properties
    if(tong.state == MOVE) tong_tool_update();
    if(bing.state == MOVE) bing_tool_update();

    //Whether get in the bubble or not
    if(block_explode_map[XToBlock_tongX][YToBlock_tongY] > 0 && tong.state == MOVE){
        al_play_sample_instance(bubbleinT_instance);
        tong.state = STUCK;
        tong.movespeed = 1;
        tong_stuck_time = al_get_time();
    }
    if(block_explode_map[XToBlock_bingX][YToBlock_bingY] > 0 && bing.state == MOVE){
        al_play_sample_instance(bubbleinB_instance);
        bing.state = STUCK;
        bing.movespeed = 1;
        bing_stuck_time = al_get_time();
    }

    //Whether bubble die or not
    if(tong.state == STUCK){
        int now_time = al_get_time();
        if(now_time - tong_stuck_time >= 6)
            tong.state = DEAD;
        if(bing.state == MOVE)
            if(XToBlock_tongX == XToBlock_bingX && YToBlock_tongY == YToBlock_bingY)
                tong.state = DEAD;
    }
    if(bing.state == STUCK){
        int now_time = al_get_time();
        if(now_time - bing_stuck_time >= 6)
            bing.state = DEAD;
        if(tong.state == MOVE)
            if(XToBlock_tongX == XToBlock_bingX && YToBlock_tongY == YToBlock_bingY)
                bing.state = DEAD;
    }

    //Decide ending video
    if(tong.state == DEAD && bing.state == DEAD){
        game_results = 1;
        printf("DRAW\n");
        return;
    }
    else if(bing.state == DEAD){
        game_results = 2;
        printf("Tong win!!\n");
        return;
    }
    else if(tong.state == DEAD){
        game_results = 3;
        printf("Bing win!!\n");
        return;
    }

    //Tong move
    if(tong.state == MOVE) tong.movespeed = tong_movespeed;
    if(key_state[ALLEGRO_KEY_W]){
        tong.dir = 2;
        int Tong_nextstep = YToBlock(tong.y-21);
        for(int i=0; i<tong.movespeed; i++){
            if(block_barrier_map[XToBlock_tongX][Tong_nextstep] == 0){//next step exist or not
                if(block_barrier_map[XToBlock(tong.x+19)][Tong_nextstep] > 0) //right front exist or not
                    tong.x -= 1;
                else if(block_barrier_map[XToBlock(tong.x-19)][Tong_nextstep] > 0) //left front exist or not
                    tong.x += 1;
                else
                    tong.y -= 1;
            }else if(block_bomb_map[XToBlock_tongX][Tong_nextstep] == 1 //nextstep(21) on bomb
                    && block_bomb_map[XToBlock_tongX][YToBlock_tongY] == 1 //on bomb
                    && Tong_nextstep == YToBlock_tongY) // and they are the same bomb
                tong.y -= 1;
            else break;
        }

    }else if(key_state[ALLEGRO_KEY_A]){
        tong.dir = 1;
        int Tong_nextstep = XToBlock(tong.x-21);
        for(int i=0; i<tong.movespeed; i++){
            if(block_barrier_map[Tong_nextstep][YToBlock_tongY] == 0){
                if(block_barrier_map[Tong_nextstep][YToBlock(tong.y-19)] > 0)
                    tong.y += 1;
                else if(block_barrier_map[Tong_nextstep][YToBlock(tong.y+19)] > 0)
                    tong.y -= 1;
                else
                    tong.x -= 1;
            }else if(block_bomb_map[Tong_nextstep][YToBlock_tongY] == 1
                    && block_bomb_map[XToBlock_tongX][YToBlock_tongY] == 1
                    && Tong_nextstep == XToBlock_tongX)
                tong.x -= 1;
            else break;
        }

    }else if(key_state[ALLEGRO_KEY_S]){
        tong.dir = 0;
        int Tong_nextstep = YToBlock(tong.y+21);
        for(int i=0; i<tong.movespeed; i++){
            if(block_barrier_map[XToBlock_tongX][Tong_nextstep] == 0){
                if(block_barrier_map[XToBlock(tong.x+19)][Tong_nextstep] > 0)
                    tong.x -= 1;
                else if(block_barrier_map[XToBlock(tong.x-19)][Tong_nextstep] > 0)
                    tong.x += 1;
                else
                    tong.y += 1;
            }else if(block_bomb_map[XToBlock_tongX][Tong_nextstep] == 1
                    && block_bomb_map[XToBlock_tongX][YToBlock_tongY] == 1
                    && Tong_nextstep == YToBlock_tongY)
                tong.y += 1;
            else break;
        }

    }else if(key_state[ALLEGRO_KEY_D]){
        tong.dir = 3;
        int Tong_nextstep = XToBlock(tong.x+21);
        for(int i=0; i<tong.movespeed; i++){
            if(block_barrier_map[Tong_nextstep][YToBlock_tongY] == 0){
                if(block_barrier_map[Tong_nextstep][YToBlock(tong.y+19)] > 0)
                    tong.y -= 1;
                else if(block_barrier_map[Tong_nextstep][YToBlock(tong.y-19)] > 0)
                    tong.y += 1;
                else
                    tong.x += 1;
            }else if(block_bomb_map[Tong_nextstep][YToBlock_tongY] == 1
                    && block_bomb_map[XToBlock_tongX][YToBlock_tongY] == 1
                    && Tong_nextstep == XToBlock_tongX)
                tong.x += 1;
            else break;
        }
    }

    //Tong place bomb
    if(key_state[ALLEGRO_KEY_SPACE] && tong.state!=STUCK){
        tong_bomb_place();
    }

    //Tong use needle
    if(key_state[ALLEGRO_KEY_V] && tong.state == STUCK && tong_have_needle){
        al_play_sample_instance(useneedleT_instance);
        al_play_sample_instance(bubbleoutT_instance);
        tong.state = MOVE;
        tong_have_needle = false;
    }

    //Bing move
    if(bing.state == MOVE) bing.movespeed = bing_movespeed;
    if(key_state[ALLEGRO_KEY_UP] ){
        bing.dir = 2;
        int Bing_nextstep = YToBlock(bing.y-21);
        for(int i=0; i<bing.movespeed; i++){
            if(block_barrier_map[XToBlock_bingX][Bing_nextstep] == 0){
                if(block_barrier_map[XToBlock(bing.x+19)][Bing_nextstep] > 0)
                    bing.x -= 1;
                else if(block_barrier_map[XToBlock(bing.x-19)][Bing_nextstep] > 0)
                    bing.x += 1;
                else
                    bing.y -= 1;
            }else if(block_bomb_map[XToBlock_bingX][Bing_nextstep] == 1
                    && block_bomb_map[XToBlock_bingX][YToBlock_bingY] == 1
                    && Bing_nextstep == YToBlock_bingY)
                bing.y -= 1;
            else break;
        }

    }else if(key_state[ALLEGRO_KEY_LEFT] ){
        bing.dir = 1;
        int Bing_nextstep = XToBlock(bing.x-21);
        for(int i=0; i<bing.movespeed; i++){
            if(block_barrier_map[Bing_nextstep][YToBlock_bingY] == 0){
                if(block_barrier_map[Bing_nextstep][YToBlock(bing.y-19)] > 0)
                    bing.y += 1;
                else if(block_barrier_map[Bing_nextstep][YToBlock(bing.y+19)] > 0)
                    bing.y -= 1;
                else
                    bing.x -= 1;
            }else if(block_bomb_map[Bing_nextstep][YToBlock_bingY] == 1
                    && block_bomb_map[XToBlock_bingX][YToBlock_bingY] == 1
                    && Bing_nextstep == XToBlock_bingX)
                bing.x -= 1;
            else break;
        }

    }else if(key_state[ALLEGRO_KEY_DOWN] ){
        bing.dir = 0;
        int Bing_nextstep = YToBlock(bing.y+21);
        for(int i=0; i<bing.movespeed; i++){
            if(block_barrier_map[XToBlock_bingX][Bing_nextstep] == 0){
                if(block_barrier_map[XToBlock(bing.x+19)][Bing_nextstep] > 0)
                    bing.x -= 1;
                else if(block_barrier_map[XToBlock(bing.x-19)][Bing_nextstep] > 0)
                    bing.x += 1;
                else
                    bing.y += 1;
            }else if(block_bomb_map[XToBlock_bingX][Bing_nextstep] == 1
                    && block_bomb_map[XToBlock_bingX][YToBlock_bingY] == 1
                    && Bing_nextstep == YToBlock_bingY)
                bing.y += 1;
            else break;
        }

    }else if(key_state[ALLEGRO_KEY_RIGHT] ){
        bing.dir = 3;
        int Bing_nextstep = XToBlock(bing.x+21);
        for(int i=0; i<bing.movespeed; i++){
            if(block_barrier_map[Bing_nextstep][YToBlock_bingY] == 0){
                if(block_barrier_map[Bing_nextstep][YToBlock(bing.y+19)] > 0)
                    bing.y -= 1;
                else if(block_barrier_map[Bing_nextstep][YToBlock(bing.y-19)] > 0)
                    bing.y += 1;
                else
                    bing.x += 1;
            }else if(block_bomb_map[Bing_nextstep][YToBlock_bingY] == 1
                    && block_bomb_map[XToBlock_bingX][YToBlock_bingY] == 1
                    && Bing_nextstep == XToBlock_bingX)
                bing.x += 1;
            else break;
        }
    }

    //Bing place bomb
    if(key_state[ALLEGRO_KEY_SLASH] && bing.state!=STUCK){
        bing_bomb_place();
    }
    //Bing use needle
    if(key_state[ALLEGRO_KEY_SEMICOLON] && bing.state == STUCK && bing_have_needle){
        al_play_sample_instance(useneedleB_instance);
        al_play_sample_instance(bubbleoutB_instance);
        bing.state = MOVE;
        bing_have_needle = false;
    }
}


void character_draw_map1(){
    int XToBlock_tongX = XToBlock(tongX);
    int YToBlock_tongY = YToBlock(tongY);
    int XToBlock_bingX = XToBlock(bingX);
    int YToBlock_bingY = YToBlock(bingY);
    // with the state, draw corresponding image
    if(tong.state == MOVE){

        if( tong.dir == 0)
            al_draw_bitmap(tong.img_move[0], tong.x-34, tong.y-75, 0);
        else if( tong.dir == 1)
            al_draw_bitmap(tong.img_move[1], tong.x-34, tong.y-75, 0);
        else if( tong.dir == 2)
            al_draw_bitmap(tong.img_move[2], tong.x-34, tong.y-75, 0);
        else if( tong.dir == 3)
            al_draw_bitmap(tong.img_move[3], tong.x-34, tong.y-75, 0);
        //al_draw_rectangle(tong.x-1, tong.y-1, tong.x+1, tong.y+1, al_map_rgb(0, 0, 100), 0);

    }

    if(tong.state == STUCK)
        al_draw_bitmap(stuck_tong, tong.x-60, tong.y-95, 0);


    if( bing.state == MOVE){

        if( bing.dir == 0)
            al_draw_bitmap(bing.img_move[0], bing.x-34, bing.y-75, 0);
        else if( bing.dir == 1)
            al_draw_bitmap(bing.img_move[1], bing.x-34, bing.y-75, 0);
        else if( bing.dir == 2)
            al_draw_bitmap(bing.img_move[2], bing.x-34, bing.y-75, 0);
        else if( bing.dir == 3)
            al_draw_bitmap(bing.img_move[3], bing.x-34, bing.y-75, 0);
        //al_draw_rectangle(bing.x-1, bing.y-1, bing.x+1, bing.y+1, al_map_rgb(10, 0, 100), 0);

    }

    if(bing.state == STUCK)
        al_draw_bitmap(stuck_bing, bing.x-60, bing.y-95, 0);
}

void character_draw_map2(){
    int XToBlock_tongX = XToBlock(tongX);
    int YToBlock_tongY = YToBlock(tongY);
    int XToBlock_bingX = XToBlock(bingX);
    int YToBlock_bingY = YToBlock(bingY);
    // with the state, draw corresponding image
    if(tong.state == MOVE){

        if(XToBlock_tongX == 6 || XToBlock_tongX == 10){
        }else if((XToBlock_tongX <=6 || XToBlock_tongX >= 9)&& YToBlock_tongY == 7){
        }else{

            if( tong.dir == 0)
                al_draw_bitmap(tong.img_move[0], tong.x-34, tong.y-75, 0);
            else if( tong.dir == 1)
                al_draw_bitmap(tong.img_move[1], tong.x-34, tong.y-75, 0);
            else if( tong.dir == 2)
                al_draw_bitmap(tong.img_move[2], tong.x-34, tong.y-75, 0);
            else if( tong.dir == 3)
                al_draw_bitmap(tong.img_move[3], tong.x-34, tong.y-75, 0);
            //al_draw_rectangle(tong.x-1, tong.y-1, tong.x+1, tong.y+1, al_map_rgb(0, 0, 100), 0);
        }

    }

    if(tong.state == STUCK)
        al_draw_bitmap(stuck_tong, tong.x-60, tong.y-95, 0);


    if( bing.state == MOVE){

        if(XToBlock_bingX == 6 || XToBlock_bingX == 10){
        }else if((XToBlock_bingX <=6 || XToBlock_bingX >= 9)&& YToBlock_bingY == 7){
        }else{
            if( bing.dir == 0)
                al_draw_bitmap(bing.img_move[0], bing.x-34, bing.y-75, 0);
            else if( bing.dir == 1)
                al_draw_bitmap(bing.img_move[1], bing.x-34, bing.y-75, 0);
            else if( bing.dir == 2)
                al_draw_bitmap(bing.img_move[2], bing.x-34, bing.y-75, 0);
            else if( bing.dir == 3)
                al_draw_bitmap(bing.img_move[3], bing.x-34, bing.y-75, 0);
            //al_draw_rectangle(bing.x-1, bing.y-1, bing.x+1, bing.y+1, al_map_rgb(10, 0, 100), 0);
        }
    }

    if(bing.state == STUCK)
        al_draw_bitmap(stuck_bing, bing.x-60, bing.y-95, 0);
}

void character_destory(){

    al_destroy_bitmap(tong.img_move[0]);
    al_destroy_bitmap(tong.img_move[1]);
    al_destroy_bitmap(tong.img_move[2]);
    al_destroy_bitmap(tong.img_move[3]);
    al_destroy_bitmap(stuck_tong);



    al_destroy_bitmap(bing.img_move[0]);
    al_destroy_bitmap(bing.img_move[1]);
    al_destroy_bitmap(bing.img_move[2]);
    al_destroy_bitmap(bing.img_move[3]);
    al_destroy_bitmap(stuck_bing);


    al_destroy_sample(useneedleT);
    al_destroy_sample_instance(useneedleT_instance);
    al_destroy_sample(useneedleB);
    al_destroy_sample_instance(useneedleB_instance);

    al_destroy_sample(bubblein);
    al_destroy_sample(bubbleout);

    al_destroy_sample_instance(bubbleinT_instance);
    al_destroy_sample_instance(bubbleinB_instance);
    al_destroy_sample_instance(bubbleoutT_instance);
    al_destroy_sample_instance(bubbleoutB_instance);

}
