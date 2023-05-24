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
            if(pixels[y*sizex+ x] == relief_beach(format))
            {
                int prob = rand()%500;
                if(prob < 1)
                {
                    int x0 = x;
                    int y0 = y;
                    int c = 200;

                    while(c > 0 && x0-1>0 && y0-1>0&&x0+1<sizex&&y0+1<sizey)
                    {
                        if(pixels[x0+y0*sizex] == ocean(format) 
                            || pixels[x0+y0*sizex] == coast(format))
                            break;
                        int nmb = rand()%50;
                        /*if( nmb < 10&& pixels[x0+1+(y0+1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0+1;
                            c--;
                        }*/
                        if(nmb < 10 && pixels[x0+1+(y0)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0;
                            c--;
                        }
                        else if(nmb<20 && pixels[x0+1+(y0-1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0+1;
                            y0 = y0-1;
                            c--;
                        }

                        /*else if(nmb<40 && pixels[x0+(y0+1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0;
                            y0 = y0+1;
                            c--;
                        }*/
                        else if(nmb<30 && pixels[x0+(y0-1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0;
                            y0 = y0-1;
                            c--;
                        }
                        /*else if(nmb<60 && pixels[x0-1+(y0+1)*sizex]!=ocean(format))
                        {
                            pixels[y0*sizex+x0] = ocean(format);
                            x0 = x0-1;
                            y0 = y0+1;
                            c--;
                        }*/
                        else if(nmb<40 && pixels[x0-1+(y0)*sizex]!=ocean(format))
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

void flooding(SDL_Surface* image, SDL_Surface* perlin, struct options* opt,
                int x, int y, int max,int c)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;

    if(c==10)
        return;

    
    SDL_PixelFormat* format = image->format;
    Uint32* pixels = image->pixels;
    Uint32* P_pixels = perlin->pixels;
    int coeff[] = {-1,0,1};
    

    for(int i = 0; i<3; i++)
    {
        for(int j = 0; j<3; j++)
        {
            if(x+coeff[i] < 0 || x+coeff[i] > sizex 
                || y+coeff[i] < 0 || y+coeff[i] > sizey || pixels[(y+coeff[j])*sizex+x+coeff[i]] == river2(format))
                continue;
            Uint8 r,g,b;
            Uint32 cur = P_pixels[(y+coeff[j])*sizex+(x+coeff[i])];
            SDL_GetRGB(cur,format,&r,&g,&b);

            //if(r <= 118)
            //    continue;
            //printf("not max :%d, %d\n\n",i, j);
            if(r < max)
            {
                //printf("in flood :%d, %d, %d, %d, %d, %d, %d, %d\n\n",opt,x+coeff[i],y+coeff[j],r , i, j, max, c);
                pixels[(y+coeff[j])*sizex+x+coeff[i]] = river2(format);
                flooding(image,perlin,opt,x+coeff[i],y+coeff[j],max,c+1);
            }
        }
    }
}

void draw_riviere2(SDL_Surface* image, SDL_Surface* perlin, struct options* opt)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;

    SDL_LockSurface(image);
    SDL_PixelFormat* format = image->format;
    Uint32* pixels = image->pixels;
    Uint32* P_pixels = perlin->pixels;

    for(int y = 0; y<sizey; y++)
    {
        for(int x = 0; x<sizex; x++)
        {
            if(pixels[y*sizex+ x] == relief_mountains(format))
            {
                int prob = rand()%500;
                if(prob < 2)
                {
                    printf("River x = %d / y = %d\n",x,y);
                    int xp = x;
                    int yp = y;
                    int x0 = x;
                    int y0 = y;
                    int lake = 0;
                    while(pixels[y0*sizex+x0]!=relief_beach(format) 
                    && pixels[y0*sizex+x0]!=coast(format) && !lake)
                    {
                        pixels[y0*sizex+x0] = river2(format);
                        int coeff[] = {-1,0,1};
                        
                        int minx = x0;
                        int miny = y0;
                        int min_val = 256;

                        for(int i = 0; i<3; i++)
                        {
                            for(int j = 0; j<3; j++)
                            {
                                
                                if((y0)*sizex+(x0) == 
                                        (y0+coeff[j])*sizex+(x0+coeff[i]))
                                    continue;
                                if(x0+coeff[i] < 0 || x0+coeff[i] > sizex 
                                    || y0+coeff[i] < 0 || y0+coeff[i] > sizey)
                                    continue;
                                if((y0+coeff[j])*sizex+(x0+coeff[i]) 
                                            == (yp)*sizex+(xp))
                                    continue;
                                if(pixels[(y0+coeff[j])*sizex+(x0+coeff[i])] 
                                            == river2(format))
                                    continue;
                                Uint8 r,g,b;
                                Uint32 cur = 
                                    P_pixels[(y0+coeff[j])*sizex+(x0+coeff[i])];
                                SDL_GetRGB(cur,format,&r,&g,&b);

                                if (r < min_val)
                                {

                                    minx = x0 + coeff[i];
                                    miny = y0 + coeff[j];
                                    min_val = r;
                                }
                            }
                        }
                        Uint8 r2,g2,b2;
                        Uint32 cur2 = 
                            P_pixels[(y0)*sizex+(x0)];
                        SDL_GetRGB(cur2,format,&r2,&g2,&b2);
                        if (r2<min_val)
                        {
                            flooding(image,perlin,opt,x0,y0,r2+2,0);
                            lake = 1;
                            break;
                        }
                        xp = x0;
                        yp = y0;
                        
                        x0 = minx;
                        y0 = miny;
                        
                    }
                }
            }
        }
    }

    SDL_UnlockSurface(image);
}
