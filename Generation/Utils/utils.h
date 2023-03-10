#pragma once

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

SDL_Surface* load_image(const char* path);

void save_image(SDL_Surface* surface, const char* path);

int** to_rows(SDL_Surface* s);

void save_to_png(SDL_Surface* surface, const char* path); 
