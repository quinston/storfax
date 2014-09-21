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

void draw_asteroids()
{
	for (int i=0; i != nMAXASTEROIDS; ++i) {

			app_log(APP_LOG_LEVEL_DEBUG, "definitions.h", 28, "Asteriod %d at x=%d", i, currentAsteroidPositions[i*2]);

	if (ASTEROID_LAYERS[i] == 0) {
		ASTEROID_LAYERS[i] = bitmap_layer_create ( (GRect) {
			.origin = {
				currentAsteroidPositions[i*2], currentAsteroidPositions[i*2+1]
			}, .size = {ASTEROID_WIDTH, ASTEROID_HEIGHT}
		});
		bitmap_layer_set_bitmap (ASTEROID_LAYERS[i], ASTEROIDS[1]);
		bitmap_layer_set_compositing_mode (ASTEROID_LAYERS[i], GCompOpAssignInverted);
		layer_add_child (the_window_layer, bitmap_layer_get_layer (ASTEROID_LAYERS[i]));
	} else {
		layer_set_frame (bitmap_layer_get_layer (ASTEROID_LAYERS[i]),
		(GRect) {
			.origin = {
				currentAsteroidPositions[i*2], currentAsteroidPositions[i*2 + 1]
			}, .size = {ASTEROID_WIDTH, ASTEROID_HEIGHT}
		});
	}
}
}

void animateAsteroid(void* g) {
	for (int i = 0 ; i != nMAXASTEROIDS; ++i) {
	if (ASTEROID_LAYERS[i] != 0)
	{
		bitmap_layer_set_bitmap(ASTEROID_LAYERS[i],
								ASTEROIDS[  bitmap_layer_get_bitmap(ASTEROID_LAYERS[i]) == ASTEROIDS[0]  ]);
	}
	}
asteroidAnimTimer = app_timer_register(ASTEROIDBLINKDELAY, (AppTimerCallback) animateAsteroid, 0);

}

void paint(struct Layer* layer, GContext* ctx)
{
	if (gameIsLost)
	{
		layer_remove_child_layers(the_window_layer);
		graphics_draw_bitmap_in_rect(ctx, gameOver, (GRect) {.origin={0,0}, .size={SCREEN_WIDTH, SCREEN_HEIGHT}});
	}
	else {


	graphics_context_set_fill_color(ctx, GColorBlack);
	graphics_fill_rect(ctx, (GRect) {.origin = {0,0}, .size = {SCREEN_WIDTH, SCREEN_HEIGHT}},0,0);

	draw_asteroids();

	draw_laser(ctx);

	}

}

void draw_laser(GContext* ctx) {
	graphics_context_set_fill_color(ctx, GColorWhite);
	graphics_fill_circle(ctx, laserHead, 3);
}

void fireLaser()
 {
	laserHead.x = plane.x;
	laserHead.y = plane.y;
	initialLaserDx = 2;

	app_timer_register(LASERDELAY, (AppTimerCallback) animateLaser, 0);
 }

void animateLaser(void* data) {

	if (laserHead.x > DEADLASERXCOORDINATE) {
		app_timer_register(LASERDELAY, (AppTimerCallback) animateLaser, 0);
	}

	laserHead.x -= initialLaserDx;

}

bool isColliding(struct GRect a, struct GRect b) {
	int x5 = (a.origin.x > b.origin.x) ? a.origin.x:b.origin.x;
	int y5 = (a.origin.y > b.origin.y) ? a.origin.y:b.origin.y;
	int x6 = (a.origin.x + a.size.w < b.origin.x + b.size.w) ? a.origin.x + a.size.w:b.origin.x + b.size.w;
	int y6 = (a.origin.y + a.size.h < b.origin.y + b.size.h) ? a.origin.y + a.size.h:b.origin.y + b.size.h;
	return (x5<x6) && (y5<y6);
}

void checkCollisions() {
	for (int i = 0; i != nMAXASTEROIDS; ++i) {
		if (ASTEROID_LAYERS[i] != 0 && SHIP_LAYER != 0)
		if (isColliding(layer_get_frame(bitmap_layer_get_layer(ASTEROID_LAYERS[i])),
						layer_get_frame(bitmap_layer_get_layer(SHIP_LAYER)))) {
			lose();
			break;
		}
	}
}

void cycle(void* data){
	moveAsteroid();

	checkCollisions();

	app_log(APP_LOG_LEVEL_DEBUG, "definitions.h", 119, "cycling!");


	cycleTimer = app_timer_register(1 / cyclesPerSecond, (AppTimerCallback) cycle, 0);


}

void moveAsteroid() {
	 for(int i=0;i != nMAXASTEROIDS; ++i) {
		if (ASTEROID_LAYERS[i] != 0) {


			// push asteroid back to top
			if (currentAsteroidPositions[2*i] > SCREEN_WIDTH) {
				currentAsteroidPositions[2*i] = getAsteroidRespawnXCoord();
				currentAsteroidPositions[2*i+1] =rand() * SCREEN_HEIGHT;
			}
			else {
				currentAsteroidPositions[2*i] += asteroidSpeed ;

			}

		}
	}
}

int getAsteroidRespawnXCoord() {
	return -10;
}

#endif // UTILITY_H_INCLUDED
