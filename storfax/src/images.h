#ifndef IMAGES_H_INCLUDED
#define IMAGES_H_INCLUDED

#define SHIP_WIDTH 30
#define SHIP_HEIGHT 40
SHIP = gbitmap_create_with_resource(RESOURCE_ID_IMG_SHIP);

#define ASTEROID_WIDTH 20
#define ASTEROID_HEIGHT 20
ASTEROIDS[0] = gbitmap_create_with_resource(RESOURCE_ID_IMG_ASTER1);
ASTEROIDS[1] = gbitmap_create_with_resource(RESOURCE_ID_IMG_ASTER2);


for (int i = 0; i != nMAXASTEROIDS; ++i) {

	ASTEROID_LAYERS[i] = 0;
	ASTEROID_LAYERS[i] = bitmap_layer_create((GRect)
{
	.origin = {-999,-999},
	.size = {ASTEROID_WIDTH, ASTEROID_HEIGHT}
});


	bitmap_layer_set_bitmap(ASTEROID_LAYERS[i], ASTEROIDS[0]);
	bitmap_layer_set_compositing_mode (ASTEROID_LAYERS[i] ,GCompOpAssignInverted);
}


gameOver = gbitmap_create_with_resource(RESOURCE_ID_IMG_GAMEOVER);
gameOverLayer = bitmap_layer_create((GRect) {.origin = {0,0}, .size = {SCREEN_WIDTH, SCREEN_HEIGHT}});


#endif // IMAGES_H_INCLUDED
