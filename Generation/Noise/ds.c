#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL_image.h>
#include "../Utils/utils.h"
#define SIZE 2049 // Change this value to adjust grid size
#define RANGE 252 // Change this value to adjust random range

void diamondSquare(int n, int **grid) {
    int side = n - 1;
    int half;
    int rand_range = RANGE;

    while (side > 1) {
        half = side / 2;

        for (int x = 0; x < n - 1; x += side) {
            for (int y = 0; y < n - 1; y += side) {
                int avg = (grid[x][y] + grid[x + side][y] +
                        grid[x][y + side] + grid[x + side][y + side]) / 4;
                grid[x + half][y + half] = avg + rand() % (rand_range * 2 + 1) - rand_range;
            }
        }

        for (int x = 0; x < n - 1; x += half) {
            for (int y = (x + half) % side; y < n - 1; y += side) {
                int avg = 0;
                int count = 0;
                if (x >= half) {
                    avg += grid[x - half][y];
                    count++;
                }
                if (x + half < n - 1) {
                    avg += grid[x + half][y];
                    count++;
                }
                if (y >= half) {
                    avg += grid[x][y - half];
                    count++;
                }
                if (y + half < n - 1) {
                    avg += grid[x][y + half];
                    count++;
                }
                grid[x][y] = avg / count + rand() % (rand_range * 2 + 1) - rand_range;
            }
        }

        side /= 2;
        rand_range /= 2;
    }
}

SDL_Surface* generate_diamond(void) {
    int **grid = calloc(SIZE, sizeof(int *));
    for (int i = 0; i < SIZE; i++) {
        grid[i] = calloc(SIZE, sizeof(int));
    }

    srand(time(NULL));

    grid[0][0] = rand() % (RANGE + 1);
    grid[0][SIZE-1] = rand() % (RANGE + 1);
    grid[SIZE-1][0] = rand() % (RANGE + 1);
    grid[SIZE-1][SIZE-1] = rand() % (RANGE + 1);

    diamondSquare(SIZE, grid);

   
    SDL_Surface* image = SDL_CreateRGBSurface(0,SIZE,SIZE,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    SDL_PixelFormat* format = image->format;
    for (int x = 0; x < SIZE; x++) {
        for (int y = 0; y < SIZE; y++) {
            int color = grid[x][y];
            color +=1;
            if(color < 0)
                color = -color;
            pixels[y*image->w+x] = SDL_MapRGB(format,color,color,color);
        }   
    }
    for (int i = 0; i < SIZE; i++) {
        free(grid[i]);
    }
    free(grid);

    return image;
}
