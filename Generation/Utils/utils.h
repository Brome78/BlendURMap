#pragma once

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define TREE 0
#define BUSH 1
#define CACTUS 2
#define ACACIA 3
#define SPRUCE 4
#define BIRCH 5
#define VILLAGE 6

typedef struct vector2
{
    int x;
    int y;
}vector2;

typedef struct options
{
    int sizex;
    int sizey;
    int resolution;
    int octave;
    double frequence;
    double persistence;
    int range;
}options;

typedef struct map
{
    SDL_Surface* map;
    int seed;
}map;

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
    int plateau;
    int plateau2;
    int plateau3;
    int swamp;
}threshold;

typedef struct chunk
{
    int xmin;
    int ymin;
    int xmax;
    int ymax;
    int id_biome;
}chunk;

typedef struct structure{
    int sizex;
    int sizey;
    SDL_Surface* scheme;
}structure;

typedef struct type_structure{
    int x;
    int y;
    int type;
}type_structure;

typedef struct current_map{
    struct options* opt_alt;
    struct options* opt_hum;
    SDL_Surface* perlin;
    SDL_Surface* simplex;
    SDL_Surface* ds;
}current_map;

SDL_Surface* load_image(const char* path);

void save_image(SDL_Surface* surface, const char* path);

int** to_rows(SDL_Surface* s);

void save_to_png(SDL_Surface* surface, const char* path); 
