#include <err.h>
#include "utils.h"
SDL_Surface* load_image(const char* path)
{
    SDL_Surface* tmp = IMG_Load(path);
    if(tmp == NULL)
        errx(EXIT_FAILURE, "load_image(IMG_Load): %s", SDL_GetError());

    SDL_Surface* result = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888,
            0);
    if(result == NULL)
        errx(EXIT_FAILURE, "load_image(ConvertSurfaceFormat): %s",
                SDL_GetError());

    SDL_FreeSurface(tmp);
    return result;
}

void save_image(SDL_Surface* surface, const char* path){
    if(SDL_SaveBMP(surface, path))
        errx(EXIT_FAILURE, "save_image(SaveBMP): %s", SDL_GetError());
}

void save_to_png(SDL_Surface* surface, const char* path) 
{
    if(IMG_SavePNG(surface, path))
        errx(EXIT_FAILURE, "save_image(SavePNG): %s", SDL_GetError());

}
