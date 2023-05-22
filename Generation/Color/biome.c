#include "../Utils/utils.h"
#include "color.h"
#include "color_mindustry.h"
#include "biome.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

Uint32 snow_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold, char export)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        if(export)
            c = m_freeze_deep_ocean(format);
        else
            c = freeze_deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        if(export)
            c = m_freeze_ocean(format);
        else
            c = freeze_ocean(format);
    }
    else if(rh<threshold->coast)
    {
        if(export)
            c = m_freeze_coast(format);
        else
            c = freeze_coast(format);
    }
    else if(rh >= threshold->picks)
    {
        if(export)
            c = m_picks(format);
        else
            c = picks(format);
    }
    else if(rh>=threshold->mountains)
    {
        if(export)
            c = m_mountains(format);
        else
            c = mountains(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        if(export)
            c = m_snow2(format);
        else
            c = mid_mountains(format);
    }
    else if (rh>=threshold->plateau2 && rh<threshold->mid_mountains)
    {
        if(export)
            c = m_snow2(format);
        else
            c = snow2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        if(export)
            c = m_snow3(format);
        else
            c = snow3(format);
    }
    else
    {
        if(export)
            c = m_snow(format);
        else
            c = snow(format);
    }
    return c;

}

Uint32 plains_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold, char export)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        if(export)
            c = m_deep_ocean(format);
        else
            c = deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        if(export)
            c = m_ocean(format);
        else
            c = ocean(format);
    }
    else if(rh<threshold->coast)
    {
        if(export)
            c = m_coast(format);
        else
            c = coast(format);
    }
    else if(rh <threshold->beach)
    {
        if(export)
            c = m_beach(format);
        else
            c = beach(format);
    }
    else if(rh >= threshold->picks)
    {
        if(export)
            c = m_picks(format);
        else
            c = picks(format);
    }
    else if(rh>=threshold->mountains)
    {
        if(export)
            c = m_mountains(format);
        else
            c = mountains(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        if(export)
            c = m_mid_mountains(format);
        else
            c = mid_mountains(format);
    }
    else if (rh>=threshold->plateau2 && rh<threshold->mid_mountains)
    {
        if(export)
            c = m_plains2(format);
        else
            c = plains2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        if(export)
            c = m_plains3(format);
        else
            c= plains3(format);
    }
    else
    {
        if(export)
            c = m_plains(format);
        else
            c = plains(format);
    }
    return c;
}

Uint32 savanna_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold, char export)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        if(export)
            c = m_deep_ocean(format);
        else
            c = deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        if(export)
            c = m_ocean(format);
        else
            c = ocean(format);
    }
    else if(rh<threshold->coast)
    {
        if(export)
            c = m_coast(format);
        else
            c = coast(format);
    }
    else if(rh <threshold->beach)
    {
        if(export)
            c = m_beach(format);
        else
            c = beach(format);
    }
    else if(rh>=threshold->mountains)
    {
        if(export)
            c = m_mountains_desert(format);
        else
            c = mountains_desert(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        if(export)
            c = m_mid_mountains_desert(format);
        else
            c = mid_mountains_desert(format);
    }
    else if(rh>=threshold->plateau2&&rh<threshold->mid_mountains)
    {
        if(export)
            c = m_savanna2(format);
        else
            c = savanna2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        if(export)
            c = m_savanna3(format);
        else
            c= savanna3(format);
    }
    else
    {
        if(export)
            c = m_savanna(format);
        else
            c = savanna(format);
    }
    return c;
}

Uint32 desert_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold, char export)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        if(export)
            c = m_deep_ocean(format);
        else
            c = deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        if(export)
            c = m_ocean(format);
        else
            c = ocean(format);
    }
    else if(rh<threshold->coast)
    {
        if(export)
            c = m_coast(format);
        else
            c = coast(format);
    }
    else if(rh <threshold->beach)
    {
        if(export)
            c = m_beach(format);
        else
            c = beach(format);
    }
    else if(rh>=threshold->mountains)
    {
        if(export)
            c = m_mountains_desert(format);
        else
            c = mountains_desert(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        if(export)
            c = m_mid_mountains_desert(format);
        else
            c = mid_mountains_desert(format);
    }
    else if(rh>=threshold->plateau2&&rh<threshold->mid_mountains)
    {
        if(export)
            c = m_desert2(format);
        else
            c = desert2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        if(export)
            c = m_desert3(format);
        else
            c= desert3(format);
    }
    else
    {
        if(export)
            c = m_desert(format);
        else
            c = desert(format);
    }
    return c;
}

Uint32 swamp_alt_filter(Uint8 rh, SDL_PixelFormat* format,
        struct threshold* threshold, char export)
{
    Uint32 c = ocean(format);
    if(rh<threshold->deep_ocean)
    {
        if(export)
            c = m_deep_ocean(format);
        else
            c = deep_ocean(format);
    }
    else if(rh<threshold->ocean)
    {
        if(export)
            c = m_ocean(format);
        else
            c = ocean(format);
    }
    else if(rh<threshold->coast)
    {
        if(export)
            c = m_coast(format);
        else
            c = coast(format);
    }
    else if(rh <threshold->beach)
    {
        if(export)
            c = m_beach(format);
        else
            c = beach(format);
    }
    else if(rh>=threshold->mountains)
    {
        if(export)
            c = m_mountains_desert(format);
        else
            c = mountains_desert(format);
    }
    else if(rh>=threshold->mid_mountains)
    {
        if(export)
            c = m_mid_mountains_desert(format);
        else
            c = mid_mountains_desert(format);
    }
    else if(rh>=threshold->plateau2&&rh<threshold->mid_mountains)
    {
        if(export)
            c = m_swamp2(format);
        else
            c = swamp2(format);
    }
    else if(rh>=threshold->plateau3 && rh<threshold->plateau2)
    {
        if(export)
            c = m_swamp3(format);
        else
            c= swamp3(format);
    }
    else
    {
        if(export)
            c = m_swamp(format);
        else
            c = swamp(format);
    }
    return c;
}

SDL_Surface* apply_biome(SDL_Surface* heightmap, SDL_Surface* tempmap, 
        SDL_Surface* hummap, struct options* opt, struct options* opt_hum,
        struct threshold *threshold, char export)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;



    Uint32* height_pixels = heightmap->pixels;
    Uint32* temp_pixels = tempmap->pixels;
    Uint32* hum_pixels = hummap->pixels;
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
            Uint8 rhu,ghu,bhu;
            SDL_GetRGB(height_pixels[y*sizex+x],format,&rh,&gh,&bh);
            SDL_GetRGB(temp_pixels[y*sizex+x],format, &rt,&gt,&bt);
            SDL_GetRGB(hum_pixels[y*(opt_hum->sizex)+x],format,&rhu,&ghu,&bhu);
            Uint32 c = ocean(format);
            if (rt<threshold->snow)
            {
                c = snow_alt_filter(rh,format,threshold,export);
            }
            else if(rt<threshold->plains)
            {
                if(rhu<threshold->swamp)
                    c = plains_alt_filter(rh,format,threshold,export);
                else
                    c = swamp_alt_filter(rh,format,threshold,export);
            }
            /*else if(rt <threshold->savanna)
            {
                c = savanna_alt_filter(rh, format, threshold);
            }*/
            else
            {
                if(rhu<threshold->savanna)
                    c = desert_alt_filter(rh, format, threshold,export);
                else
                    c = savanna_alt_filter(rh, format, threshold,export);

            }
            if(y+1<sizey&&rh==threshold->mid_mountains&&c==mid_mountains(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_mountains(format);
            }
            else if(y+1<sizey&&rh==threshold->mid_mountains&&c==mid_mountains_desert(format))
            {
                pixels[y*sizex+x] = c;
                pixels[(y+1)*sizex+x]=relief_desert(format);
            }

            else if(y+1<sizey&&rh==threshold->coast&&c==beach(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_beach(format);

            }
            else if(y+1<sizey&&rh==threshold->mountains&&c==mountains(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_mountains(format);
            }

            else if(y+1<sizey&&rh==threshold->mountains&&c==mountains_desert(format))
            {
                pixels[(y)*sizex+x] = c;
                pixels[(y+1)*sizex+x] = relief_desert(format);
            }
            else if(pixels[y*sizex+x] == relief_mountains(format)&&
                    ((rh>threshold->mid_mountains && rh<threshold->mountains-1) ||rh>threshold->mountains))
            {
                pixels[y*sizex+x] = c;
            }
            else if(pixels[y*sizex+x] == relief_desert(format)&&
                    ((rh>threshold->mid_mountains && rh<threshold->mountains-1)||rh>threshold->mountains))
            {
                pixels[y*sizex+x] = c;
            }

            else if(pixels[y*sizex+x] == relief_beach(format)&&rh>threshold->coast)
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

