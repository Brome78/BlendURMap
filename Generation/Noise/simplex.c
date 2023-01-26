#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include "simplex.h"

static int32_t grad3[12][3] = {
    {1,1,0}, {-1,1,0}, {1,-1,0}, {-1,-1,0},
    {1,0,1}, {-1,0,1}, {1,0,-1}, {-1,0,-1},
    {0,1,1}, {0,-1,1}, {0,1,-1}, {0,-1,-1}
};

static double dot2(int32_t g[3], double x, double y) {
    return g[0]*x + g[1]*y;
}
static int32_t perm[256] = {151,160,137,91,90,15,
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
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};
double simplex_noise_2d(double x, double y) {
    // Skewing and unskewing factors
    const double F2 = 0.5 * (sqrt(3.0) - 1.0);
    const double G2 = (3.0 - sqrt(3.0)) / 6.0;

    // Skew the input space to determine which simplex cell we're in
    double s = (x + y) * F2;
    int32_t i = (int32_t)floor(x + s);
    int32_t j = (int32_t)floor(y + s);

    // Unskew the cell origin back to (x,y) space
    double t = (i + j) * G2;
    double X0 = i - t;
    double Y0 = j - t;

    // The x,y distances from the cell origin
    double x0 = x - X0;
    double y0 = y - Y0;

    // For the 2D case, the simplex shape is an equilateral triangle.
    // Determine which simplex we are in.
    int32_t i1, j1;
    if (x0 > y0) {
        i1 = 1;
        j1 = 0;
    } else {
        i1 = 0;
        j1 = 1;
    }

    // Offsets for middle corner in (i,j) unskewed coords
    double x1 = x0 - (double)i1 + G2;
    double y1 = y0 - (double)j1 + G2;

    // Offsets for last corner in (i,j) unskewed coords
    double x2 = x0 - 1.0 + 2.0 * G2;
    double y2 = y0 - 1.0 + 2.0 * G2;

    // Work out the hashed gradient indices of the three simplex corners
    int32_t ii = i & 255;
    int32_t jj = j & 255;
    int32_t gi0 = perm[ii + perm[jj]] % 12;
    int32_t gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
    int32_t gi2 = perm[ii + 1 + perm[jj + 1]] % 12;

    // Calculate the contribution from the three corners
    double n0, n1, n2;

    // Noise contributions from the three corners
    double t0 = 0.5 - x0 * x0 - y0 * y0;
    if (t0 < 0) {
        n0 = 0.0;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * dot2(grad3[gi0], x0, y0);
    }
    double t1 = 0.5 - x1 * x1 - y1 * y1;
    if (t1 < 0) {
        n1 = 0.0;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * dot2(grad3[gi1], x1, y1);
    }

    double t2 = 0.5 - x2 * x2 - y2 * y2;
    if (t2 < 0) {
        n2 = 0.0;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * dot2(grad3[gi2], x2, y2);
    }

    // Add contributions from each corner to get the final noise value.
    // The result is scaled to return values in the interval [-1,1].
    return 70.0 * (n0 + n1 + n2);
}
SDL_Surface* generate_simplex(double sizex, double sizey)
{
    SDL_Surface* image = SDL_CreateRGBSurface(0,sizex,sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    SDL_PixelFormat* format = image->format;
    for (int x = 0; x < sizex; x++) {
        for (int y = 0; y < sizey; y++) {
            double noise = simplex_noise_2d(y,x);
            int color = (int)((noise+ 1.0) * 0.5 * 255.0); 
            //color = color%255;
            pixels[x*image->w+y] = SDL_MapRGB(format,color,color,color);
        }
    }
    return image;
}
