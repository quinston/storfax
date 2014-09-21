#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

void draw_ship_at(int x, int y);

void draw_asteroids();

void animateAsteroid(void*);

void moveAsteroid();

void paint(struct Layer*, GContext*);

void draw_laser(GContext*);

void fireLaser();
void animateLaser(void*);

void checkCollisions();

void cycle(void*);

int getAsteroidRespawnXCoord();

#endif
