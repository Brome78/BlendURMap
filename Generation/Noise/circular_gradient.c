#include "../Utils/utils.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "circular_gradient.h"

/*void apply_island(struct map* map, struct opt* opt)
{
    return;
}*/

struct map* generate_circ_gradient(struct options* opt)
{
    SDL_Surface* image = SDL_CreateRGBSurface(0,opt->sizex,opt->sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;

    SDL_PixelFormat* format = image->format;

    int center_x = opt->sizex / 2;
    int center_y = opt->sizey / 2;

    int max = center_x*center_x + center_y*center_y;
    for(int y = 0; y<opt->sizey; y++)
    {
        for(int x = 0; x<opt->sizex; x++)
        {
            int distx = x- center_x;
            int disty = y-center_y;
            float c = distx*distx + disty*disty;

            //printf("max = %d\n\n",max);
            //printf("c before = %f\n",c);
            c = (c/max)*254;
            //printf("c inter = %f\n",c);
            pixels[y*opt->sizex+x] = SDL_MapRGB(format,(int)c,(int)c,(int)c);
        }
    }

    SDL_UnlockSurface(image);
    struct map* map = malloc(sizeof(struct map));
    map->map = image;
    map->seed = NULL;

    return map;
}
