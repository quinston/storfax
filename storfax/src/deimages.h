#ifndef DEIMAGES_H_INCLUDED
#define DEIMAGES_H_INCLUDED

gbitmap_destroy(SHIP);

for (int i = 0; i != nASTEROIDTYPES; ++i) {
	gbitmap_destroy(ASTEROIDS[i]);
}


#endif // DEIMAGES_H_INCLUDED
