#include "../Utils/utils.h"
#include "color.h"
#include "biome.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

Uint32 snow_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        c = freeze_deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        c = freeze_ocean(format);
    }
    else if(rh<threshold->coast)
    {
        c = freeze_coast(format);
    }
    else if(rh >= threshold->picks)
    {
        c = picks(format);
    }
    else if(rh>=threshold->mountains)
    {
        c = mountains(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        c = mid_mountains(format);
    }
    else if (rh>=threshold->plateau2 && rh<threshold->mid_mountains)
    {
        c = snow2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        c = snow3(format);
    }
    else
    {
        c = snow(format);
    }
    return c;

}

Uint32 plains_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        c = deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        c = ocean(format);
    }
    else if(rh<threshold->coast)
    {
        c = coast(format);
    }
    else if(rh>= threshold->coast && rh <threshold->plateau)
    {
        c = beach(format);
    }
    else if(rh >= threshold->picks)
    {
        c = picks(format);
    }
    else if(rh>=threshold->mountains)
    {
        c = mountains(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        c = mid_mountains(format);
    }
    else if (rh>=threshold->plateau2 && rh<threshold->mid_mountains)
    {
        c = plains2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        c= plains3(format);
    }
    else
    {
        c = plains(format);
    }
    return c;
}

Uint32 savanna_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        c = deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        c = ocean(format);
    }

    else if(rh<threshold->coast)
    {
        c = coast(format);
    }
    else if(rh>= threshold->coast && rh <threshold->plateau)
    {
        c = beach(format);
    }
    else if(rh>=threshold->mountains)
    {
        c = mountains_desert(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        c = mid_mountains_desert(format);
    }
    else if(rh>=threshold->plateau2&&rh<threshold->mid_mountains)
    {
        c = savanna2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        c= savanna3(format);
    }
    else
    {
        c = savanna(format);
    }
    return c;
}

Uint32 desert_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        c = deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        c = ocean(format);
    }

    else if(rh<threshold->coast)
    {
        c = coast(format);
    }
    else if(rh>= threshold->coast && rh <threshold->plateau)
    {
        c = beach(format);
    }
    else if(rh>=threshold->mountains)
    {
        c = mountains_desert(format);
    }

    else if(rh>=threshold->mid_mountains)
    {
        c = mid_mountains_desert(format);
    }
    else if(rh>=threshold->plateau2&&rh<threshold->mid_mountains)
    {
        c = desert2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        c= desert3(format);
    }
    else
    {
        c = desert(format);
    }
    return c;
}

SDL_Surface* apply_biome(SDL_Surface* heightmap, SDL_Surface* tempmap,
        struct options* opt, struct threshold *threshold)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;

    Uint32* height_pixels = heightmap->pixels;
    Uint32* temp_pixels = tempmap->pixels;
    SDL_Surface* image = SDL_CreateRGBSurface(0,sizex,sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    SDL_PixelFormat* format = image->format;

    for(int y = 0; y<sizey; y++)
    {
        for(int x = 0; x<sizex; x++)
        {
            Uint8 rh,gh,bh;
            Uint8 rt,gt,bt;
            SDL_GetRGB(height_pixels[y*sizex+x],format,&rh,&gh,&bh);
            SDL_GetRGB(temp_pixels[y*sizex+x],format, &rt,&gt,&bt);
            Uint32 c = ocean(format);
            if (rt<threshold->snow)
            {
                c = snow_alt_filter(rh,format,threshold);    
            }
            else if(rt<threshold->plains)
            {
                c = plains_alt_filter(rh,format,threshold);
            }
            else if(rt <threshold->savanna)
            {
                c = savanna_alt_filter(rh, format, threshold);
            }
            else
            {
                c = desert_alt_filter(rh, format, threshold);
            }
            if(y+1<sizey&&rh==155&&c==mid_mountains(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_mountains(format);
            }
            else if(y+1<sizey&&rh==155&&c==mid_mountains_desert(format))
            {
                pixels[y*sizex+x] = c;
                pixels[(y+1)*sizex+x]=relief_desert(format);
            }

            else if(y+1<sizey&&rh==118&&c==beach(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_beach(format);

            }
            else if(y+1<sizey&&rh==160&&c==mountains(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_mountains(format);
            }

            else if(y+1<sizey&&rh==160&&c==mountains_desert(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_desert(format);
            }
            else if(pixels[y*sizex+x] == relief_mountains(format)&&
                    ((rh>155 && rh<159) ||rh>160))
            {
                pixels[y*sizex+x] = c;
            }
            else if(pixels[y*sizex+x] == relief_desert(format)&&
                    ((rh>155 && rh<159)||rh>160))
            {
                pixels[y*sizex+x] = c;
            }

            else if(pixels[y*sizex+x] == relief_beach(format)&&rh>118)
                pixels[y*sizex+x] = c;

            else if(pixels[y*sizex+x]!=relief_mountains(format)&&
                    pixels[y*sizex+x]!=relief_beach(format)&&
                    pixels[y*sizex+x]!=relief_desert(format))
                pixels[y*sizex+x] =c;
        }
    }
    SDL_UnlockSurface(image);
    return image;
}

