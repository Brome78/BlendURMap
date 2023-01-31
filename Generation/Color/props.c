#include "../Utils/utils.h"

Uint32 log_c(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,  120, 66, 18 );
}
Uint32 leave_c(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format, 30, 173, 8 );
}

int draw_bush(SDL_Surface *map, int x, int y, int sizex, int sizey)
{
    if (x-3 < 0 || y-3 < 0 || x+3 > sizex || y+3 > sizey)
    {
        return 0;
    }

    Uint32 *pixels = map->pixels;
    SDL_LockSurface(map);

    SDL_PixelFormat* format = map->format;

    Uint32 c = log_c(format);
    Uint32 c2 = leave_c(format);
    /*for(int i = 0; i<y+200; i++)
    {
        for(int j = 0; j<x+200;j++)
        {
            pixels[i*sizex+j] = c;
        }
    }*/
    pixels[y*sizex+x] = c;
    pixels[(y-1)*sizex+x] = c;
    pixels[(y-2)*sizex+x] = c2;
    pixels[(y-2)*sizex+x+1] = c2;
    pixels[(y-2)*sizex+x-1] = c2;

    pixels[(y-3)*sizex+x] = c2;

    return 1;
}
