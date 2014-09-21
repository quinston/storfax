#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

void draw_ship_at (int x, int y)
{
	//bitmap_layer_destroy(SHIP_LAYER);
	if (SHIP_LAYER == 0) {
		SHIP_LAYER = bitmap_layer_create ( (GRect) {
			.origin = {x, y}, .size = {SHIP_WIDTH, SHIP_HEIGHT}
		});
		bitmap_layer_set_bitmap (SHIP_LAYER, SHIP);
		bitmap_layer_set_compositing_mode (SHIP_LAYER, GCompOpAssignInverted);
		layer_add_child (the_window_layer, bitmap_layer_get_layer (SHIP_LAYER));
	} else {
		layer_set_frame (bitmap_layer_get_layer (SHIP_LAYER),
		(GRect) {
			.origin = {x, y}, .size = {SHIP_WIDTH, SHIP_HEIGHT}
		});
	}
}

void draw_asteroid_at (int numPosition)
{
	if (ASTEROID_LAYERS[0] == 0) {
		ASTEROID_LAYERS[0] = bitmap_layer_create ( (GRect) {
			.origin = {
				asteroidPositions[0], asteroidPositions[1]
			}, .size = {ASTEROID_WIDTH, ASTEROID_HEIGHT}
		});
		bitmap_layer_set_bitmap (ASTEROID_LAYERS[0], ASTEROIDS[1]);
		bitmap_layer_set_compositing_mode (ASTEROID_LAYERS[0], GCompOpAssignInverted);
		layer_add_child (the_window_layer, bitmap_layer_get_layer (ASTEROID_LAYERS[0]));
	} else {
		layer_set_frame (bitmap_layer_get_layer (ASTEROID_LAYERS[0]),
		(GRect) {
			.origin = {
				asteroidPositions[numPosition*2], asteroidPositions[numPosition*2 + 1]
			}, .size = {ASTEROID_WIDTH, ASTEROID_HEIGHT}
		});
	}
}

void animateAsteroid(void* g) {
	if (ASTEROID_LAYERS[0] != 0)
	{
		bitmap_layer_set_bitmap(ASTEROID_LAYERS[0], ASTEROIDS[ time_ms(0,0) % 2]);
	}
asteroidAnimTimer = app_timer_register(ASTEROIDBLINKDELAY, (AppTimerCallback) animateAsteroid, 0);
}

#endif // UTILITY_H_INCLUDED
