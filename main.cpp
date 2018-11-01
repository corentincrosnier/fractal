#include <iostream>
#include "event.h"
#include <math.h>

using namespace std;

Uint32 getPixel(SDL_Surface* surface, int x, int y, int *alpha);

int main(){
	SDL_Init(SDL_INIT_VIDEO);
	pthread_t p_fractal;
	s_fractal fractal={
		.screen=SDL_SetVideoMode(500,500,32,SDL_DOUBLEBUF | SDL_RESIZABLE),
		//.bro=NULL,
		.fractal_mut=PTHREAD_MUTEX_INITIALIZER,
		.dataSet=NULL,
		.centerX=0,
		.centerY=0,
		.k=1,
		.pitch=fractal.k*fractal.screen->h/4,
		.Cx=-0.5,
		.Cy=0.6,
		.stop=0,
		.count=0,
	};
	srand(time(NULL));

	cout << azerty(&fractal,0,0,200) <<endl;
	pthread_create(&p_fractal,NULL,fractal_thread,&fractal);
	event(&fractal);
	pthread_join(p_fractal,NULL);
	//fclose(fractal.dataSet);
	SDL_Quit();

return 0;
}

Uint32 getPixel(SDL_Surface* surface, int x, int y, int *alpha){

	if(x<0 || y<0 || x>=surface->w || y>=surface->h)
		return 0;
	int bpp=surface->format->BytesPerPixel;
	Uint8 *p=(Uint8*)surface->pixels+y*surface->pitch+x*bpp;
	if(alpha!=NULL && !surface->format->Amask)
		*alpha=0;

	switch(bpp)
	{
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] << 16 | p[1] << 8 | p[2];
			return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			{
				if(alpha!=NULL && surface->format->Amask)
					*alpha=p[0];
				return *(Uint32 *)p;
			}
			else
			{
				if(alpha!=NULL && surface->format->Amask)
					*alpha=255-p[3];
				return p[0] | p[1]<<8 | p[2]<<16;
			}
		default:
			return 0;
	}
}
