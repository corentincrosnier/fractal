#include "event.h"

void event(s_fractal *fractal){
	SDL_Event event;
while(!fractal->stop){
		SDL_PollEvent(&event);
		//SDL_Flip(fractal->screen);
		switch(event.type){
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym){
					case SDLK_ESCAPE:
						fractal->stop=1;
					break;
					case SDLK_r:
						cout << "ozef" << endl;
						pthread_mutex_lock(&fractal->fractal_mut);
						fractal->centerX=0;
						fractal->centerY=0;
						fractal->k=1;
						fractal->pitch=fractal->k*fractal->screen->h/4;
						pthread_mutex_unlock(&fractal->fractal_mut);
					break;
					case SDLK_KP_PLUS:
						pthread_mutex_lock(&fractal->fractal_mut);
						fractal->k+=1;
						//fractal->pitch=fractal->k*fractal->screen->h/4;
						pthread_mutex_unlock(&fractal->fractal_mut);
					break;
					case SDLK_KP_MINUS:
						pthread_mutex_lock(&fractal->fractal_mut);
						fractal->k-=2;
						//fractal->pitch=fractal->k*fractal->screen->h/4;
						pthread_mutex_unlock(&fractal->fractal_mut);
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				pthread_mutex_lock(&fractal->fractal_mut);
				fractal->centerX=(event.button.x-fractal->screen->w/2)*4.0/(Screen->h*F->k);
				fractal->centerY=(-event.button.y+fractal->screen->h/2)*4.0/(Screen->h*F->k);
				fractal->pitch=fractal->k*fractal->screen->h/4;
				pthread_mutex_unlock(&fractal->fractal_mut);
				switch(event.button.button){
					case SDL_BUTTON_LEFT:
						pthread_mutex_lock(&fractal->fractal_mut);
						fractal->k+=1;
						pthread_mutex_unlock(&fractal->fractal_mut);
					break;
					case SDL_BUTTON_RIGHT:
						pthread_mutex_lock(&fractal->fractal_mut);
						fractal->k-=1;
						pthread_mutex_unlock(&fractal->fractal_mut);
					break;
				}
			break;
			case SDL_VIDEORESIZE:
				pthread_mutex_lock(&fractal->fractal_mut);
				fractal->screen=SDL_SetVideoMode(event.resize.w,event.resize.h,32,SDL_DOUBLEBUF | SDL_RESIZABLE);
				fractal->pitch=fractal->k*fractal->screen->h/4;
				pthread_mutex_unlock(&fractal->fractal_mut);
			break;
		}
	}
}
