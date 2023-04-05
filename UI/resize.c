#include "resize.h"

#include <stdio.h>
#include <math.h>
//#include <stdlib.h>

SDL_Surface *resize_image(SDL_Surface *surface,int w2,int h2)
{

    SDL_Rect dstrect;

    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = w2;
    dstrect.h = h2;

    SDL_Surface *new_surface = SDL_CreateRGBSurface(0,w2,h2,32,0,0,0,0);
    SDL_BlitSurface(surface, NULL, new_surface, &dstrect);
    return new_surface;
}

void resize(const char* input_image, const char* output_image, int w, int h)
{
    SDL_Surface *surface = IMG_Load(input_image);
    SDL_Surface *new_surface = resize_image(surface,w,h);
    IMG_SavePNG(new_surface, output_image);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(new_surface);
}
