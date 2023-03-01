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




SDL_Surface* draw_riviere(SDL_Surface* image,SDL_Surface* heightmap, int sizex, int sizey)
{
    SDL_LockSurface(image);
    SDL_PixelFormat* format = image->format;
    Uint32* pixels = image->pixels;
    Uint32* h = heightmap->pixels;
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

