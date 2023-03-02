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


void shuffle_diam(int *perm, int size)
{
    int n = size - 1;
    while(n>1)
    {
        int k = 0;
        char c = rand()%size;
        if(c<0)
            c = -c;
        k = c;
        if(k<0)
            k = -k;
        n--;
        int tmp = perm[n];
        perm[n] = perm[k];
        perm[k] = tmp;
    }
}
// 2D random noise function
double noise2d(int x, int y) 
{
    int n = x + y * 57;
    n = (n << 13) ^ n;
    return (1.0 - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0);
}

// coordinates (x,y) of a point 
// array _perm containing a random integers permutation
// resolution which defines the size of the grid on which the function is applied
double diamond_square(double x, double y, int* _perm, double* resolution)
{
    int intX = (int)x;
    int intY = (int)y;
    double fracX = x - intX;
    double fracY = y - intY;
    double TL, TR, BL, BR;
    int step = *resolution;

    // If the resolution is > 1, the function recursively calls the diamond_square function on 
    // 4 points (TL, TR, BL, BR) which are located at the corners of a square of size step, 
    // and whose coordinates are calculated as a function of the initial position (intX, intY) and the grid size 
    // The grid size for recursive calls is divided by 2 at each call to obtain a finer resolution
    if (step > 1)
    {
        double halfStep = step / 2.0;
        TL = diamond_square(intX, intY, _perm, &halfStep);
        TR = diamond_square(intX + step, intY, _perm, &halfStep);
        BL = diamond_square(intX, intY + step, _perm, &halfStep);
        BR = diamond_square(intX + step, intY + step, _perm, &halfStep);
    }
    // If resolution == 1, i.e. the grid is reduced to one point, the function 
    // uses the noise2d function to calculate the noise value for each corner of the square
    else
    {
        TL = noise2d(intX, intY);
        TR = noise2d(intX + step, intY);
        BL = noise2d(intX, intY + step);
        BR = noise2d(intX + step, intY + step);
    }

    // Calculates the sum of the values of the top corners (TL and TR), 
    // the left corners (TL and BL), and all the corners (TL, TR, BL, BR) to find the center
    double top = TL + TR;
    double left = TL + BL;
    double center = TL + TR + BL + BR;

    double result = 0.0;
    int count = 0;

    // Calculates the average of the corner values according to the position 
    // of the point (x,y) in the grid. It checks whether the point is located on an edge 
    // or a corner of the grid, and adds the average value accordingly
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

    // If none of the special cases is satisfied, the function uses 
    // the value of the center to calculate the avg
    if (count == 0)
    {
        result += center / 4.0;
        count++;
    }

    result /= count;

    // returns the calculated average value
    return result;
}


struct map* generate_diamond_square(int seed, struct options *opt)
{
    int tmp;

    if(seed == -1)
        tmp = time(NULL);
    else
        tmp = seed;
    srand(tmp);
    SDL_Surface* image = SDL_CreateRGBSurface(0, opt->sizex, opt->sizey, 32, 0, 0, 0, 0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    
    shuffle_diam(_perm, 256);
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
    map->seed = tmp;
    
    return map;
}
