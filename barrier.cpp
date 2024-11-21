#include "barrier.h"
ALLEGRO_BITMAP *box1 = NULL;
ALLEGRO_BITMAP *box2 = NULL;
ALLEGRO_BITMAP *box3 = NULL;

ALLEGRO_BITMAP *vbox = NULL;
ALLEGRO_BITMAP *vbox_y = NULL;
ALLEGRO_BITMAP *vbox_r = NULL;
ALLEGRO_BITMAP *vbarrier_b = NULL;
ALLEGRO_BITMAP *vbarrier_o = NULL;
ALLEGRO_BITMAP *vbarrier_r = NULL;
ALLEGRO_BITMAP *vbarrier_y = NULL;
ALLEGRO_BITMAP *tree = NULL;
ALLEGRO_BITMAP *bush = NULL;
void barrier_init()
{
    if(map_dir == 0){
        box1 = al_load_bitmap("./pic/box1.png");
        box2 = al_load_bitmap("./pic/box2.png");
        box3 = al_load_bitmap("./pic/box3.png");
    }else{
        vbox = al_load_bitmap("./pic/village/box.png");
        vbox_y = al_load_bitmap("./pic/village/block_yellow.png");
        vbox_r = al_load_bitmap("./pic/village/block_red.png");
        vbarrier_b = al_load_bitmap("./pic/village/house_blue.png");
        vbarrier_o = al_load_bitmap("./pic/village/house_orange.png");
        vbarrier_r = al_load_bitmap("./pic/village/house_red.png");
        vbarrier_y = al_load_bitmap("./pic/village/house_yellow.png");
        tree = al_load_bitmap("./pic/village/tree.png");
        bush = al_load_bitmap("./pic/village/bush.png");
    }

    if(map_dir == 0){//map1
        for(int i=0; i<14; i++){
            block_barrier_map[0][i] = 3;
            block_barrier_map[16][i] = 3;
        }
        for(int i=0; i<16; i++){
            block_barrier_map[i][0] = 3;
            block_barrier_map[i][14] = 3;
        }
        block_barrier_map[2][2] = 3;
        block_barrier_map[2][12] = 3;
        block_barrier_map[14][2] = 3;
        block_barrier_map[14][12] = 3;

        srand(time(NULL));
        for(int i=0; i<=30; i++){
            int px = (rand()%7)+5;
            int py = (rand()%7)+4;
            block_barrier_map[px][py] = 2;
        }


        for(int i=4; i<=13; i++) block_barrier_map[1][i] = 2;
        block_barrier_map[2][3] = 2;
        block_barrier_map[2][8] = 2;
        block_barrier_map[2][9] = 2;
        block_barrier_map[2][10] = 2;

        block_barrier_map[3][1] = 2;
        block_barrier_map[3][2] = 2;
        for(int i=4; i<=10; i++) block_barrier_map[3][i] = 2;
        for(int i=5; i<=11; i++) block_barrier_map[i][2] = 2;
        for(int i=3; i<=12; i++) block_barrier_map[i][13] = 2;
        for(int i=3; i<=5; i++) block_barrier_map[i][12] = 2;
        for(int i=9; i<=11; i++) block_barrier_map[i][12] = 2;
        for(int i=1; i<=11; i++) block_barrier_map[15][i] = 2;
        for(int i=7; i<=9; i++) block_barrier_map[i][6] = 3;
        for(int i=7; i<=9; i++) block_barrier_map[i][7] = 3;
        block_barrier_map[8][4] = 0;
        block_barrier_map[8][5] = 0;
        block_barrier_map[6][6] = 0;
        block_barrier_map[6][10] = 0;
        block_barrier_map[7][5] = 0;
        block_barrier_map[9][4] = 0;
        for(int i=3; i<=10; i++) block_barrier_map[14][i] = 2;
        for(int i=5; i<=8; i++) block_barrier_map[13][i] = 2;
        for(int i=2; i<=10; i++) block_barrier_map[12][i] = 2;
        for(int i=4; i<=13; i++) block_barrier_map[i][12] = 2;
        block_barrier_map[8][1] = 2;
        for(int i=7; i<=9; i++) block_barrier_map[i][3] = 2;
        for(int i=7; i<=9; i++) block_barrier_map[i][11] = 2;
        for(int i=7; i<=10; i++) block_barrier_map[4][i] = 2;

    }else if(map_dir == 1){//map2

        for(int i=1; i<=5; i++){ //horizontal
            for(int j=1; j<=3; j++){
                block_barrier_map[i][j*2-1] = 2;
                block_barrier_map[16-i][j*2] = 2;
                block_barrier_map[i][14-j*2] = 2;
                block_barrier_map[16-i][15-j*2] = 2;
            }
        }
        for(int i=1; i<=3; i++){ //vertical
            for(int j=1; j<=6; j++){
                block_barrier_map[i*2-1][j] = 2;
                block_barrier_map[17-i*2][14-j] = 2;
            }
        }
        for(int i=1; i<=2; i++){ //vertical
            for(int j=1; j<=6; j++){
                block_barrier_map[i*2][14-j] = 2;
                block_barrier_map[16-i*2][j] = 2;
            }
        }
        block_barrier_map[1][1] = 0;
        block_barrier_map[1][2] = 0;
        block_barrier_map[2][1] = 0;

        block_barrier_map[15][13] = 0;
        block_barrier_map[15][12] = 0;
        block_barrier_map[14][13] = 0;

        for(int i=1; i<=6; i++){ //box
            block_barrier_map[7][i*2] = 2;
        }

        for(int i=1; i<=4; i++){
            block_barrier_map[8][i*3] = 2;
        }

        for(int i=1; i<=7; i++){
            block_barrier_map[9][i*2-1] = 2;
        }




        for(int i=1; i<=2; i++){    //house_o
            for(int j=1; j<=3; j++){
                block_barrier_map[i*2][j*2] = 3;
            }
        }

        for(int i=1; i<=2; i++){    //house_r
            for(int j=1; j<=3; j++){
                block_barrier_map[i*2+10][j*2+6] = 3;
            }
        }

        for(int i=1; i<=3; i++){    //house_b
            for(int j=1; j<=3; j++){
                block_barrier_map[i*2-1][j*2+7] = 3;
            }
        }

        for(int i=1; i<=3; i++){    //house_y
            for(int j=1; j<=3; j++){
                block_barrier_map[i*2+9][j*2-1] = 3;
            }
        }

        for(int i=1; i<=3; i++){ //tree----
            block_barrier_map[i*2-1][7] = 3;
        }
        for(int i=1; i<=3; i++){
            block_barrier_map[i*2+9][7] = 3;
        }

        //tree|||

        block_barrier_map[6][2] = 3;
        block_barrier_map[6][4] = 3;
        block_barrier_map[6][6] = 3;
        block_barrier_map[10][2] = 3;
        block_barrier_map[10][4] = 3;
        block_barrier_map[10][8] = 3;

        block_barrier_map[6][10] = 3;
        block_barrier_map[6][12] = 3;
        block_barrier_map[10][10] = 3;
        block_barrier_map[10][12] = 3;

        //wall
        for(int i=0; i<14; i++){
            block_barrier_map[0][i] = 3;
            block_barrier_map[16][i] = 3;
        }
        for(int i=0; i<16; i++){
            block_barrier_map[i][0] = 3;
            block_barrier_map[i][14] = 3;
        }


    }
}



void barrier_draw()
{
    if(map_dir == 0){
        int choose;
        for(int i=1; i<16; i++){
            for(int j=1; j<14; j++){

                if(block_barrier_map[i][j] == 2){
                    choose = (i*j)%3 + 1;
                    if(choose == 1)
                        al_draw_bitmap(box1, i*40-19, j*40+2, 0);
                    if(choose == 2)
                        al_draw_bitmap(box2, i*40-19, j*40+2, 0);
                    if(choose == 3)
                        al_draw_bitmap(box3, i*40-19, j*40+2, 0);

                }
            }
        }
    }else if(map_dir == 1){

        for(int i=1; i<=5; i++){
            for(int j=1; j<=13; j++){
                if(block_barrier_map[i][j] == 2){
                    if((i+j)%2 == 0) al_draw_bitmap(vbox_r, i*40-19, j*40+2, 0);
                    else al_draw_bitmap(vbox_y, i*40-19, j*40+2, 0);
                }
            }
        }

        for(int i=11; i<=15; i++){
            for(int j=1; j<=13; j++){
                if(block_barrier_map[i][j] == 2){
                    if((i+j)%2 == 0) al_draw_bitmap(vbox_r, i*40-19, j*40+2, 0);
                    else al_draw_bitmap(vbox_y, i*40-19, j*40+2, 0);
                }
            }
        }

        for(int i=7; i<=9; i++){
            for(int j=1; j<=13; j++){
                if(block_barrier_map[i][j] == 2){
                    al_draw_bitmap(vbox, i*40-19, j*40+2, 0);
                }
            }
        }

        for(int i=1; i<=2; i++){    //house_o
            for(int j=1; j<=3; j++){
                al_draw_bitmap(vbarrier_o, i*2*40-19, j*2*40-13, 0);
                //block_barrier_map[i*2][j*2] = 3;
            }
        }



        for(int i=1; i<=3; i++){    //house_b
            for(int j=1; j<=3; j++){
                al_draw_bitmap(vbarrier_b, (i*2-1)*40-19, (j*2+7)*40-13, 0);
                //block_barrier_map[i*2-1][j*2+7] = 3;
            }
        }

        for(int i=1; i<=3; i++){    //house_y
            for(int j=1; j<=3; j++){
                al_draw_bitmap(vbarrier_y, (i*2+9)*40-19, (j*2-1)*40-13, 0);
                //block_barrier_map[i*2+9][j*2-1] = 3;
            }
        }

        for(int i=1; i<=3; i++){ //tree----
            al_draw_bitmap(tree, (i*2-1)*40-19, 7*40-28, 0);
            //block_barrier_map[i*2-1][7] = 3;
        }
        for(int i=1; i<=3; i++){
            al_draw_bitmap(tree, (i*2+9)*40-19, 7*40-28, 0);
            //block_barrier_map[i*2+9][7] = 3;
        }

        //tree|||
        al_draw_bitmap(bush, 6*40-19, 1*40-13, 0);
        al_draw_bitmap(tree, 6*40-19, 2*40-28, 0);
        al_draw_bitmap(bush, 6*40-19, 3*40-13, 0);
        //block_barrier_map[6][2] = 3;
        al_draw_bitmap(tree, 6*40-19, 4*40-28, 0);
        al_draw_bitmap(bush, 6*40-19, 5*40-13, 0);
        //block_barrier_map[6][4] = 3;
        al_draw_bitmap(tree, 6*40-19, 6*40-28, 0);
        al_draw_bitmap(bush, 6*40-19, 7*40-13, 0);
        al_draw_bitmap(bush, 6*40-19, 8*40-13, 0);
        //block_barrier_map[6][6] = 3;
        al_draw_bitmap(bush, 6*40-19, 9*40-13, 0);
        al_draw_bitmap(tree, 6*40-19, 10*40-28, 0);
        //block_barrier_map[6][10] = 3;
        al_draw_bitmap(bush, 6*40-19, 11*40-13, 0);
        al_draw_bitmap(tree, 6*40-19, 12*40-28, 0);
        al_draw_bitmap(bush, 6*40-19, 13*40-13, 0);
        //block_barrier_map[6][12] = 3;



        al_draw_bitmap(bush, 10*40-19, 1*40-13, 0);
        al_draw_bitmap(tree, 10*40-19, 2*40-28, 0);
        al_draw_bitmap(bush, 10*40-19, 3*40-13, 0);
        //block_barrier_map[10][2] = 3;
        al_draw_bitmap(tree, 10*40-19, 4*40-28, 0);
        al_draw_bitmap(bush, 10*40-19, 5*40-13, 0);
        al_draw_bitmap(bush, 10*40-19, 6*40-13, 0);
        al_draw_bitmap(bush, 10*40-19, 7*40-13, 0);
        //block_barrier_map[10][4] = 3;
        al_draw_bitmap(tree, 10*40-19, 8*40-28, 0);
        al_draw_bitmap(bush, 10*40-19, 9*40-13, 0);
        //block_barrier_map[10][8] = 3;
        al_draw_bitmap(tree, 10*40-19, 10*40-28, 0);
        al_draw_bitmap(bush, 10*40-19, 11*40-13, 0);
        //block_barrier_map[10][10] = 3;
        al_draw_bitmap(tree, 10*40-19, 12*40-28, 0);
        al_draw_bitmap(bush, 10*40-19, 13*40-13, 0);
        //block_barrier_map[10][12] = 3;


        al_draw_bitmap(bush, 2*40-19, 7*40-13, 0);
        al_draw_bitmap(bush, 4*40-19, 7*40-13, 0);
        al_draw_bitmap(bush, 12*40-19, 7*40-13, 0);
        al_draw_bitmap(bush, 14*40-19, 7*40-13, 0);

        for(int i=1; i<=2; i++){    //house_r
            for(int j=1; j<=3; j++){
                al_draw_bitmap(vbarrier_r, (i*2+10)*40-19, (j*2+6)*40-13, 0);

            }
        }
    }
}

void barrier_destroy(){
    al_destroy_bitmap(box1);
    al_destroy_bitmap(box2);
    al_destroy_bitmap(box3);

    al_destroy_bitmap(vbox_y);
    al_destroy_bitmap(vbox_r);
    al_destroy_bitmap(vbarrier_b);
    al_destroy_bitmap(vbarrier_o);
    al_destroy_bitmap(vbarrier_r);
    al_destroy_bitmap(vbarrier_y);
    al_destroy_bitmap(tree);
    al_destroy_bitmap(bush);

}

