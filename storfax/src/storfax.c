#include <pebble.h>


static Window* window;
static Layer* the_window_layer;

static TextLayer* text_layer;


static GBitmap* SHIP;
static BitmapLayer* SHIP_LAYER;

static GBitmap* COSMOS;
static BitmapLayer* COSMOS_LAYER;

#include "prototypes.h"


/* Up and down buttons on the bottom*/
#define SCREEN_WIDTH 168
#define SCREEN_HEIGHT 144

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

	text_layer = text_layer_create ( (GRect) {
		.origin = { 0, 72 }, .size = { bounds.size.w, 20 }
	});
	text_layer_set_text (text_layer, "Press a buttoon");
	text_layer_set_text_alignment (text_layer, GTextAlignmentCenter);
	layer_add_child (the_window_layer, text_layer_get_layer (text_layer));
}

static void window_unload (Window* window)
{
	text_layer_destroy (text_layer);
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
