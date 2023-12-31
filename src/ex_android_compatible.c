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

#define MAX_TOUCH 10

struct touch {
   bool down;
   double x, y;
} touch[MAX_TOUCH];

static void draw_touches(void)
{
   int i;

   for (i = 0; i < MAX_TOUCH; i++) {
      if (touch[i].down) {
         al_draw_filled_rectangle(
            touch[i].x-40, touch[i].y-40,
            touch[i].x+40, touch[i].y+40,
            al_map_rgb(100+i*20, 40+i*20, 40+i*20));
      }
   }
}

#ifdef ANDROID
#include <allegro5/allegro_android.h>

const char *loadAsset(const char* asset)
{
    /* This is loaded from assets in the apk. */
    al_android_set_apk_file_interface();

    ALLEGRO_FILE *fin = al_fopen(asset, "rb");
    al_set_standard_file_interface();
    ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_USER_DATA_PATH);
    al_set_path_filename(path, asset);
    ALLEGRO_FILE *fout = al_fopen(al_path_cstr(path, '/'), "wb");
    while (!al_feof(fin)) {
        char buf[1024];
        int n = al_fread(fin, buf, 1024);
        al_fwrite(fout, buf, n);
    }
    al_fclose(fin);
    al_fclose(fout);

    

    return al_path_cstr(path, '/');
}
#else

const char *loadAsset(const char* asset)
{
    return asset;
}

#endif // ANDROID

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
    al_set_new_display_option(ALLEGRO_SUPPORTED_ORIENTATIONS, ALLEGRO_DISPLAY_ORIENTATION_LANDSCAPE, ALLEGRO_REQUIRE);

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / FPS); if(!timer) { printf("[INIT_ERROR]: Couldn't create timer!\n"); return -1;} else{ printf("[INIT]: Created timer.\n");}
    ALLEGRO_EVENT_QUEUE* event_queue = al_create_event_queue(); if(!event_queue) { printf("[INIT_ERROR]: Couldn't create event queue!\n"); return -1;} else{ printf("[INIT]: Created event queue.\n");}
    ALLEGRO_DISPLAY* display = al_create_display(WIDTH, HEIGHT); if(!display) { printf("[INIT_ERROR]: Couldn't create display!\n"); return -1;} else{ printf("[INIT]: Created display.\n");}

    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_touch_input_event_source());
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

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;

            case ALLEGRO_EVENT_TOUCH_BEGIN:
                //ALLEGRO_DEBUG("touch %i begin", event.touch.id);
                touch[event.touch.id].down = true;
                touch[event.touch.id].x = event.touch.x;
                touch[event.touch.id].y = event.touch.y;
                break;

            case ALLEGRO_EVENT_TOUCH_END:
                //ALLEGRO_DEBUG("touch %i end", event.touch.id);
                touch[event.touch.id].down = false;
                touch[event.touch.id].x = 0.0;
                touch[event.touch.id].y = 0.0;
                break;

            case ALLEGRO_EVENT_TOUCH_MOVE:
                //ALLEGRO_DEBUG("touch %i move: %fx%f", event.touch.id, event.touch.x, event.touch.y);
                touch[event.touch.id].x = event.touch.x;
                touch[event.touch.id].y = event.touch.y;
                break;

            case ALLEGRO_EVENT_DISPLAY_HALT_DRAWING:
                al_stop_timer(timer);
                redraw = false;
                al_acknowledge_drawing_halt(display);
                break;

            case ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING:
                al_acknowledge_drawing_resume(display);
                al_start_timer(timer);
                break;
            
            case ALLEGRO_EVENT_DISPLAY_RESIZE:
                al_acknowledge_resize(display);
                break;
        }

        if(done)
            break;

        if(redraw && al_is_event_queue_empty(event_queue))
        {
            al_clear_to_color(al_map_rgb(0, 0, 0));

            draw();

            draw_touches();
            
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
    // You can use if(key[ALLEGRO_KEY_...]){ then do } to detect if key has been pressed.
    return;
}

void draw() 
{
    // What to draw on the screen.
    return;
}