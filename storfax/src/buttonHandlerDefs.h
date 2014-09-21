static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
	text_layer_set_text(text_layer, "Select");
}

static void text_layer_set_number(TextLayer* text_layer, uint16_t i) {
	static char g[4];
	snprintf(g, 4, "%d", i);
	text_layer_set_text(text_layer, g);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
	plane.y -= 10;

	text_layer_set_number(text_layer, plane.y);

	draw_ship_at(plane.x, plane.y);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
	plane.y += 10;

	text_layer_set_number(text_layer, plane.y);

	draw_ship_at(plane.x, plane.y);
}
