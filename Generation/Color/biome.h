#ifndef BIOME_H__
#define BIOME_H__


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

typedef struct threshold{
    int deep_ocean;
    int ocean;
    int coast;
    int beach;
    int mid_mountains;
    int mountains;
    int picks;
    int plains;
    int snow;
    int savanna;
}threshold;

SDL_Surface* apply_biome(SDL_Surface* heightmap, SDL_Surface* tempmap,
        struct options* opt, struct threshold *threshold);



#endif
