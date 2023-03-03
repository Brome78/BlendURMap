#include "../Utils/utils.h"
#include "../Color/color.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


SDL_Surface* draw_riviere(SDL_Surface* image, struct options* opt)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;

    SDL_LockSurface(image);
    SDL_PixelFormat* format = image->format;
    Uint32* pixels = image->pixels;
    for(int y = 0; y<sizey; y++)
    {
        for(int x = 0; x<sizex; x++)
        {
            if(pixels[y*sizex+ x] == ocean(format))
            {
                int prob = rand()%7000;
                if(prob < 1)
                {
                    int x0 = x;
                    int y0 = y;
                    int c = 500;

                    while(c > 0 && x0-1>0 && y0-1>0&&x0+1<sizex&&y0+1<sizey)
                    {
                        int nmb = rand()%80;
                        if( nmb < 10&& pixels[x0+1+(y0+1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0+1;
                            c--;
                        }
                        else if(nmb < 20 && pixels[x0+1+(y0)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0;
                            c--;
                        }
                        else if(nmb<30 && pixels[x0+1+(y0-1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0-1;
                            c--;
                        }

                        else if(nmb<40 && pixels[x0+(y0+1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0;
                            y0 = y0+1;
                            c--;
                        }
                        else if(nmb<50 && pixels[x0+(y0-1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0;
                            y0 = y0-1;
                            c--;
                        }
                        else if(nmb<60 && pixels[x0-1+(y0+1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0-1;
                            y0 = y0+1;
                            c--;
                        }
                        else if(nmb<70 && pixels[x0-1+(y0)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0-1;
                            y0 = y0;
                            c--;
                        }

                        else
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0-1;
                            y0 = y0-1;
                            c--;
                        }

                    }
                }
            }
        }
    }
    SDL_UnlockSurface(image);
    return image;
}

