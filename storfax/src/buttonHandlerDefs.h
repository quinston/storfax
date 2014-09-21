#pragma once

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	if (laserHead.x < DEADLASERXCOORDINATE) {
		fireLaser();
	}
}

static void text_layer_set_number(TextLayer* text_layer, uint16_t i) {
	static char g[4];
	snprintf(g, 4, "%d", i);

}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	plane.y -= 10;

    if (currentAsteroidPositions[0] > 0) --currentAsteroidPositions[0];


	draw_ship_at(plane.x, plane.y);

	draw_asteroid_at(currentAsteroidPositions[0]);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	plane.y += 10;


	draw_ship_at(plane.x, plane.y);

	if (currentAsteroidPositions[0] < nASTEROIDPOSITIONS) ++currentAsteroidPositions[0];

	draw_asteroid_at(currentAsteroidPositions[0]);
}
