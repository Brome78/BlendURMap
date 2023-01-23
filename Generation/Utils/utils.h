#pragma once

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct vector2
{
    int x;
    int y;
}vector2;


SDL_Surface* load_image(const char* path);

void save_image(SDL_Surface* surface, const char* path);

