#include "../Utils/utils.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <stdio.h>

float interpolate(float a0, float a1, float w)
{
    return (a1-a0)*w + a0;
}

void shuffle(int *perm, int size)
{
    int n = size - 1;
    while(n>1)
    {
        int k = rand()%size;
        n--;
        int tmp = perm[n];
        perm[n] = perm[k];
        perm[k] = tmp;
    }

}

double perlin(double x,double y,int resolution,int *perm)
{
    double tmpX;
    double tmpY;
    int x0, y0, ii, jj, gi0, gi1, gi2, gi3;
    double unit = 1.0/sqrt(2);
    double tmp, s, t, u, v, Cx, Cy, Li1, Li2;
    int gradientX = 2;
    double gradient[] = {unit,unit,-unit,unit,unit,-unit,-unit,-unit,
        1,0,-1,0,0,1,0,-1};

    x /= resolution;
    y /= resolution;
    x0 = x;
    y0 = y;

    ii = x0 % 255;
    jj = y0 % 255;

    gi0 = perm[(ii + perm[jj])%255]%8;
    gi1 = perm[(ii + 1 + perm[jj])%255]%8;
    gi2 = perm[(ii + perm[jj + 1])%255]%8;
    gi3 = perm[(ii + 1 + perm[jj + 1])%255]%8;


    tmpX = x-x0;
    tmpY = y-y0;
    s = gradient[gi0*gradientX+0] * tmpX + gradient[gi0*gradientX+1]*tmpY;

    tmpX = x-(x0+1);
    tmpY = y-y0;
    t = gradient[gi1*gradientX+0] * tmpX + gradient[gi1*gradientX+1]*tmpY;

    tmpX = x-x0;
    tmpY = y-(y0+1);
    u = gradient[gi2*gradientX+0] * tmpX + gradient[gi2*gradientX+1]*tmpY;

    tmpX = x-(x0+1);
    tmpY = y-(y0+1);
    v = gradient[gi3*gradientX+0] * tmpX + gradient[gi3*gradientX+1]*tmpY;

    tmp = x-x0;
    Cx = 3*tmp*tmp-2*tmp*tmp*tmp;

    Li1 = s + Cx * (t-s);
    Li2 = u + Cx * (v-u);

    tmp = y - y0;
    Cy = 3*tmp*tmp-2*tmp*tmp*tmp;

    return Li1 + Cy * (Li2-Li1);
}

double color_perlin(double x, double y, int resolution, int *perm, int oct,
        double freq, double pers)
{
    double r = 0.;
    double f = freq;
    double amplitude = 1.;

    for(int i = 0; i < oct; i++)
    {
        //Translation du centre de symétrie en i * 4096
        int t = i * 4096;

        //Calcul du bruit translaté
        r += perlin(x * f + t, y*f+t, resolution, perm) * amplitude;

        amplitude *= pers;
        f *= 2;
    }

    double geo_lim = (1 - pers) / (1 - amplitude);

    return r * geo_lim;
}

SDL_Surface* perlin_generate(int sizex,int sizey, int resolution)
{
    srand(time(NULL));
    SDL_Surface* image = SDL_CreateRGBSurface(0,sizex,sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    

    int perm[] = 
{151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,
 142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,
 203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,
 74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,
 105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,
 187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,
 64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,
 47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,
 153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,
 112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,
 162,241,81,51,145,235,249,14,239,107,49,192,214,31,181,199,106,157,184,
 84,204,176,115,121,50,45,127,4,150,254,138,236,205,93,222,114,67,29,24,72,
 243,141,128,195,78,66,215,61,
 156,180};


    shuffle(perm,256);
    SDL_PixelFormat* format = image->format;
    for(int y = 0; y<sizey;y++)
    {
        for(int x = 0; x<sizex; x++)
        {
            int c = (color_perlin(x,y,resolution,perm,5,2.0,0.5)+1)*0.5*255;
            pixels[y*sizey+x] = SDL_MapRGB(format,c,c,c);
        }
    }

    SDL_UnlockSurface(image);
    return image;
}


