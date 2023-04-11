#ifndef PROPS_H__
#define PROPS_H__



#include "../Utils/utils.h"


struct type_structure** apply_props(SDL_Surface *map, struct chunk **chunk_map, 
        struct options* opt);

#endif
