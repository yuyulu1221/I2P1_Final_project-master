#include "ending.h"

static ALLEGRO_DISPLAY *screen;
static char const *filename_1;
static char const *filename_2;
static char const *filename_3;
ALLEGRO_EVENT_QUEUE *queue;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *timer;
ALLEGRO_VIDEO *video;

void video_display(ALLEGRO_VIDEO *video) {
    ALLEGRO_BITMAP *frame = al_get_video_frame(video);
    // check if we get the frame successfully
    // Note the this code is necessary
    if ( !frame )
        return;
    // Display the frame.
    // rescale the frame into the size of screen
    al_draw_scaled_bitmap(frame,
                          // the rescale position of the frame
                          0, 0,
                          // the width and height you want to rescale
                          al_get_bitmap_width(frame),
                          al_get_bitmap_height(frame),
                          // the position of result image
                          0, 0,
                          // the width and height of result image
                          al_get_display_width(screen),
                          al_get_display_height(screen), 0);
    al_flip_display();
}


void init_video(){
    //al_init();
    al_init_video_addon();
    //al_install_audio();
    timer = al_create_timer(1.0 / 60);
    //al_set_new_display_flags(ALLEGRO_RESIZABLE);
    //al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    screen = al_create_display(800, 600);
    // linear interpolation for scaling images
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);
    filename_1 = "./video/draw.ogv";
    filename_2 = "./video/tong.ogv";
    filename_3 = "./video/bing.ogv";

    printf("reading video.....\n");

    if(game_results == 1)
        video = al_open_video(filename_1);
    else if(game_results == 2)
        video = al_open_video(filename_2);
    else if(game_results == 3)
        video = al_open_video(filename_3);

    if( video )
        printf("read video succeed\n");
    else
        printf("read video fail!!!!\n");
    queue = al_create_event_queue();
    // register video event
    ALLEGRO_EVENT_SOURCE *temp = al_get_video_event_source(video);
    al_register_event_source(queue, temp);
    al_register_event_source(queue, al_get_display_event_source(screen));
    al_register_event_source(queue, al_get_timer_event_source(timer));

}
void video_begin(){
    al_reserve_samples(1);
    al_start_video(video, al_get_default_mixer());
    al_start_timer(timer);
}
void destroy_video(){
    al_destroy_display(screen);
    al_destroy_event_queue(queue);
}
void ending_begin() {
    init_video();
    video_begin();
    while( 1 ){
        al_wait_for_event(queue, &event);
        if( event.type == ALLEGRO_EVENT_TIMER ) {
            video_display(video);
        } else if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
            al_close_video(video);
            break;
        } else if( event.type == ALLEGRO_EVENT_VIDEO_FINISHED ) {
            break;
        }
    }
    destroy_video();
    game_results = -1; //after video shut down the game
}
