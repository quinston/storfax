#include <pebble.h>


/* Up and down buttons on the bottom,

y-axis increases at the down button*/
#define SCREEN_WIDTH 168
#define SCREEN_HEIGHT 144

static Window* window;
static Layer* the_window_layer;


static GBitmap* SHIP;
static BitmapLayer* SHIP_LAYER;

static GBitmap* COSMOS;
static BitmapLayer* COSMOS_LAYER;

#define nASTEROIDTYPES 2
static GBitmap* ASTEROIDS[nASTEROIDTYPES];
#define nMAXASTEROIDS 8
static BitmapLayer* ASTEROID_LAYERS[nMAXASTEROIDS];
#define ASTEROIDBLINKDELAY 100

static AppTimer* asteroidAnimTimer;

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


#include "buttonHandlerDefs.h"

#include "setupHandlers.h"


static void window_load (Window* window)
{
	the_window_layer = window_get_root_layer (window);

	GRect bounds = layer_get_bounds (the_window_layer);

}

static void window_unload (Window* window)
{
}

static void init (void)
{

	#include "images.h"

	window = window_create();
	window_set_background_color(window, GColorBlack);

	window_set_click_config_provider (window, click_config_provider);
	window_set_window_handlers (window, (WindowHandlers) {
		.load = window_load,
		 .unload = window_unload,
	});
	const bool animated = true;
	window_stack_push (window, animated);


	asteroidAnimTimer = app_timer_register(ASTEROIDBLINKDELAY, (AppTimerCallback) animateAsteroid, 0);
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

	init();

	app_event_loop();
	deinit();
}

#include "definitions.h"
