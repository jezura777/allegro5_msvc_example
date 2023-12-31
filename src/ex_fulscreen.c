#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro5.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define WIDTH   640
#define HEIGHT  480
#define FPS      60

void update(unsigned char key[ALLEGRO_KEY_MAX]);
void draw();

int main() 
{
    if(!al_init()) { printf("[INIT_ERROR]: Couldn't initialize allegro!\n"); return -1; } else { printf("[INIT]: Initialized allegro.\n");}
    if(!al_install_keyboard()) { printf("[INIT_ERROR]: Couldn't install keyboard!\n"); return -1;} else { printf("[INIT]: Initialized keyboard.\n");}
    if(!al_install_audio()) { printf("[INIT_ERROR]: Couldn't install audio!\n"); return -1;} else { printf("[INIT]: Initialized audio.\n");}
    if(!al_init_primitives_addon()) { printf("[INIT_ERROR]: Couldn't initilize primitives addon\n"); return -1;} else { printf("[INIT]: Initialized primitives addon.\n");}

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS); if(!timer) { printf("[INIT_ERROR]: Couldn't create timer!\n"); return -1;} else{ printf("[INIT]: Created timer.\n");}
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue(); if(!event_queue) { printf("[INIT_ERROR]: Couldn't create event queue!\n"); return -1;} else{ printf("[INIT]: Created event queue.\n");}
    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT); if(!display) { printf("[INIT_ERROR]: Couldn't create display!\n"); return -1;} else{ printf("[INIT]: Created display.\n");}

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    bool done = false;
    bool redraw = true;
    ALLEGRO_EVENT event;

    #define KEY_SEEN     1
    #define KEY_RELEASED 2

    unsigned char key[ALLEGRO_KEY_MAX];
    memset(key, 0, sizeof(key));

    al_start_timer(timer);
    while(1)
    {
        al_wait_for_event(event_queue, &event);

        switch(event.type)
        {
            case ALLEGRO_EVENT_TIMER:
                update(key);
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                key[event.keyboard.keycode] = KEY_SEEN | KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_KEY_UP:
                key[event.keyboard.keycode] &= KEY_RELEASED;
                break;

            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(display);
                break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            draw();
            
            al_flip_display();

            redraw = false;
        }

    }

    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);
    return 0;
}

void update(unsigned char key[ALLEGRO_KEY_MAX]) 
{
    // What happens every frame typically game logic, collision detection, etc.
    // You can use if(key[ALLEGRO_KEY_...]){ then do }
    return;
}

void draw() 
{
    // What to draw on the screen.
    return;
}