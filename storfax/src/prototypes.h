#ifndef PROTOTYPES_H_INCLUDED
#define PROTOTYPES_H_INCLUDED

void draw_ship_at(int x, int y);

// there are 8 predefined positions for asteroids
void draw_asteroid_at(int numPosition);

void animateAsteroid(void*);

void paint(struct Layer*, GContext*);

void draw_laser(GContext*);

void fireLaser();
void animateLaser(void*);

#endif
