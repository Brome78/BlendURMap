#ifndef PROPS_H__
#define PROPS_H__



#include "../Utils/utils.h"

int draw_tree(SDL_Surface *map, int x, int y, int sizex, int sizey);
int apply_props(SDL_Surface *map, struct chunk **chunk_map, 
        int sizex, int sizey);

#endif
