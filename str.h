#ifndef STR_H
#define STR_H
#include <SDL/SDL.h>
#include <pthread.h>
#include <iostream>
#include <math.h>

using namespace std;

struct s_fractal{
	SDL_Surface *screen;
	//SDL_Surface *bro;
	pthread_mutex_t fractal_mut;
	FILE *dataSet;
	int centerX;
	int centerY;
	double k;
	int pitch;
	double Cx;
	double Cy;
	int stop;
	int count;
};

#endif
