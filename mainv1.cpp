#include <allegro5/allegro.h>
#include<iostream>
using namespace std;

const float FPS = 60; //rate that timer ticks at
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int BOUNCER_SIZE = 32; //player size

enum MYKEYS { //enumerations
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT
};

int main() {

	//allegro variables
	ALLEGRO_DISPLAY* display = NULL;
	ALLEGRO_EVENT_QUEUE* event_queue = NULL; //sort of like a bucket of all the things that happen in the game
	ALLEGRO_TIMER* timer = NULL; //a ticking clock that dictates the rhythm of the game
	ALLEGRO_BITMAP* bouncer = NULL; //player
	//using a bitmap allows me to upload a sprite to my player later on (requires a helper library)

	//player and game variables
	float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0; //middle screen
	float bouncer_y = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0; //middle screen
	bool key[4] = { false, false, false, false }; //hold keystroke data
	bool redraw = true;
	bool doexit = false; //game loop

	//set up allegro
	al_init();
	al_install_keyboard();
	timer = al_create_timer(1.0 / FPS);
	display = al_create_display(SCREEN_W, SCREEN_H);

	//any helper libraries are initialized under this

	//set up player
	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE); //create player
	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255, 0, 255)); //these 3 lines must be together

	//set up rest of game
	al_set_target_bitmap(al_get_backbuffer(display));
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source()); //these 3 lines just tell you what does in the event_queue(event bucket)
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_flip_display(); //flip display so that it actually is on the display
	al_start_timer(timer); //start the timer so it starts ticking

	//game loop
	while (!doexit) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev); //create event queue and start having it look for stuff

		//timer section
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (key[KEY_UP] && bouncer_y >= 4.0) { //bounds checking & movement
				bouncer_y -= 4.0;
			}

			if (key[KEY_DOWN] && bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0) {
				bouncer_y += 4.0;
			}

			if (key[KEY_LEFT] && bouncer_x >= 4.0) {
				bouncer_x -= 4.0;
			}

			if (key[KEY_RIGHT] && bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0) {
				bouncer_x += 4.0;
			}

			redraw = true;
		}

		//input and output section
		else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break; //if you press the x button then kill the progream
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) { //looking for the event time of a keypress
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = true; //when each key is pressed, one of the boolian values we set up earlier is set to true
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = true;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = true;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = true;
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) { //looking for the event time of a keypress
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_UP:
				key[KEY_UP] = false; //when each key is pressed, one of the boolian values we set up earlier is set to true
				break;

			case ALLEGRO_KEY_DOWN:
				key[KEY_DOWN] = false;
				break;

			case ALLEGRO_KEY_LEFT:
				key[KEY_LEFT] = false;
				break;

			case ALLEGRO_KEY_RIGHT:
				key[KEY_RIGHT] = false;
				break;
			}
		}
		

		//render section
		if (redraw && al_is_event_queue_empty(event_queue)){
			redraw = false;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_bitmap(bouncer, bouncer_x, bouncer_y, 0); //drawing player
			al_flip_display(); //flips everything from memory onto the screen
;		}
	} //end game loop

	//clean up memory
	al_destroy_bitmap(bouncer);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);

	return 0; //kill program
}
