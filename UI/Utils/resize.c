#include <stdio.h>
#include <math.h>
#include "../../Generation/Utils/utils.h"

SDL_Surface *resize_image(SDL_Surface *surface,int w2,int h2) {
    Uint32 *pixels = surface->pixels;
    int w1 = surface->w;
    int h1 = surface->h;
    if(w1>h1)
    {
        h2 = (h1*w2)/w1;
    }
    if(w1<h1)
    {
        w2 = (w1*h2)/h1;
    }
    SDL_Surface *new_surface = SDL_CreateRGBSurface(0,w2,h2,32,0,0,0,0);

    int error = SDL_LockSurface(surface);
    if(error)
    {
        errx(EXIT_FAILURE, "resize_image(LockSurface): %s", SDL_GetError());
    }
    SDL_LockSurface(new_surface);

    int *temp = new_surface->pixels;
    double x_ratio = w1/(double)w2;
    double y_ratio = h1/(double)h2;
    double px, py ;
    for (int i=0;i<h2;i++) {
        for (int j=0;j<w2;j++) {
            px = floor(j*x_ratio);
            py = floor(i*y_ratio);
            temp[(i*w2)+j] = pixels[(int)((py*w1)+px)];
        }
    }
    SDL_UnlockSurface(surface);
    SDL_UnlockSurface(new_surface);
    return new_surface;
}

void resize(const char* input_image, const char* output_image, int w, int h)
{
    SDL_Surface *surface = load_image(input_image);
    SDL_Surface *new_surface = resize_image(surface,w,h);
    save_image(new_surface, output_image);
    SDL_FreeSurface(surface);
    SDL_FreeSurface(new_surface);
}
