#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "../Utils/utils.h"
#include "diamond_square.h"

#define M_PI 3.14159265358979323846

int _perm[256] = {151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
};


/*double interpolate(double a, double b, double x)
{
    double ft = x * M_PI;
    double f = (1.0 - cos(ft)) * 0.5;
    return a * (1.0 - f) + b * f;
}*/


char* shuffle_diam(int *_perm, int size, char *seed)
{
    char* n_seed;
    if(seed == NULL)
    {
        n_seed = malloc(size*sizeof(char));
        n_seed[0] = 1;
        n_seed[1] = 1;
    }
    int n = size - 1;
    while(n > 1)
    {
        int k = 0;
        if(seed == NULL)
        {
            char c = rand()%size;
            if(c < 0)
                c = -c;
            if(c == 0 && c == '\n')
                c++;
            n_seed[n] = c;
            k = c;
            if(k < 0)
                k = -k;
        }
        else
        {
            k = (int)seed[n];
            if(k < 0)
                k = -k;
        }
        n--;
        int tmp = _perm[n];
        _perm[n] = _perm[k];
        _perm[k] = tmp;
    }
    if(seed == NULL)
        return n_seed;
    return seed;
}


/*double diamond_square(double x, double y, int* resolution, int* _perm) 
{
    double scale = 1.0 / (double)(1 << *resolution);
    int step = 1 << *resolution;
    double r = 0.5 * scale;
    // double h = 0.5 * scale;
    double z = 0.0;
    
    // Diamond step
    for (int i = step; i <= SIZE - step; i += step) 
    {
        for (int j = step; j <= SIZE - step; j += step) 
        {
            double a = heights[i-step][j-step];
            double b = heights[i+step][j-step];
            double c = heights[i-step][j+step];
            double d = heights[i+step][j+step];
            double e = (a + b + c + d) * 0.25 + r * (_perm[SIZE*(i/step) + j/step] - 0.5);
            heights[i][j] = e;
        }
    }
    
    // Square step
    for (int i = 0; i <= SIZE; i += step) {
        for (int j = (i+step) % (2*step); j <= SIZE; j += 2*step) 
        {
            double a = (i-step < 0) ? 0.0 : heights[i-step][j];
            double b = (i+step > SIZE) ? 0.0 : heights[i+step][j];
            double c = (j-step < 0) ? 0.0 : heights[i][j-step];
            double d = (j+step > SIZE) ? 0.0 : heights[i][j+step];
            double e = (a + b + c + d) * 0.25 + r * (_perm[SIZE*i + j] - 0.5);
            heights[i][j] = e;
        }
    }
    
    // Update values outside the grid (wrapping)
    for (int i = 0; i < SIZE; i += step) 
    {
        heights[0][i] = heights[SIZE][i];
        heights[i][0] = heights[i][SIZE];
    }
    heights[0][0] = 0.5 * (heights[0][step] + heights[step][0]);
    heights[SIZE][0] = 0.5 * (heights[SIZE-step][0] + heights[SIZE][step]);
    heights[0][SIZE] = 0.5 * (heights[step][SIZE] + heights[0][SIZE-step]);
    heights[SIZE][SIZE] = 0.5 * (heights[SIZE-step][SIZE] + heights[SIZE][SIZE-step]);

    // Return height at given coordinates
    int ix = (int)(x / scale);
    int iy = (int)(y / scale);
    double dx = x / scale - ix;
    double dy = y / scale - iy;
    double h1 = heights[ix][iy] * (1.0 - dx) + heights[ix+step][iy] * dx;
    double h2 = heights[ix][iy+step] * (1.0 - dx) + heights[ix+step][iy+step] * dx;
    z = h1 * (1.0 - dy) + h2 * dy;
    return z;
}*/

// Fonction de bruit aléatoire 2D
double noise2d(int x, int y) 
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

double diamond_square(double x, double y, int* _perm, double* resolution)
{
    int intX = (int)x;
    int intY = (int)y;
    double fracX = x - intX;
    double fracY = y - intY;
    double TL, TR, BL, BR;
    int step = *resolution;
    if (step > 1)
    {
        double halfStep = step / 2.0;
        TL = diamond_square(intX, intY, _perm, &halfStep);
        TR = diamond_square(intX + step, intY, _perm, &halfStep);
        BL = diamond_square(intX, intY + step, _perm, &halfStep);
        BR = diamond_square(intX + step, intY + step, _perm, &halfStep);
    }
    else
    {
        TL = noise2d(intX, intY);
        TR = noise2d(intX + step, intY);
        BL = noise2d(intX, intY + step);
        BR = noise2d(intX + step, intY + step);
    }

    double top = TL + TR;
    double left = TL + BL;
    double center = TL + TR + BL + BR;

    double result = 0.0;
    int count = 0;

    if (intX % step == 0 && intY % step == 0)
    {
        result += center / 4.0;
        count++;
    }

    if (intY % step == 0 && fracX == 0)
    {
        result += top / 2.0;
        count++;
    }

    if (intX % step == 0 && fracY == 0)
    {
        result += left / 2.0;
        count++;
    }

    if (fracX == 0 && fracY == 0)
    {
        result += center / 4.0;
        count++;
    }

    if (count == 0)
    {
        result += center / 4.0;
        count++;
    }

    result /= count;

    return result;
}


struct map* generate_diamond_square(char* seed, struct options *opt)
{
    srand(time(NULL));
    SDL_Surface* image = SDL_CreateRGBSurface(0, opt->sizex, opt->sizey, 32, 0, 0, 0, 0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    
    char* n_seed = shuffle_diam(_perm, 256, seed);
    SDL_PixelFormat* format = image->format;
    for (int y = 0; y < opt->sizey; y++)
    {
        for (int x = 0; x < opt->sizex; x++)
        {
            int c = (diamond_square(x, y, _perm, (double*)(&opt->resolution)) + 1) * 0.5 * 255;
            pixels[y * opt->sizex + x] = SDL_MapRGB(format, c, c, c);
        }
    }

    SDL_UnlockSurface(image);
    struct map* map = malloc(sizeof(struct map));
    map->map = image;
    map->seed = n_seed;
    
    return map;
}