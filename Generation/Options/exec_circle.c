#include <stdio.h>

#include "../Utils/utils.h"
#include "../Noise/circular_gradient.h"

void exec_circle(struct options* opt)
{
    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Circular Gradient\n");

    struct map* circ = generate_circ_gradient(opt);

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nSave Gradient\n");

    save_to_png(circ->map,"circular_gradient.png");

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");

    free(opt);
    SDL_FreeSurface(circ->map);
    free(circ);

}
