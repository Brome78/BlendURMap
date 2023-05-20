#include <stdio.h>
#include <stdlib.h>

#include "../Utils/utils.h"
#include "../Utils/threshold.h"

#include "../Noise/perlin.h"
#include "../Noise/simplex.h"
#include "../Noise/ds.h"

#include "../Color/biome.h"
#include "../Color/river.h"


void exec_map(int seed, struct options* opt_alt, struct options* opt_temp, 
        struct options* opt_hum)
{
    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Perlin Noise\n");

    struct map* perlin = perlin_generate(seed,opt_alt);

    printf("\e[1;1H\e[2J");
    printf("[///         ]\nGenerate Simplex Noise\n");

    struct map *simplex = generate_simplex(seed,opt_temp);

    SDL_Surface* ds = generate_diamond(seed,opt_hum);

    struct threshold *t = default_threshold_map();

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nApply Biome\n");

    SDL_Surface *map = apply_biome(perlin->map, simplex->map, ds,
            opt_alt, opt_hum,t,0);


    printf("\e[1;1H\e[2J");
    printf("[/////////   ]\nSave Map\n");

    save_to_png(ds,"ds.png");

    save_to_png(map,"map.png"); 

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");

    SDL_FreeSurface(perlin->map);
    free(perlin);
    free(t);

    free(opt_alt);
    free(opt_temp);
    free(opt_hum);
    SDL_FreeSurface(map);
    SDL_FreeSurface(ds);

    SDL_FreeSurface(simplex->map);
    free(simplex);

}
