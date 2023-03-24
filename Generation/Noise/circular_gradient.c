#include "../Utils/utils.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "circular_gradient.h"

void apply_island(struct map* map, struct options* opt)
{
    struct map* circ = generate_circ_gradient(opt);
    SDL_Surface* res = map->map;
    Uint32* pixels = res->pixels;
    Uint32* pixels_circ = circ->map->pixels;
    SDL_PixelFormat* format = res->format;

    for(int y = 0; y<opt->sizey; y++)
    {
        for(int x = 0; x<opt->sizex; x++)
        {
            Uint8 r,g,b;
            Uint8 rc,gc,bc;

            SDL_GetRGB(pixels_circ[y*opt->sizex+x],format,&r,&g,&b);
            SDL_GetRGB(pixels[y*opt->sizex+x],format,&rc,&gc,&bc);
            float tmp = (float)r/255;
            pixels[y*opt->sizex+x] = SDL_MapRGB(format,(int)rc*(tmp),
                    (int)gc*(tmp),(int)bc*(tmp));
        }
    }
    SDL_FreeSurface(circ->map);
    free(circ);
}

struct map* generate_circ_gradient(struct options* opt)
{
    SDL_Surface* image = SDL_CreateRGBSurface(0,opt->sizex,opt->sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;

    SDL_PixelFormat* format = image->format;

    int center_x = opt->sizex / 2;
    int center_y = opt->sizey / 2;

    int max = (center_x*center_x + center_y*center_y);
    for(int y = 0; y<opt->sizey; y++)
    {
        for(int x = 0; x<opt->sizex; x++)
        {
            int distx = x- center_x;
            int disty = y-center_y;
            float c = distx*distx + disty*disty;

            c = 255 - ((c/max)*254);
            pixels[y*opt->sizex+x] = SDL_MapRGB(format,(int)c,(int)c,(int)c);
        }
    }

    


    SDL_UnlockSurface(image);
    struct map* map = malloc(sizeof(struct map));
    map->map = image;

    return map;
}
