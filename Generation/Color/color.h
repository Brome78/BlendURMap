#ifndef COLOR_H__
#define COLOR_H__


#include "../Utils/utils.h"

#define DEEP_OCEAN 1
#define OCEAN 2
#define COAST 3
#define PLAINS 4
#define MID_MOUNTAINS 5
#define MOUNTAINS 6
#define PICKS 7
#define DESERT 8
#define SAVANNA 9
#define FREEZE_PLAINS 10
#define BEACH 11
#define FOREST 12

Uint32 plains2(SDL_PixelFormat* format);
Uint32 plains(SDL_PixelFormat* format);
Uint32 desert(SDL_PixelFormat* format);

SDL_Surface* apply_biome(SDL_Surface* heightmap, SDL_Surface* tempmap,
        int sizex, int sizey);

SDL_Surface* draw_riviere(SDL_Surface* image,SDL_Surface* heightmap, int sizex, int sizey);

#endif
