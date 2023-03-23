#include <stdio.h>

#include "../Utils/utils.h"
#include "../Noise/perlin.h"

void exec_perlin(int seed, struct options* opt, struct map* pgen)
{
    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Perlin Noise\n");

    struct map* perlin = perlin_generate(seed,opt);

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nSave Noise\n");

    save_to_png(perlin->map,"perlin.png");

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");

    pgen = perlin; //Save to a pointer to use for export

    free(opt);
    //SDL_FreeSurface(perlin->map);
    //free(perlin);

}
