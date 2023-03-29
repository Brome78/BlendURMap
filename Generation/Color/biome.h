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



SDL_Surface* apply_biome(SDL_Surface* heightmap, SDL_Surface* tempmap,
        SDL_Surface* hummap, struct options* opt, struct options* opt_hum,
        struct threshold *threshold);



#endif
