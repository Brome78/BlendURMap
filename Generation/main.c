#include "Utils/utils.h"
#include "Noise/perlin.h"
#include "Color/color.h"
#include "Noise/simplex.h"
#include "Color/chunk.h"
#include "Noise/seed.h"
#include <stdlib.h>
#include <stdio.h>

int main(void)
{


    char *s = read_seed("seed");

    struct map *perlin = perlin_generate(1920,1080,500,s);
    //FILE *seed = fopen("seed","w");
    //fprintf(seed,"%s",perlin->seed);
    save_image(perlin->map,"simplex.png");
    struct map *perlin2 = perlin_generate(1920,1080,900,s);
    SDL_Surface *map = apply_biome(perlin->map, perlin2->map,
            1920,1080);


    save_image(map,"map.png");

    struct chunk **chunk_map = define_chunk(perlin->map,
            perlin2->map,1920,1080);
    //print_chunk(chunk_map, 1000,1000);
    //map = draw_riviere(map,perlin,1920,1080);
    //save_image(map,"riviere.png");
    SDL_FreeSurface(perlin->map);
    SDL_FreeSurface(map);
    return 0;
}
