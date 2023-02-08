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
    char* seed;
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
}threshold;

typedef struct chunk
{
    int xmin;
    int ymin;
    int xmax;
    int ymax;
    int id_biome;
}chunk;

SDL_Surface* load_image(const char* path);

void save_image(SDL_Surface* surface, const char* path);

int** to_rows(SDL_Surface* s);

void bmp_to_png(char* input,char* output); 
