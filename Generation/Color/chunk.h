#ifndef CHUNK_H__
#define CHUNK_H__


#include "../Utils/utils.h"

typedef struct chunk
{
    int xmin;
    int ymin;
    int xmax;
    int ymax;
    int id_biome;
}chunk;

struct chunk **define_chunk(SDL_Surface *height, SDL_Surface *temp,
        int sizex, int sizey);

void print_chunk(struct chunk **chunk_map, int sizex,int sizey);

#endif
