#include <pebble.h>


/* Up and down buttons on the bottom,

y-axis increases at the down button*/
#define SCREEN_WIDTH 144
#define SCREEN_HEIGHT 168

static Window* window;
static Layer* the_window_layer;

static GBitmap* gameOver;
static BitmapLayer* gameOverLayer;
int gameIsLost;


static GBitmap* SHIP;
static BitmapLayer* SHIP_LAYER;


#define nASTEROIDTYPES 2
static GBitmap* ASTEROIDS[nASTEROIDTYPES];
#define nMAXASTEROIDS 8
static BitmapLayer* ASTEROID_LAYERS[nMAXASTEROIDS];
#define ASTEROIDBLINKDELAY 100

static int asteroidSpeed = 1;


static AppTimer* asteroidAnimTimer;

static AppTimer* cycleTimer;
static float cyclesPerSecond = 10;

#include "asteroidPositionGraph.h"

#include "prototypes.h"



/*
x: The coordinate of the MIDDLE of the plane. The plane is centred at x.
*/
struct Thing {
	uint16_t x;
	uint16_t y;
};

struct Thing plane;

struct GPoint laserHead;
float initialLaserDx;
float initialLaserDy;
#define LASERDELAY 40
#define DEADLASERXCOORDINATE -10


#include "buttonHandlerDefs.h"

#include "setupHandlers.h"


static void window_load (Window* window)
{
	the_window_layer = window_get_root_layer (window);

	layer_set_update_proc(the_window_layer, paint);

	GRect bounds = layer_get_bounds (the_window_layer);

	for (int i = 0; i != nMAXASTEROIDS; ++i){
		layer_add_child(the_window_layer, bitmap_layer_get_layer( ASTEROID_LAYERS[i]));
	}

	asteroidAnimTimer = app_timer_register(ASTEROIDBLINKDELAY, (AppTimerCallback) animateAsteroid, 0);

	cycleTimer = app_timer_register(1 / cyclesPerSecond, (AppTimerCallback) cycle, 0);



}

static void window_unload (Window* window)
{
}

static void init (void)
{
	gameIsLost = false;
	#include "images.h"

	window = window_create();
	window_set_background_color(window, GColorBlack);
	window_set_fullscreen(window, 1);

	window_set_click_config_provider (window, click_config_provider);
	window_set_window_handlers (window, (WindowHandlers) {
		.load = window_load,
		 .unload = window_unload,
	});
	const bool animated = true;
	window_stack_push (window, animated);

}

static void deinit (void)
{
	#include "deimages.h"

	window_destroy (window);
}

int main (void)
{
	plane.x = 100;
	plane.y = 80;

	laserHead.x = laserHead.y = -90;

	init();

	app_event_loop();
	deinit();
}

void lose() {
	gameIsLost = 1;
}

#include "definitions.h"
