#ifndef FRACTAL_H
#define FRACTAL_H
#include "str.h"

#define Screen fractal->screen
#define Bro fractal->bro
#define fractal F

int azerty(s_fractal *fractal, double x, double y, int nbIter);
void *fractal_thread(void *s_fractal_addr);
void julia(s_fractal *fractal);
void bro(s_fractal *fractal);
void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
double f_rand();

#endif
