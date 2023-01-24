#include "../Utils/utils.h"

Uint32 deep_ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0,0,180);
}

Uint32 ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0,0,255);
}

Uint32 coast(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,25,173,232);
}

Uint32 beach(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,241,230,186);
}

Uint32 picks(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,255,255,255);
}

Uint32 mountains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,90,90,90);
}

Uint32 plains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,58, 148, 45);
}




SDL_Surface* apply_biome(SDL_Surface* heightmap, int sizex, int sizey)
{
    Uint32* height_pixels = heightmap->pixels;
    SDL_Surface* image = SDL_CreateRGBSurface(0,sizex,sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    SDL_PixelFormat* format = image->format;

    for(int y = 0; y<sizey; y++)
    {
        for(int x = 0; x<sizex; x++)
        {
            Uint8 r,g,b;
            SDL_GetRGB(height_pixels[y*sizey+x],format,&r,&g,&b);
            Uint32 c = ocean(format);
            if(r<95)
            {
                c = deep_ocean(format);
            }
            else if(r<110)
            {
                c = ocean(format);
            }
            else if(r<128)
            {
                c = coast(format);
            }
            else if(r>= 128 && r <135)
            {
                c = beach(format);
            }
            else if(r >= 170)
            {
                c = picks(format);
            }
            else if(r>=150)
            {
                c = mountains(format);
            }
            else
            {
                c = plains(format);
            }
            pixels[y*sizey+x] = c;
        }
    }
    SDL_UnlockSurface(image);
    return image;
}
