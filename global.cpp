#include "global.h"
#define MAXSPEED 12
#define MAXBUBBLE 8
#define MAXPOWER 6

// variables for global usage
const float FPS = 30.0;
const int WIDTH = 800;
const int HEIGHT = 600;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool judge_next_window = false;
double game_clock_start;
int game_clock = 166;
int tongX, tongY;
int bingX, bingY;
int tong_movespeed = 4;
int bing_movespeed = 6;
int tong_bombs_isplaced;
int tong_bombs_canplace = 1;
int bing_bombs_isplaced;
int bing_bombs_canplace = 2;
int bombT_power = 2;
int bombB_power = 1;
bool tong_have_needle = true;
bool bing_have_needle = true;
int block_barrier_map[17][15]; //0:nothing; 1:bomb; 2:weak block; 3:hard block
int block_bomb_map[17][15]; //0:nothing; 1:bomb; 2:explode
int block_explode_map[17][15]; //0: save; 1: fire!!!
int block_tool_map[17][15];
int game_results; //0: still playing; 1:draw; 2:tong win; 3:bing win;
int map_dir;

int XToBlock(int X)
{
    if(X-21<0) return 0;
    return (X-21)/40+1;
}

int YToBlock(int Y)
{
    if(Y-42<0) return 0;
    return (Y-42)/40+1;
}
