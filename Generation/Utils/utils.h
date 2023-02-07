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

SDL_Surface* load_image(const char* path);

void save_image(SDL_Surface* surface, const char* path);

int** to_rows(SDL_Surface* s);

void bmp_to_png(char* input,char* output); 
