#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

void draw_ship_at (int x, int y)
{
	//bitmap_layer_destroy(SHIP_LAYER);
	if (SHIP_LAYER == 0) {
		SHIP_LAYER = bitmap_layer_create ( (GRect) {
			.origin = {x, y - SHIP_HEIGHT /2}, .size = {SHIP_WIDTH, SHIP_HEIGHT}
		});
		bitmap_layer_set_bitmap (SHIP_LAYER, SHIP);
		bitmap_layer_set_compositing_mode (SHIP_LAYER, GCompOpAssignInverted);
		layer_add_child (the_window_layer, bitmap_layer_get_layer (SHIP_LAYER));
	} else {
		layer_set_frame (bitmap_layer_get_layer (SHIP_LAYER),
		(GRect) {
			.origin = {x, y- SHIP_HEIGHT /2}, .size = {SHIP_WIDTH, SHIP_HEIGHT}
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
		bitmap_layer_set_bitmap(ASTEROID_LAYERS[0],
								ASTEROIDS[  bitmap_layer_get_bitmap(ASTEROID_LAYERS[0]) == ASTEROIDS[0]  ]);
	}
asteroidAnimTimer = app_timer_register(ASTEROIDBLINKDELAY, (AppTimerCallback) animateAsteroid, 0);
}

void paint(struct Layer* layer, GContext* ctx)
{
	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, (GRect) {.origin = {0,0}, .size = {SCREEN_WIDTH, SCREEN_HEIGHT}},0,0);

	draw_laser(ctx);

}

void draw_laser(GContext* ctx) {
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_circle(ctx, laserHead, 3);
}

void fireLaser()
 {
	laserHead.x = plane.x;
	laserHead.y = plane.y;
	initialLaserDy = 1 + (SCREEN_HEIGHT/2 - plane.x)/SCREEN_WIDTH;
	initialLaserDx = 2;

	app_timer_register(LASERDELAY, (AppTimerCallback) animateLaser, 0);
 }

void animateLaser(void* data) {

	if (laserHead.x > DEADLASERXCOORDINATE) {
		app_timer_register(LASERDELAY, (AppTimerCallback) animateLaser, 0);
	}

	laserHead.x -= initialLaserDx;
	laserHead.y -= initialLaserDy;
	initialLaserDy /= 2;

}

#endif // UTILITY_H_INCLUDED
