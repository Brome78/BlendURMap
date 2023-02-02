#include "Utils/utils.h"
#include "Noise/perlin.h"
#include "Color/color.h"
#include "Noise/simplex.h"
#include "Color/chunk.h"
#include "Noise/seed.h"
#include "Color/biome.h"
#include "Color/props.h"

#include <err.h>
#include <png.h>

#include <stdlib.h>
#include <libpng/png.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    if(argc != 3 && argc != 2)
        errx(EXIT_FAILURE,"USAGE: ./main + --perlin or --simplex + (optional) --map");

    char *s = read_seed("seed");

    if(strcmp(argv[1],"--simplex") == 0)
    {
        SDL_Surface* simplex = generate_simplex(1920,1080,500);
        save_image(simplex,"simplex.bmp");
        bmp_to_png("simplex.bmp","simplex.png");
        return 0;
    }

    struct map* perlin = perlin_generate(1920,1080,500,s);

    save_image(perlin->map,"perlin.bmp");
    struct map *perlin2 = perlin_generate(1920,1080,900,s);

    struct threshold *t = malloc(sizeof(struct threshold));
    t->deep_ocean = 90;
    t->ocean = 110;
    t->coast = 118;
    t->beach = 125;
    t->mid_mountains = 155;
    t->mountains = 160;
    t->picks = 170;
    t->plains = 140;
    t->snow = 115;
    t->savanna = 155;

    SDL_Surface *map = apply_biome(perlin->map, perlin2->map,
            1920,1080,t);

    save_image(map,"map.bmp");
    struct chunk **chunk_map = define_chunk(perlin->map,
            perlin2->map,1920,1080);

    apply_props(map, chunk_map,1920,1080);
    save_image(map,"map_forest.bmp");

    map = draw_riviere(map,perlin->map,1920,1080);
    save_image(map,"riviere.png");
    SDL_FreeSurface(perlin->map);
    SDL_FreeSurface(map);
    return 0;
}
