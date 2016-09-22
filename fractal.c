#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>

#define ANCHO 1280  
#define ALTO 720

SDL_Surface *screen=NULL;

void lineas(float x1,float y1,float x2,float y2)
{
	float m, tmp, inc=0.1, y;
	m=(y2-y1)/(x2-x1);
	if(x1>x2)
		for(;x2<=x1;x2=x2+inc)
		{
			y=m*x2-m*x1+y1;
			SDL_Rect punto={x2+ANCHO/3,(ALTO/3-y),1,1};
			SDL_FillRect(screen, &punto, SDL_MapRGBA(screen->format,0,255,0,0));	
		}
	else
		for(;x1<=x2;x1=x1+inc)
		{
			y=m*x1-m*x2+y2;
			SDL_Rect punto={x1+ANCHO/3,(ALTO/3-y),1,1};
			SDL_FillRect(screen, &punto, SDL_MapRGBA(screen->format,0,255,0,0));
			
		}
		SDL_Flip(screen);

}

void fractal(float x1, float y1, float x2, float y2, int n, int ang)
{
	if(n==0)
	{
		lineas(x1,y1,x2,y2);
		return;
	}
	float xp,yp,d;
	d=(sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) ) );

	xp=x1+(d/3)*cos(ang*3.1416/180);
	yp=y1+(d/3)*sin(ang*3.1416/180);

	fractal(x1,y1,xp,yp,n-1,ang);

	x1=xp+(d/3)*cos((ang+60)*3.1416/180);
	y1=yp+(d/3)*sin((ang+60)*3.1416/180);

	fractal(xp,yp,x1,y1,n-1,ang+60);

	xp=xp+(d/3)*cos(ang*3.1416/180);
	yp=yp+(d/3)*sin(ang*3.1416/180);

	fractal(x1,y1,xp,yp,n-1,ang+300);

	fractal(xp,yp,x2,y2,n-1,ang);

}

int main()
{
	int n; 
	float tam=500;
	
	printf("Numero de iteraciones: ");
	scanf("%d", &n);
	
	if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 ) 
		exit(0);	
   
    SDL_WM_SetCaption("FRACTAL", NULL);
	screen = SDL_SetVideoMode(ANCHO,ALTO,24, SDL_SWSURFACE);
	if(screen == NULL)
	{
		printf("No se ha podido establecer el modo de vídeo: %s\n", SDL_GetError());
		exit(1);
	}
	
	fractal(0,0,tam,0,n,0);
	
	fractal(tam,0,tam/2,tam*sin(300*3.1416/180),n,240);
	
	fractal(tam/2,tam*sin(300*3.1416/180),0,0,n,120);
	
	SDL_Flip(screen);
	SDL_Delay(7000);
    SDL_Quit();
	return 0;
}

