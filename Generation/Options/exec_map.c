#include <stdio.h>
#include <stdlib.h>

#include "../Utils/utils.h"
#include "../Utils/threshold.h"

#include "../Noise/perlin.h"
#include "../Noise/simplex.h"
#include "../Noise/ds.h"

#include "../Color/biome.h"

void exec_map(int seed, struct options* opt_alt, struct options* opt_temp)
{
    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Perlin Noise\n");

    struct map* perlin = perlin_generate(seed,opt_alt);

    printf("\e[1;1H\e[2J");
    printf("[///         ]\nGenerate Simplex Noise\n");

    struct map *simplex = generate_simplex(seed,opt_temp);

    struct threshold *t = default_threshold_map();

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nApply Biome\n");

    SDL_Surface *map = apply_biome(perlin->map, simplex->map,
            opt_alt,t);

    printf("\e[1;1H\e[2J");
    printf("[/////////   ]\nSave Map\n");

    save_to_png(map,"map.png");

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");

    SDL_FreeSurface(perlin->map);
    free(perlin);
    free(t);

    free(opt_alt);
    free(opt_temp);
    SDL_FreeSurface(map);

    SDL_FreeSurface(simplex->map);
    free(simplex);

}
