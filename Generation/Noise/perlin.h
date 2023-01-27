
#ifndef PERLIN_H__
#define PERLIN_H__

#include "../Utils/utils.h"

typedef struct map
{
    SDL_Surface* map;
    char* seed;
}map;

struct map* perlin_generate(int sizex, int sizey,
        int resolution, char *seed);

#endif
