#include "tool.h"
#define NUMSHOE 12
#define NUMBUBL 12
#define NUMPWUP 12
#define NUMRDVL 1
#define NUMPWPL 1
#define NUMNEDL 2

enum {NONE = 0, SHOE, BUBL, PWUP, RDVL, PWPL, NEDL};

ALLEGRO_SAMPLE *sample_Tgetball = NULL;
ALLEGRO_SAMPLE_INSTANCE* tong_getball_Sound;

ALLEGRO_SAMPLE *sample_Tgetbig = NULL;
ALLEGRO_SAMPLE_INSTANCE* tong_getbig_Sound;

ALLEGRO_SAMPLE *sample_Tgetpower = NULL;
ALLEGRO_SAMPLE_INSTANCE* tong_getpower_Sound;

ALLEGRO_SAMPLE *sample_Tgetred = NULL;
ALLEGRO_SAMPLE_INSTANCE* tong_getred_Sound;

ALLEGRO_SAMPLE *sample_Tgetshoe = NULL;
ALLEGRO_SAMPLE_INSTANCE* tong_getshoe_Sound;

ALLEGRO_SAMPLE *sample_Tgetneedle = NULL;
ALLEGRO_SAMPLE_INSTANCE* tong_getneedle_Sound;

ALLEGRO_SAMPLE *sample_getT = NULL;
ALLEGRO_SAMPLE_INSTANCE* getT_Sound;

ALLEGRO_SAMPLE *sample_Bgetitem = NULL;
ALLEGRO_SAMPLE_INSTANCE* bing_getitem_Sound;

ALLEGRO_SAMPLE *sample_getB = NULL;
ALLEGRO_SAMPLE_INSTANCE* getB_Sound;

typedef struct NODE
{
    int bx, by;
    int state;
    ALLEGRO_BITMAP* TOOL;

}tool;

tool shoe[NUMSHOE];
tool bubl[NUMBUBL];
tool pwup[NUMPWUP];
tool rdvl[NUMRDVL];
tool pwpl[NUMPWPL];
tool nedl[NUMNEDL];

void tool_init()
{
    sample_Tgetball = al_load_sample("./sound/tong/tong_getball.mp3");
    tong_getball_Sound  = al_create_sample_instance(sample_Tgetball);
    al_set_sample_instance_playmode(tong_getball_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(tong_getball_Sound, al_get_default_mixer());

    sample_Tgetbig = al_load_sample("./sound/tong/tong_getbig.mp3");
    tong_getbig_Sound  = al_create_sample_instance(sample_Tgetbig);
    al_set_sample_instance_playmode(tong_getbig_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(tong_getbig_Sound, al_get_default_mixer());

    sample_Tgetpower = al_load_sample("./sound/tong/tong_getpower.mp3");
    tong_getpower_Sound  = al_create_sample_instance(sample_Tgetpower);
    al_set_sample_instance_playmode(tong_getpower_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(tong_getpower_Sound, al_get_default_mixer());

    sample_Tgetred = al_load_sample("./sound/tong/tong_getred.mp3");
    tong_getred_Sound  = al_create_sample_instance(sample_Tgetred);
    al_set_sample_instance_playmode(tong_getred_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(tong_getred_Sound, al_get_default_mixer());

    sample_Tgetshoe = al_load_sample("./sound/tong/tong_getshoe.mp3");
    tong_getshoe_Sound  = al_create_sample_instance(sample_Tgetshoe);
    al_set_sample_instance_playmode(tong_getshoe_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(tong_getshoe_Sound, al_get_default_mixer());

    sample_Tgetneedle = al_load_sample("./sound/tong/tong_getneedle.mp3");
    tong_getneedle_Sound  = al_create_sample_instance(sample_Tgetneedle);
    al_set_sample_instance_playmode(tong_getneedle_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(tong_getneedle_Sound, al_get_default_mixer());

    sample_Bgetitem = al_load_sample("./sound/bing/bing_getitem.mp3");
    bing_getitem_Sound  = al_create_sample_instance(sample_Bgetitem);
    al_set_sample_instance_playmode(bing_getitem_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(bing_getitem_Sound, al_get_default_mixer());

    sample_getT = al_load_sample("./sound/getitems.mp3");
    getT_Sound  = al_create_sample_instance(sample_getT);
    al_set_sample_instance_playmode(getT_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(getT_Sound, al_get_default_mixer());

    sample_getB = al_load_sample("./sound/getitems.mp3");
    getB_Sound  = al_create_sample_instance(sample_getB);
    al_set_sample_instance_playmode(getB_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(getB_Sound, al_get_default_mixer());

    srand(time(NULL));
    for(int i=0; i<NUMSHOE; i++){
        int tmpx = 2*((rand()%6)+1)+1; printf("shoe[%d] - tmpx: %d\n", i, tmpx);
        int tmpy = 2*((rand()%5)+1)+1; printf("shoe[%d] - tmpy: %d\n", i, tmpy);
        if(block_tool_map[tmpx][tmpy] != 0){
            i--;
            continue;
        }
        shoe[i].TOOL = al_load_bitmap("./pic/shoe.png");
        shoe[i].state = 1;
        shoe[i].bx = tmpx;
        shoe[i].by = tmpy;
        block_tool_map[tmpx][tmpy] = SHOE;
    }
    for(int i=0; i<NUMBUBL; i++){
        int tmpx = 2*((rand()%5)+1)+2; printf("bubl[%d] - tmpx: %d\n", i, tmpx);
        int tmpy = 2*((rand()%5)+1)+1; printf("bubl[%d] - tmpy: %d\n", i, tmpy);
        if(block_tool_map[tmpx][tmpy] != 0){
            i--;
            continue;
        }
        bubl[i].TOOL = al_load_bitmap("./pic/bubl.png");
        bubl[i].state = 1;
        bubl[i].bx = tmpx;
        bubl[i].by = tmpy;
        block_tool_map[tmpx][tmpy] = BUBL;
    }
    for(int i=0; i<NUMPWUP; i++){
        int tmpx = 2*((rand()%6)+1)+1; printf("pwup[%d] - tmpx: %d\n", i, tmpx);
        int tmpy = 2*((rand()%4)+1)+2; printf("pwup[%d] - tmpy: %d\n", i, tmpy);
        if(block_tool_map[tmpx][tmpy] != 0){
            i--;
            continue;
        }
        pwup[i].TOOL = al_load_bitmap("./pic/pwup.png");
        pwup[i].state = 1;
        pwup[i].bx = tmpx;
        pwup[i].by = tmpy;
        block_tool_map[tmpx][tmpy] = PWUP;
    }
    for(int i=0; i<NUMRDVL; i++){
        int tmpx = 2*((rand()%5)+1)+2; printf("%d - tmpx: %d\n", i, tmpx);
        int tmpy = 2*((rand()%4)+1)+2; printf("%d - tmpy: %d\n", i, tmpy);
        if(block_tool_map[tmpx][tmpy] != 0){
            i--;
            continue;
        }
        rdvl[i].TOOL = al_load_bitmap("./pic/rdvl.png");
        rdvl[i].state = 1;
        rdvl[i].bx = tmpx;
        rdvl[i].by = tmpy;
        block_tool_map[tmpx][tmpy] = RDVL;
    }
    for(int i=0; i<NUMPWPL; i++){
        int tmpx = 2*((rand()%5)+1)+2; printf("%d - tmpx: %d\n", i, tmpx);
        int tmpy = 2*((rand()%4)+1)+2; printf("%d - tmpy: %d\n", i, tmpy);
        if(block_tool_map[tmpx][tmpy] != 0){
            i--;
            continue;
        }
        pwpl[i].TOOL = al_load_bitmap("./pic/pwpl.png");
        pwpl[i].state = 1;
        pwpl[i].bx = tmpx;
        pwpl[i].by = tmpy;
        block_tool_map[tmpx][tmpy] = PWPL;
    }
    for(int i=0; i<NUMNEDL; i++){
        int tmpx = 2*((rand()%5)+1)+2; printf("%d - tmpx: %d\n", i, tmpx);
        int tmpy = 2*((rand()%4)+1)+2; printf("%d - tmpy: %d\n", i, tmpy);
        if(block_tool_map[tmpx][tmpy] != 0){
            i--;
            continue;
        }
        nedl[i].TOOL = al_load_bitmap("./pic/needle.png");
        nedl[i].state = 1;
        nedl[i].bx = tmpx;
        nedl[i].by = tmpy;
        block_tool_map[tmpx][tmpy] = NEDL;
    }

    block_tool_map[8][4] = 0;
    block_tool_map[8][5] = 0;
    block_tool_map[7][5] = 0;
    block_tool_map[9][4] = 0;
    for(int i=7; i<=9; i++){
        block_tool_map[i][6] = 0;
        block_tool_map[i][7] = 0;
    }
}

void tong_tool_update()
{
    int tongX_tmp = XToBlock(tongX);
    int tongY_tmp = YToBlock(tongY);

    if(block_tool_map[tongX_tmp][tongY_tmp] != 0)
        al_play_sample_instance(getT_Sound);

    if(block_tool_map[tongX_tmp][tongY_tmp] == SHOE){
        block_tool_map[tongX_tmp][tongY_tmp] = 0;
        al_play_sample_instance(tong_getshoe_Sound);
        if(tong_movespeed < MAXSPEED)
            tong_movespeed++;
    }
    else if(block_tool_map[tongX_tmp][tongY_tmp] == BUBL){
        block_tool_map[tongX_tmp][tongY_tmp] = 0;
        al_play_sample_instance(tong_getball_Sound);
        if(tong_bombs_canplace < bombT_power)
            tong_bombs_canplace++;
    }
    else if(block_tool_map[tongX_tmp][tongY_tmp] == PWUP){
        block_tool_map[tongX_tmp][tongY_tmp] = 0;
        al_play_sample_instance(tong_getpower_Sound);
        bombT_power++;
    }
    else if(block_tool_map[tongX_tmp][tongY_tmp] == RDVL){
        block_tool_map[tongX_tmp][tongY_tmp] = 0;
        al_play_sample_instance(tong_getred_Sound);
        tong_movespeed = MAXSPEED;
    }
    else if(block_tool_map[tongX_tmp][tongY_tmp] == PWPL){
        block_tool_map[tongX_tmp][tongY_tmp] = 0;
        al_play_sample_instance(tong_getbig_Sound);
        bombT_power = MAXPOWER;
    }
    else if(block_tool_map[tongX_tmp][tongY_tmp] == NEDL){
        block_tool_map[tongX_tmp][tongY_tmp] = 0;
        al_play_sample_instance(tong_getneedle_Sound);
        tong_have_needle = true;
    }
}

void bing_tool_update()
{
    int bingX_tmp = XToBlock(bingX);
    int bingY_tmp = YToBlock(bingY);

    if(block_tool_map[bingX_tmp][bingY_tmp] != 0){
        al_play_sample_instance(getB_Sound);
        al_play_sample_instance(bing_getitem_Sound);
    }
    if(block_tool_map[bingX_tmp][bingY_tmp] == SHOE){
        block_tool_map[bingX_tmp][bingY_tmp] = 0;
        if(bing_movespeed < MAXSPEED)
            bing_movespeed++;
    }
    else if(block_tool_map[bingX_tmp][bingY_tmp] == BUBL){
        block_tool_map[bingX_tmp][bingY_tmp] = 0;
        if(bing_bombs_canplace < MAXBUBBLE)
            bing_bombs_canplace++;
    }
    else if(block_tool_map[bingX_tmp][bingY_tmp] == PWUP){
        block_tool_map[bingX_tmp][bingY_tmp] = 0;
        bombB_power++;
    }
    else if(block_tool_map[bingX_tmp][bingY_tmp] == RDVL){
        block_tool_map[bingX_tmp][bingY_tmp] = 0;
        bing_movespeed = MAXSPEED;
    }
    else if(block_tool_map[bingX_tmp][bingY_tmp] == PWPL){
        block_tool_map[bingX_tmp][bingY_tmp] = 0;
        bombB_power = MAXPOWER;
    }
    else if(block_tool_map[bingX_tmp][bingY_tmp] == NEDL){
        block_tool_map[bingX_tmp][bingY_tmp] = 0;
        bing_have_needle = true;
    }
}

void tool_draw()
{
    for(int i=0; i<NUMSHOE; i++){
        if(shoe[i].state == 1 && block_tool_map[shoe[i].bx][shoe[i].by] == SHOE){
            al_draw_bitmap(shoe[i].TOOL, (shoe[i].bx-1)*40+21, (shoe[i].by-1)*40+42, 0);
            //al_draw_rectangle((shoe[i].bx-1)*40+21, (shoe[i].by-1)*40+42, (shoe[i].bx-1)*40+61, (shoe[i].by-1)*40+82, al_map_rgb(200, 50, 80), 0);
        }
    }
    for(int i=0; i<NUMBUBL; i++){
        if(bubl[i].state == 1 && block_tool_map[bubl[i].bx][bubl[i].by] == BUBL){
            al_draw_bitmap(bubl[i].TOOL, (bubl[i].bx-1)*40+21, (bubl[i].by-1)*40+42, 0);
            //al_draw_rectangle((bubl[i].bx-1)*40+21, (bubl[i].by-1)*40+42, (bubl[i].bx-1)*40+61, (bubl[i].by-1)*40+82, al_map_rgb(200, 200, 80), 0);
        }
    }
    for(int i=0; i<NUMPWUP; i++){
        if(pwup[i].state == 1 && block_tool_map[pwup[i].bx][pwup[i].by] == PWUP){
            al_draw_bitmap(pwup[i].TOOL, (pwup[i].bx-1)*40+22, (pwup[i].by-1)*40+43, 0);
            //al_draw_rectangle((pwup[i].bx-1)*40+21, (pwup[i].by-1)*40+42, (pwup[i].bx-1)*40+61, (pwup[i].by-1)*40+82, al_map_rgb(200, 20, 80), 0);
        }
    }
    for(int i=0; i<NUMRDVL; i++){
        if(rdvl[i].state == 1 && block_tool_map[rdvl[i].bx][rdvl[i].by] == RDVL){
            al_draw_bitmap(rdvl[i].TOOL, (rdvl[i].bx-1)*40+21, (rdvl[i].by-1)*40+42, 0);
            //al_draw_rectangle((rdvl[i].bx-1)*40+21, (rdvl[i].by-1)*40+42, (rdvl[i].bx-1)*40+61, (rdvl[i].by-1)*40+82, al_map_rgb(200, 20, 80), 0);
        }
    }
    for(int i=0; i<NUMPWPL; i++){
        if(pwpl[i].state == 1 && block_tool_map[pwpl[i].bx][pwpl[i].by] == PWPL){
            al_draw_bitmap(pwpl[i].TOOL, (pwpl[i].bx-1)*40+21, (pwpl[i].by-1)*40+42, 0);
            //al_draw_rectangle((pwpl[i].bx-1)*40+21, (pwpl[i].by-1)*40+42, (pwpl[i].bx-1)*40+61, (pwpl[i].by-1)*40+82, al_map_rgb(200, 20, 80), 0);
        }
    }
    for(int i=0; i<NUMNEDL; i++){
        if(nedl[i].state == 1 && block_tool_map[nedl[i].bx][nedl[i].by] == NEDL){
            al_draw_bitmap(nedl[i].TOOL, (nedl[i].bx-1)*40+15, (nedl[i].by-1)*40+37, 0);
        }
    }
}


void tool_destroy(){
    for(int i=0; i<NUMSHOE; i++) al_destroy_bitmap(shoe[i].TOOL);
    for(int i=0; i<NUMBUBL; i++) al_destroy_bitmap(bubl[i].TOOL);
    for(int i=0; i<NUMPWUP; i++) al_destroy_bitmap(pwup[i].TOOL);
    for(int i=0; i<NUMRDVL; i++) al_destroy_bitmap(rdvl[i].TOOL);
    for(int i=0; i<NUMPWPL; i++) al_destroy_bitmap(pwpl[i].TOOL);
    for(int i=0; i<NUMNEDL; i++) al_destroy_bitmap(nedl[i].TOOL);
}
