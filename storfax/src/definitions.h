#ifndef DEFINITIONS_H_INCLUDED
#define DEFINITIONS_H_INCLUDED

void draw_ship_at(int x, int y){
	//bitmap_layer_destroy(SHIP_LAYER);
	if (SHIP_LAYER == 0) {
		SHIP_LAYER = bitmap_layer_create((GRect) {.origin = {x,y}, .size={SHIP_WIDTH, SHIP_HEIGHT}});
		bitmap_layer_set_bitmap(SHIP_LAYER, SHIP);
		bitmap_layer_set_compositing_mode(SHIP_LAYER, GCompOpAssignInverted);
		layer_add_child(the_window_layer, bitmap_layer_get_layer(SHIP_LAYER));
	}
	else {
		layer_set_frame(bitmap_layer_get_layer(SHIP_LAYER),
						(GRect) {.origin = {x,y}, .size={SHIP_WIDTH, SHIP_HEIGHT}});
	}
}


#endif // UTILITY_H_INCLUDED
