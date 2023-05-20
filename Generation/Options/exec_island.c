#include <stdio.h>
#include <stdlib.h>

#include "../Utils/utils.h"
#include "../Utils/threshold.h"

#include "../Noise/perlin.h"
#include "../Noise/simplex.h"
#include "../Noise/circular_gradient.h"
#include "../Noise/ds.h"

#include "../Exportation/export.h"

#include "../Color/biome.h"

void exec_island(int seed, struct options* opt_alt, struct options* opt_temp,
        struct options* opt_hum)
{
    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Perlin Noise\n");

    opt_alt->sizex = 1000;
    opt_alt->sizey = 1000;

    struct map* perlin = perlin_generate(seed,opt_alt);

    printf("\e[1;1H\e[2J");
    printf("[///         ]\nGenerate Simplex Noise\n");

    opt_temp->sizex = 1000;
    opt_temp->sizey = 1000;

    struct map *simplex = generate_simplex(seed,opt_temp);

    SDL_Surface* ds = generate_diamond(seed,opt_hum);

    apply_island(perlin,opt_alt);
    apply_island(simplex, opt_alt);

    save_to_png(perlin->map,"perlin.png");
    save_to_png(simplex->map,"simplex.png");

    struct threshold *t = default_threshold_island();

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nApply Biome\n");

    SDL_Surface *map = apply_biome(perlin->map, simplex->map, ds,
            opt_alt,opt_hum,t,0);

    printf("\e[1;1H\e[2J");
    printf("[/////////   ]\nSave Map\n");

    save_to_png(map,"island.png");
    export_3d_map(perlin,map,"island.OBJ");

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");

    SDL_FreeSurface(perlin->map);
    free(perlin);
    free(t);

    free(opt_alt);
    free(opt_temp);
    free(opt_hum);
    SDL_FreeSurface(ds);
    SDL_FreeSurface(map);

    SDL_FreeSurface(simplex->map);
    free(simplex);

}
