#include <stdio.h>

#include "../Noise/simplex.h"
#include "../Utils/utils.h"

void exec_simplex(int seed, struct options* opt)
{
    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Simplex Noise\n");

    struct map* simplex = generate_simplex(seed,opt);

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nSave Noise\n");

    save_to_png(simplex->map,"simplex.png");

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");

    free(opt);
    SDL_FreeSurface(simplex->map);
    free(simplex);
}
