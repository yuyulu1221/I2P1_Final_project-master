#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#define GAME_TERMINATE -1
#define MAXSPEED 15
#define MAXBUBBLE 7
#define MAXPOWER 6
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// note that you can't assign initial value here!
extern const float FPS;
extern const int WIDTH;
extern const int HEIGHT;
extern bool key_state[ALLEGRO_KEY_MAX];
extern bool judge_next_window;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *fps;
extern double game_clock_start;
extern int game_clock;
extern int tongX, tongY;
extern int bingX, bingY;
extern int tong_movespeed;
extern int bing_movespeed;
extern bool tong_have_needle;
extern bool bing_have_needle;
extern int tong_bombs_isplaced;
extern int tong_bombs_canplace;
extern int bing_bombs_isplaced;
extern int bing_bombs_canplace;
extern int bombT_power;
extern int bombB_power;
//extern int barrier_map[1000][800];
extern int block_barrier_map[17][15];
extern int block_bomb_map[17][15];
extern int block_explode_map[17][15];
extern int block_tool_map[17][15];
extern int game_results;
extern int map_dir;

#endif

int XToBlock(int);
int YToBlock(int);
