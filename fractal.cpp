#include "fractal.h"

#define PRECISION 200

int azerty(s_fractal *fractal, double x, double y, int nbIter){
	if(nbIter && x*x+y*y<=4)
		return azerty(fractal,x*x-y*y+fractal->Cx,2*x*y+fractal->Cy,nbIter-1);

	else
		return nbIter;
}

void *fractal_thread(void *s_fractal_addr){

	s_fractal *fractal=(s_fractal*)s_fractal_addr;

	while(!F->stop){
		//bro(fractal);
		julia(fractal);
	}

pthread_exit(NULL);
}

void julia(s_fractal *fractal){
	double x,y;
	int X=0.5*(Screen->w-Screen->h);
	int Y=0;
	int deep;
	Uint8 colFact;
	Uint32 col;

	pthread_mutex_lock(&F->fractal_mut);
	SDL_FillRect(Screen,NULL,0x000000);
	for(x=F->centerX-2.0/F->k;x<=F->centerX+2.0/F->k;x+=4.0/(Screen->h*F->k)){
		for(y=F->centerY-2.0/F->k;y<=F->centerY+2.0/F->k;y+=4.0/(Screen->h*F->k)){
			deep=azerty(F,x,y,PRECISION);
			colFact=(Uint8)((PRECISION-deep)*255/PRECISION);
			col=SDL_MapRGB(Screen->format,0.5*colFact,0.6*colFact,colFact);
			setPixel(Screen,X,Y,col);
			//setPixel(Screen,(int)(x*F->pitch)+Screen->w/2,(int)(-y*F->pitch)+Screen->h/2,0xCCCCCC);
			Y++;
		}
		Y=0;
		X++;
	}
	cout << F->Cx << endl;
	//F->Cx+=0.0001;
	SDL_Flip(Screen);
	pthread_mutex_unlock(&F->fractal_mut);
}

void bro(s_fractal *fractal){
	double x,y;
	int X=0;
	int Y=0;
	int deep;
	Uint8 colFact;
	Uint32 col;

	SDL_FillRect(Screen,NULL,0x000000);
	for(F->Cx=F->centerX-2.0/F->k;F->Cx<=F->centerX+2.0/F->k;F->Cx+=4.0/(Screen->h*F->k)){
		for(F->Cy=-2.0/F->k+F->centerY;F->Cy<=2.0/F->k+F->centerY;F->Cy+=4.0/(Screen->h*F->k)){
			deep=azerty(F,0,0,PRECISION);
			setPixel(Screen,X,Y,0x101010*deep);
			Y++;
		}
		Y=0;
		X++;
	}
	F->Cx+=0.01;
	SDL_Flip(Screen);
}

void setPixel(SDL_Surface *surface, int x, int y, Uint32 pixel){

	Uint8 *p;
	int bpp; 
	if(x>=0 && y>=0 && x<surface->w && y<surface->h)
	{
		bpp = surface->format->BytesPerPixel;

		p = (Uint8 *)surface->pixels+y*surface->pitch+x*bpp;

		switch(bpp) 
		{
			case 1:
				*p = pixel;
				break;

			case 2:
				*(Uint16 *)p = pixel;
				break;

			case 3:
				if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
					p[0] = (pixel >> 16) & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = pixel & 0xff;
				} else {
					p[0] = pixel & 0xff;
					p[1] = (pixel >> 8) & 0xff;
					p[2] = (pixel >> 16) & 0xff;
				}
				break;

			case 4:
				*(Uint32 *)p = pixel;
				break;
		}
	}
}

double f_rand(){
return (rand()%(201))/100.0-1.0;
}
