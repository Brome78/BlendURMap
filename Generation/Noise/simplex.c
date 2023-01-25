#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "../Utils/utils.h"
static int grad2[8][2] = 
{
    {1,1}, {-1,1}, {1,-1}, {-1,-1},
    {1,0}, {-1,0}, {0,1}, {0,-1}
};
int perm[256] = {151,160,137,91,90,15,
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

static double dot2(int g[2], double x, double y) {
    return g[0]*x + g[1]*y;
}

void randomizePermArray(int perm[256]) {
    for (int i = 0; i < 256; i++) {
        perm[i] = rand() % 256;
    }
}
double simplex_noise_2d(double x, double y) {
    // Skew the input space to determine which simplex cell we're in
    double s = (x + y) * 0.36602540378443864676372317075294; // (sqrt(3)-1)/2
    int i = floor(x + s);
    int j = floor(y + s);

    // Unskew the cell origin back to (x,y) space
    double t = (i + j) * 0.21132486540518711774542560974902; // 0.5 * (sqrt(3)-1)
    double X0 = i - t;
    double Y0 = j - t;

    // Calculate the position of the point relative to the cell origin
    double x0 = x - X0;
    double y0 = y - Y0;

    // Compute the dot product of the point and all eight corners of the simplex
    int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
    if (x0 > y0) {
        i1 = 1;
        j1 = 0;
    } else {
        i1 = 0;
        j1 = 1;
    }

    // Work out the hashed gradient indices of the three simplex corners
    int ii = i & 255;
    int jj = j & 255;
    int gi0 = perm[ii + perm[jj]] % 8;
    int gi1 = perm[ii + i1 + perm[jj + j1]] % 8;
    int gi2 = perm[ii + 1 + perm[jj + 1]] % 8;

    // Calculate the contribution from the three corners
    double n0, n1, n2;
    double t0 = 0.5 - x0*x0-y0*y0;
    if (t0 < 0) {
        n0 = 0;
    } else {
        t0 *= t0;
        n0 = t0 * t0 * dot2(grad2[gi0], x0, y0);
    }
    double t1 = 0.5 - x0*x0-y0*y0;
    if (t1 < 0) {
        n1 = 0;
    } else {
        t1 *= t1;
        n1 = t1 * t1 * dot2(grad2[gi1], x0 - i1 + 0.21132486540518711774542560974902, y0 - j1 + 0.21132486540518711774542560974902);
    }
    double t2 = 0.5 - x0*x0-y0*y0;
    if (t2 < 0) {
        n2 = 0;
    } else {
        t2 *= t2;
        n2 = t2 * t2 * dot2(grad2[gi2], x0 - 1.0 + 0.21132486540518711774542560974902, y0- 1.0 + 0.21132486540518711774542560974902);
    }
   return 70.0 * (n1 + n2 + n0);
}

SDL_Surface* generate_simplex(int sizex,int sizey)
{
    srand(time(NULL));
    SDL_Surface* image = SDL_CreateRGBSurface(0,sizex,sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    randomizePermArray(perm);
    SDL_PixelFormat* format = image->format;
    for (int x = 0; x < sizex; x++) {
        for (int y = 0; y < sizey; y++) {
            double noise = simplex_noise_2d((double)x / sizex, (double)y / sizey);
            int color = (int)((noise + 1.0) * 128.0);
            pixels[y*sizey+x] = SDL_MapRGB(format,color,color,color);
        }
    }
    SDL_UnlockSurface(image);
    return image;
}


