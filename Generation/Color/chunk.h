#ifndef CHUNK_H__
#define CHUNK_H__


#include "../Utils/utils.h"
#include "biome.h"

typedef struct chunk
{
    int xmin;
    int ymin;
    int xmax;
    int ymax;
    int id_biome;
}chunk;

struct chunk **define_chunk(SDL_Surface *height, SDL_Surface *temp,
        struct options* opt, struct threshold* t);

void free_chunk(struct chunk **chunk_map, struct options* opt);

void print_chunk(struct chunk **chunk_map, struct options* opt);

#endif
