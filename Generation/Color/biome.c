#include "../Utils/utils.h"
#include "color.h"
#include "biome.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
                else
                {
                    c=snow(format);
                }
            }
            else if(rt<threshold->plains)
            {
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
                else if(rh>= threshold->coast && rh <120)
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
                else if (rh>=140 && rh<155)
                {
                    c = plains2(format);
                }
                else if(rh>=135&&rh<140)
                {
                    c= plains3(format);
                }
                else 
                {
                    c = plains(format);
                }
            }
            else if(rt <threshold->savanna)
            {
                if(rh<90)
                {
                    c = deep_ocean(format);
                }
                else if(rh<110)
                {
                    c = ocean(format);
                }

                else if(rh<118)
                {
                    c = coast(format);
                }
                else if(rh>= 118 && rh <120)
                {
                    c = beach(format);
                }
                else if(rh<130 && rh>=125)
                {
                    c = savanna(format);
                }
                else if(rh>=130&&rh<155)
                {
                    c = savanna2(format);
                }
                else if(rh<160)
                {
                    c = mid_mountains_desert(format);
                }
                
                else
                {
                    c = mountains_desert(format);
                }
            }
            else
            {
                if(rh<90)
                {
                    c = deep_ocean(format);
                }
                else if(rh<110)
                {
                    c = ocean(format);
                }

                else if(rh<118)
                {
                    c = coast(format);
                }
                else if(rh>= 118 && rh <125)
                {
                    c = beach(format);
                }
                else if(rh<155)
                {
                    c = desert(format);
                }
                else if(rh<160)
                {
                    c = mid_mountains_desert(format);
                }
                else
                {
                    c = mountains_desert(format);
                }
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

