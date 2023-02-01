#include "../Utils/utils.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

Uint32 mid_mountains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,120,120,120);
}

Uint32 plains2(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0,102,51);
}

Uint32 plains3(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0, 130, 0 );
}

Uint32 plains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,58, 148, 45);
}

Uint32 low_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,198, 175, 109);
}

Uint32 desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,198, 175, 109);
}

Uint32 mid_mountains_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,183, 149, 11 );
}

Uint32 mountains_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,185, 119, 14);
}
Uint32 savanna(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,146, 164, 90 );
}

Uint32 savanna2(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,111, 127, 68 );
}

Uint32 snow(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,214, 234, 248);
}

Uint32 freeze_ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,127, 179, 213);
}
Uint32 freeze_coast(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,169, 204, 227);
}
Uint32 freeze_deep_ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,41, 128, 185);
}
Uint32 relief_mountains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,70, 70, 70);
}
Uint32 relief_beach(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,41, 128, 185);
}
Uint32 relief_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,165,100,0);
}


SDL_Surface* apply_biome(SDL_Surface* heightmap, SDL_Surface* tempmap,
        int sizex, int sizey)
{
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
            if (rt<115)
            {
                if(rh<90)
                {
                    c = freeze_deep_ocean(format);
                }
                else if(rh<110)
                {
                    c = freeze_ocean(format);
                }
                else if(rh<118)
                {
                    c = freeze_coast(format);
                }
                /*else if(rh>= 118 && rh <125)
                {
                    c = beach(format);
                }*/
                else if(rh >= 170)
                {
                    c = picks(format);
                }
                else if(rh>=160)
                {
                    c = mountains(format);
                }
                else if(rh>=155)
                {
                    c = mid_mountains(format);
                }
                else
                {
                    c=snow(format);
                }
            }
            else if(rt<140)
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
                else if(rh >= 170)
                {
                    c = picks(format);
                }
                else if(rh>=160)
                {
                    c = mountains(format);
                }
                else if(rh>=155)
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
            else if(rt <155)
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


SDL_Surface* draw_riviere(SDL_Surface* image,SDL_Surface* heightmap, int sizex, int sizey)
{
    SDL_LockSurface(image);
    SDL_PixelFormat* format = image->format;
    Uint32* pixels = image->pixels;
    Uint32* h = heightmap->pixels;
    srand(time(NULL));
    for(int y = 0; y<sizey; y++)
    {
        for(int x = 0; x<sizex; x++)
        {
            if(pixels[y*sizex+ x] == ocean(format))
            {
                int prob = rand()%100;
                if(prob < 10)
                {
                    int x0 = x;
                    
                    int y0 = y;
                    
                    char End = 0;
                    while(!End && x0-1>0 && y0-1>0&&x0+1<sizex&&y0+1<sizey)
                    {
                        if(h[x0+1+(y0+1)*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0+1;
                        }
                        else if(h[x0+1+y0*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0;
                        }
                        else if(h[x0+1+(y0-1)*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0-1;
                        }

                        else if(h[x0 + (y0+1)*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0;
                            y0 = y0+1;
                        }
                        else if(h[x0+(y0-1)*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0;
                            y0 = y0-1;
                        }
                        else if(h[x0-1+(y0+1)*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0-1;
                            y0 = y0+1;
                        }
                        else if(h[x0-1+y0*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0-1;
                            y0 = y0;
                        }
                        else if(h[x0-1+(y0-1)*sizex]>h[x0+y0*sizex])
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0-1;
                            y0 = y0-1;
                        }
                        else
                        {
                            End = 1;
                        }

                        
                    }
                }
            }
        }
    }
    SDL_UnlockSurface(image);
    return image;
}

