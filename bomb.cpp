#include "bomb.h"
#define HUGENUM 99999

ALLEGRO_BITMAP *MID1 = NULL;
ALLEGRO_BITMAP *MID2 = NULL;
ALLEGRO_BITMAP *WATER1_2 = NULL;
ALLEGRO_BITMAP *WATER1_1 = NULL;
ALLEGRO_BITMAP *LAST1 = NULL;
ALLEGRO_BITMAP *LAST2 = NULL;

ALLEGRO_BITMAP *WATER1_2_90 = NULL;
ALLEGRO_BITMAP *WATER1_1_90 = NULL;
ALLEGRO_BITMAP *LAST1_90 = NULL;
ALLEGRO_BITMAP *LAST2_90 = NULL;

ALLEGRO_SAMPLE *sample_put = NULL;
ALLEGRO_SAMPLE_INSTANCE *putballT_Sound;
ALLEGRO_SAMPLE_INSTANCE *putballB_Sound;

ALLEGRO_SAMPLE *sample_boom = NULL;

int Ti, Bi;

typedef struct NODE
{
    int x, y; //the position of image
    int bx, by;
    int width, height; // the width and height of image
    int state; // the state of bomb
    double place_time;
    double explo_time;
    double explo_end_time;
    ALLEGRO_BITMAP *BALL;
    ALLEGRO_SAMPLE_INSTANCE *explode_Sound;
    int anime; // counting the time of animation
    int anime_time; // indicate how long the animation
    int stop[4];
    int stop_len[4];
}bomb;

bomb bombT[MAXBUBBLE];
bomb bombB[MAXBUBBLE];


void bomb_init()
{
    sample_boom = al_load_sample("./sound/boom.mp3");
    for(int i=0; i<MAXBUBBLE; i++){
        bombT[i].explode_Sound = al_create_sample_instance(sample_boom);
        al_set_sample_instance_playmode(bombT[i].explode_Sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(bombT[i].explode_Sound, al_get_default_mixer());
    }
    for(int i=0; i<MAXBUBBLE; i++){
        bombB[i].explode_Sound = al_create_sample_instance(sample_boom);
        al_set_sample_instance_playmode(bombB[i].explode_Sound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(bombB[i].explode_Sound, al_get_default_mixer());
    }


    sample_put = al_load_sample("./sound/putball.mp3");
    putballT_Sound  = al_create_sample_instance(sample_put);
    al_set_sample_instance_playmode(putballT_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(putballT_Sound, al_get_default_mixer());
    putballB_Sound  = al_create_sample_instance(sample_put);
    al_set_sample_instance_playmode(putballB_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(putballB_Sound, al_get_default_mixer());


    MID1 = al_load_bitmap("./pic/water/mid1.png");
    MID2 = al_load_bitmap("./pic/water/mid2.png");
    WATER1_1 = al_load_bitmap("./pic/water/water1_1.png");
    WATER1_2 = al_load_bitmap("./pic/water/water1_2.png");
    /*WATER2 = al_load_bitmap("./pic/water/water2.png");
    WATER3 = al_load_bitmap("./pic/water/water3.png");
    WATER4 = al_load_bitmap("./pic/water/water4.png");
    WATER4 = al_load_bitmap("./pic/water/water5.png");
    WATER6 = al_load_bitmap("./pic/water/water6.png");*/
    LAST1 = al_load_bitmap("./pic/water/last1.png");
    LAST2 = al_load_bitmap("./pic/water/last2.png");

    WATER1_1_90 = al_load_bitmap("./pic/water/90/water1_1.png");
    WATER1_2_90 = al_load_bitmap("./pic/water/90/water1_2.png");
    /*WATER2_90 = al_load_bitmap("./pic/water/90/water2.png");
    WATER3_90 = al_load_bitmap("./pic/water/90/water3.png");
    WATER4_90 = al_load_bitmap("./pic/water/90/water4.png");
    WATER4_90 = al_load_bitmap("./pic/water/90/water5.png");
    WATER6_90 = al_load_bitmap("./pic/water/90/water6.png");*/
    LAST1_90 = al_load_bitmap("./pic/water/90/last1.png");
    LAST2_90 = al_load_bitmap("./pic/water/90/last2.png");

    for(int i=0; i<MAXBUBBLE; i++){
        bombT[i].BALL = al_load_bitmap("./pic/ball.png");
        bombT[i].state = 0;
    }
    for(int i=0; i<MAXBUBBLE; i++){
        bombB[i].BALL = al_load_bitmap("./pic/ball.png");
        bombB[i].state = 0;
    }
}

void tong_bomb_place()
{
    Ti %= tong_bombs_canplace;
    if(tong_bombs_isplaced < tong_bombs_canplace){
        if(bombT[Ti].state == 0 && block_barrier_map[XToBlock(tongX)][YToBlock(tongY)] == 0)
        {
            bombT[Ti].bx = XToBlock(tongX);
            bombT[Ti].by = YToBlock(tongY);
            bombT[Ti].place_time = al_get_time();
            bombT[Ti].x = (bombT[Ti].bx-1)*40+41;
            bombT[Ti].y = (bombT[Ti].by-1)*40+62;
            bombT[Ti].state = 1;
            tong_bombs_isplaced++;
            block_bomb_map[bombT[Ti].bx][bombT[Ti].by] = 1;
            block_barrier_map[bombT[Ti].bx][bombT[Ti].by] = 1;
            al_play_sample_instance(putballT_Sound);
            Ti++;
        }
    }
}

void bing_bomb_place()
{
    Bi %= bing_bombs_canplace;
    if(bing_bombs_isplaced < bing_bombs_canplace){
        if(bombB[Bi].state == 0 && block_barrier_map[XToBlock(bingX)][YToBlock(bingY)] == 0)
        {
            bombB[Bi].bx = XToBlock(bingX);
            bombB[Bi].by = YToBlock(bingY);
            bombB[Bi].place_time = al_get_time();
            bombB[Bi].x = (bombB[Bi].bx-1)*40+41;
            bombB[Bi].y = (bombB[Bi].by-1)*40+62;
            bombB[Bi].state = 1;
            bing_bombs_isplaced++;
            block_bomb_map[bombB[Bi].bx][bombB[Bi].by] = 1;
            block_barrier_map[bombB[Bi].bx][bombB[Bi].by] = 1;
            al_play_sample_instance(putballB_Sound);
            Bi++;
        }

    }
}
void bomb_update()
{


    for(int i=0; i<MAXBUBBLE; i++){
        if(bombT[i].state == 1) bombT[i].explo_time = al_get_time();
        if(bombT[i].explo_time - bombT[i].place_time >= 3 || block_bomb_map[bombT[i].bx][bombT[i].by] == 2) //chain explosion
        {
            //bombT[i] explode
            tong_bombs_isplaced--;
            printf("(%d)BombExplo[%d][%d]\n", i, bombT[i].bx, bombT[i].by);
            bombT[i].state = 2;
            al_play_sample_instance(bombT[i].explode_Sound);
            bombT[i].place_time = bombT[i].explo_time;// avoid original bomb loop again
            block_barrier_map[bombT[i].bx][bombT[i].by] = 0;
            block_bomb_map[bombT[i].bx][bombT[i].by] = 0;
            block_explode_map[bombT[i].bx][bombT[i].by] += 1;
            for(int p=1; p<=bombT_power; p++){
                if(!(bombT[i].stop[0])){//before arriving the end
                    int bombT_x_add = bombT[i].bx+p;
                    if(block_barrier_map[bombT_x_add][bombT[i].by] <= 1){
                        block_explode_map[bombT_x_add][bombT[i].by] += 1;
                        if(block_tool_map[bombT_x_add][bombT[i].by] != 0)
                            block_tool_map[bombT_x_add][bombT[i].by] = 0;//elliminate tools
                        if(block_bomb_map[bombT_x_add][bombT[i].by] == 1)
                            block_bomb_map[bombT_x_add][bombT[i].by] = 2;
                    }
                    else if(block_barrier_map[bombT_x_add][bombT[i].by] == 2){
                        block_barrier_map[bombT_x_add][bombT[i].by] = 0;
                        bombT[i].stop[0] = 1;
                    }
                    else{
                        bombT[i].stop[0] = 1;
                    }

                    if(!(bombT[i].stop[0])) bombT[i].stop_len[0] = p;
                    else bombT[i].stop_len[0] = p-1;
                }
                if(!bombT[i].stop[1]){
                    int bombT_x_min = bombT[i].bx-p;
                    if(block_barrier_map[bombT_x_min][bombT[i].by] <= 1){
                        block_explode_map[bombT_x_min][bombT[i].by] += 1;
                        if(block_tool_map[bombT_x_min][bombT[i].by] != 0)
                            block_tool_map[bombT_x_min][bombT[i].by] = 0;
                        if(block_bomb_map[bombT_x_min][bombT[i].by] == 1){
                            block_bomb_map[bombT_x_min][bombT[i].by] = 2;
                        }
                    }
                    else if(block_barrier_map[bombT_x_min][bombT[i].by] == 2){
                        block_barrier_map[bombT_x_min][bombT[i].by] = 0;
                        bombT[i].stop[1] = 1;
                    }
                    else bombT[i].stop[1] = 1;
                    if(!(bombT[i].stop[1])) bombT[i].stop_len[1] = p;
                    else bombT[i].stop_len[1] = p-1;
                }
                if(!bombT[i].stop[2]){
                    int bombT_y_add = bombT[i].by+p;
                    if(block_barrier_map[bombT[i].bx][bombT_y_add] <= 1){
                        block_explode_map[bombT[i].bx][bombT_y_add] += 1;
                        if(block_tool_map[bombT[i].bx][bombT_y_add] != 0)
                            block_tool_map[bombT[i].bx][bombT_y_add] = 0;
                        if(block_bomb_map[bombT[i].bx][bombT_y_add] == 1){
                            block_bomb_map[bombT[i].bx][bombT_y_add] = 2;
                        }
                    }
                    else if(block_barrier_map[bombT[i].bx][bombT_y_add] == 2){
                        block_barrier_map[bombT[i].bx][bombT_y_add] = 0;
                        bombT[i].stop[2] = 1;
                    }
                    else bombT[i].stop[2] = 1;
                    if(!(bombT[i].stop[2])) bombT[i].stop_len[2] = p;
                    else bombT[i].stop_len[2] = p-1;
                }
                if(!bombT[i].stop[3]){
                    int bombT_y_min = bombT[i].by-p;
                    if(block_barrier_map[bombT[i].bx][bombT_y_min] <= 1){
                        block_explode_map[bombT[i].bx][bombT_y_min] += 1;
                        if(block_tool_map[bombT[i].bx][bombT_y_min] != 0)
                            block_tool_map[bombT[i].bx][bombT_y_min] = 0;
                        if(block_bomb_map[bombT[i].bx][bombT_y_min] == 1){
                            block_bomb_map[bombT[i].bx][bombT_y_min] = 2;
                        }
                    }
                    else if(block_barrier_map[bombT[i].bx][bombT_y_min] == 2){
                        block_barrier_map[bombT[i].bx][bombT_y_min] = 0;
                        bombT[i].stop[3] = 1;
                    }
                    else bombT[i].stop[3] = 1;
                    if(!(bombT[i].stop[3])) bombT[i].stop_len[3] = p;
                    else bombT[i].stop_len[3] = p-1;
                }
            }
        }
        if(bombT[i].state == 2) bombT[i].explo_end_time = al_get_time();//bomb 1 sec
        if(bombT[i].explo_end_time - bombT[i].explo_time >= 1){
            bombT[i].explo_time = bombT[i].explo_end_time;
            bombT[i].state = 0;
            for(int j=0; j<4; j++) bombT[i].stop[j] = 0;
            block_explode_map[bombT[i].bx][bombT[i].by] -= 1;
            for(int p=0; p<=bombT_power; p++){
                if(p<=bombT[i].stop_len[0]){
                    block_explode_map[bombT[i].bx+p][bombT[i].by] -= 1;
                }
                if(p<=bombT[i].stop_len[1]){
                    block_explode_map[bombT[i].bx-p][bombT[i].by] -= 1;
                }
                if(p<=bombT[i].stop_len[2]){
                    block_explode_map[bombT[i].bx][bombT[i].by+p] -= 1;
                }
                if(p<=bombT[i].stop_len[3]){
                    block_explode_map[bombT[i].bx][bombT[i].by-p] -= 1;
                }
            }
        }
    }

    for(int i=0; i<MAXBUBBLE; i++){
        if(bombB[i].state == 1) bombB[i].explo_time = al_get_time();
        if(bombB[i].explo_time - bombB[i].place_time >= 3 || block_bomb_map[bombB[i].bx][bombB[i].by] == 2) //chain explosion
        {
            //bombB[i] explode
            printf("(%d)BombExplo[%d][%d]\n", i, bombB[i].bx, bombB[i].by);
            bombB[i].state = 2;
            bombB[i].anime = 0;
            al_play_sample_instance(bombB[i].explode_Sound);
            bombB[i].place_time = bombB[i].explo_time;
            block_barrier_map[bombB[i].bx][bombB[i].by] = 0;
            block_bomb_map[bombB[i].bx][bombB[i].by] = 0;
            bing_bombs_isplaced--;
            block_explode_map[bombB[i].bx][bombB[i].by] += 1;
            for(int p=1; p<=bombB_power; p++){
                if(!(bombB[i].stop[0])){
                    int bombB_x_add = bombB[i].bx+p;
                    if(block_barrier_map[bombB_x_add][bombB[i].by] <= 1){
                        block_explode_map[bombB_x_add][bombB[i].by] += 1;
                        if(block_tool_map[bombB_x_add][bombB[i].by] != 0)
                            block_tool_map[bombB_x_add][bombB[i].by] = 0;
                        if(block_bomb_map[bombB_x_add][bombB[i].by] == 1){
                            block_bomb_map[bombB_x_add][bombB[i].by] = 2;
                        }
                    }
                    else if(block_barrier_map[bombB_x_add][bombB[i].by] == 2){
                        block_barrier_map[bombB_x_add][bombB[i].by] = 0;
                        bombB[i].stop[0] = 1;
                    }
                    else
                        bombB[i].stop[0] = 1;
                    if(!(bombB[i].stop[0])) bombB[i].stop_len[0] = p;
                    else bombB[i].stop_len[0] = p-1;
                }
                if(!bombB[i].stop[1]){
                    int bombB_x_min = bombB[i].bx-p;
                    if(block_barrier_map[bombB_x_min][bombB[i].by] <= 1){
                        block_explode_map[bombB_x_min][bombB[i].by] += 1;
                        if(block_tool_map[bombB_x_min][bombB[i].by] != 0)
                            block_tool_map[bombB_x_min][bombB[i].by] = 0;
                        if(block_bomb_map[bombB_x_min][bombB[i].by] == 1){
                            block_bomb_map[bombB_x_min][bombB[i].by] = 2;
                        }
                    }
                    else if(block_barrier_map[bombB_x_min][bombB[i].by] == 2){
                        block_barrier_map[bombB_x_min][bombB[i].by] = 0;
                        bombB[i].stop[1] = 1;
                    }
                    else bombB[i].stop[1] = 1;
                    if(!(bombB[i].stop[1])) bombB[i].stop_len[1] = p;
                    else bombB[i].stop_len[1] = p-1;
                }
                if(!bombB[i].stop[2]){
                    int bombB_y_add = bombB[i].by+p;
                    if(block_barrier_map[bombB[i].bx][bombB_y_add] <= 1){
                        block_explode_map[bombB[i].bx][bombB_y_add] += 1;
                        if(block_tool_map[bombB[i].bx][bombB_y_add] != 0)
                            block_tool_map[bombB[i].bx][bombB_y_add] = 0;
                        if(block_bomb_map[bombB[i].bx][bombB_y_add] == 1){
                            block_bomb_map[bombB[i].bx][bombB_y_add] = 2;
                        }
                    }
                    else if(block_barrier_map[bombB[i].bx][bombB_y_add] == 2){
                        block_barrier_map[bombB[i].bx][bombB_y_add] = 0;
                        bombB[i].stop[2] = 1;
                    }
                    else bombB[i].stop[2] = 1;
                    if(!(bombB[i].stop[2])) bombB[i].stop_len[2] = p;
                    else bombB[i].stop_len[2] = p-1;
                }
                if(!bombB[i].stop[3]){
                    int bombB_y_min = bombB[i].by-p;
                    if(block_barrier_map[bombB[i].bx][bombB_y_min] <= 1){
                        block_explode_map[bombB[i].bx][bombB_y_min] += 1;
                        if(block_tool_map[bombB[i].bx][bombB_y_min] != 0)
                            block_tool_map[bombB[i].bx][bombB_y_min] = 0;
                        if(block_bomb_map[bombB[i].bx][bombB_y_min] == 1){
                            block_bomb_map[bombB[i].bx][bombB_y_min] = 2;
                        }
                    }
                    else if(block_barrier_map[bombB[i].bx][bombB_y_min] == 2){
                        block_barrier_map[bombB[i].bx][bombB_y_min] = 0;
                        bombB[i].stop[3] = 1;
                    }
                    else bombB[i].stop[3] = 1;
                    if(!(bombB[i].stop[3])) bombB[i].stop_len[3] = p;
                    else bombB[i].stop_len[3] = p-1;
                }
            }
        }
        if(bombB[i].state == 2) bombB[i].explo_end_time = al_get_time();
        if(bombB[i].explo_end_time - bombB[i].explo_time >= 1){
            bombB[i].explo_time = bombB[i].explo_end_time;
            bombB[i].state = 0;
            for(int j=0; j<4; j++) bombB[i].stop[j] = 0;
            block_explode_map[bombB[i].bx][bombB[i].by] -= 1;
            for(int p=1; p<=bombB_power; p++){
                if(p<=bombB[i].stop_len[0]){
                    block_explode_map[bombB[i].bx+p][bombB[i].by] -= 1;
                }
                if(p<=bombB[i].stop_len[1]){
                    block_explode_map[bombB[i].bx-p][bombB[i].by] -= 1;
                }
                if(p<=bombB[i].stop_len[2]){
                    block_explode_map[bombB[i].bx][bombB[i].by+p] -= 1;
                }
                if(p<=bombB[i].stop_len[3]){
                    block_explode_map[bombB[i].bx][bombB[i].by-p] -= 1;
                }
            }
        }
    }
}



void water_draw(){
    bomb *B;
    for(int i=0; i<MAXBUBBLE; i++){//test canplace
        for(int j=0; j<2; j++){
            if(j==0) B = bombB+i;
            else if(j==1) B = bombT+i;


            if(B->state == 2){

                int bomb_x = (B->bx);
                int bomb_y = (B->by);

                int waterspout = (B->anime)%2;



                B->bx += B->stop_len[0];
                if(waterspout == 1) al_draw_bitmap(LAST1_90, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_HORIZONTAL);
                else al_draw_bitmap(LAST2_90, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_HORIZONTAL);
                B->bx--;
                while(B->bx > bomb_x){
                    if(waterspout == 1){
                    al_draw_bitmap(WATER1_1_90, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_HORIZONTAL);
                    }else{
                    al_draw_bitmap(WATER1_2_90, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_HORIZONTAL);
                    }
                    B->bx--;
                }
                B->bx = bomb_x;

                B->bx -= B->stop_len[1];
                if(waterspout == 1) al_draw_bitmap(LAST1_90, B->bx*40-19, B->by*40+2, 0);
                else al_draw_bitmap(LAST2_90, B->bx*40-19, B->by*40+2, 0);
                B->bx++;
                while(B->bx < bomb_x){
                    if(waterspout == 1){
                    al_draw_bitmap(WATER1_1_90, B->bx*40-19, B->by*40+2, 0);
                    }else{
                    al_draw_bitmap(WATER1_2_90, B->bx*40-19, B->by*40+2, 0);
                    }
                    B->bx++;
                }
                B->bx = bomb_x;

                B->by += B->stop_len[2];
                if(waterspout == 1) al_draw_bitmap(LAST1, B->bx*40-19, B->by*40+2, 0);
                else al_draw_bitmap(LAST2, B->bx*40-19, B->by*40+2, 0);
                B->by--;
                while(B->by > bomb_y){
                    if(waterspout == 1){
                    al_draw_bitmap(WATER1_1, B->bx*40-19, B->by*40+2, 0);
                    }else{
                    al_draw_bitmap(WATER1_2, B->bx*40-19, B->by*40+2, 0);
                    }
                    B->by--;
                }
                B->by = bomb_y;

                B->by -= B->stop_len[3];
                if(waterspout == 1) al_draw_bitmap(LAST1, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_VERTICAL);
                else al_draw_bitmap(LAST2, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_VERTICAL);
                B->by++;
                while(B->by < bomb_y){
                    if(waterspout == 1){
                    al_draw_bitmap(WATER1_1, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_VERTICAL);
                    }else{
                    al_draw_bitmap(WATER1_2, B->bx*40-19, B->by*40+2, ALLEGRO_FLIP_VERTICAL);
                    }
                    B->by++;
                }
                B->by = bomb_y;



                if(waterspout == 1){
                    al_draw_bitmap(MID1, B->bx*40-19, B->by*40+2, 0);
                }else{
                    al_draw_bitmap(MID2, B->bx*40-19, B->by*40+2, 0);
                }

            }

        }
    }
}
void water_process(ALLEGRO_EVENT event){
    for(int i=0; i<MAXBUBBLE; i++){
        if(bombT[i].state == 2)
        if( event.type == ALLEGRO_EVENT_TIMER ){
            if( event.timer.source == fps ){
                bombT[i].anime++;
                bombT[i].anime %= 31;

            }
        }
        //bombT[i].anime = 0;
    }
    for(int i=0; i<MAXBUBBLE; i++){
        if(bombB[i].state == 2)
        if( event.type == ALLEGRO_EVENT_TIMER ){
            if( event.timer.source == fps ){
                bombB[i].anime++;
                bombB[i].anime %= 31;

            }
        }
        //bombB[i].anime = 0;
    }
}
void bomb_draw()
{
    for(int i=0; i<MAXBUBBLE; i++){
        if(bombT[i].state == 1){
            al_draw_bitmap(bombT[i].BALL, bombT[i].x-22, bombT[i].y-25, 0);
            //al_draw_rectangle(bombT[i].x-20, bombT[i].y-20, bombT[i].x+20, bombT[i].y+20, al_map_rgb(20, 150, 20), 0);
        }
        if(bombB[i].state == 1){
            al_draw_bitmap(bombB[i].BALL, bombB[i].x-22, bombB[i].y-25, 0);
            //al_draw_rectangle(bombB[i].x-20, bombB[i].y-20, bombB[i].x+20, bombB[i].y+20, al_map_rgb(150, 20, 20), 0);
        }
    }

}

void bomb_destroy()
{
    for(int i=0; i<MAXBUBBLE; i++){
        al_destroy_bitmap(bombT[i].BALL);
    }
    for(int i=0; i<MAXBUBBLE; i++){
        al_destroy_bitmap(bombB[i].BALL);
    }
    al_destroy_bitmap(MID1);
    al_destroy_bitmap(MID2);
    al_destroy_bitmap(WATER1_1);
    al_destroy_bitmap(WATER1_2);
    al_destroy_bitmap(LAST1);
    al_destroy_bitmap(LAST2);

    al_destroy_bitmap(WATER1_1_90);
    al_destroy_bitmap(WATER1_2_90);
    al_destroy_bitmap(LAST1_90);
    al_destroy_bitmap(LAST2_90);


}
