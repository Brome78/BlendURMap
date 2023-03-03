#include <stdio.h>

#include "../Utils/utils.h"
#include "../Noise/ds.h"

void exec_ds(int seed, struct options* opt)
{
    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Diamond-Square Noise\n");

    SDL_Surface* diamond_square = generate_diamond();

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nSave Noise\n");

    save_to_png(diamond_square,"diamond_square.png");

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");

    free(opt);
    SDL_FreeSurface(diamond_square);
}
