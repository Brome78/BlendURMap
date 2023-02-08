#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utils/utils.h"
#include "Noise/perlin.h"
#include "Color/color.h"
#include "Noise/simplex.h"
#include "Color/chunk.h"
#include "Noise/seed.h"
#include "Color/biome.h"
#include "Color/props.h"

int main(int argc, char** argv)
{
    if(argc != 3 && argc != 2)
        errx(EXIT_FAILURE,"USAGE: ./main + -perlin or -simplex + (optional) -map");

    char *s = read_seed("seed");

    struct options* opt_alt = malloc(sizeof(struct options));
    opt_alt->sizex = 1920;
    opt_alt->sizey = 1080;
    opt_alt->resolution = 500;
    opt_alt->octave = 5;
    opt_alt->frequence = 2.0;
    opt_alt->persistence = 0.5;

    struct options* opt_temp = malloc(sizeof(struct options));
    opt_temp->sizex = 1920;
    opt_temp->sizey = 1080;
    opt_temp->resolution = 800;
    opt_temp->octave = 5;
    opt_temp->frequence = 2.0;
    opt_temp->persistence = 0.5;

    if(strcmp(argv[1],"-simplex") == 0)
    {
        struct map* simplex = generate_simplex(s,opt_alt);
        save_image(simplex->map,"simplex.bmp");
        bmp_to_png("simplex.bmp","simplex.png");
        SDL_FreeSurface(simplex->map);
    }
    else if(strcmp(argv[1],"-perlin") == 0)
    {

        struct map* perlin = perlin_generate(s,opt_alt);
        save_image(perlin->map,"perlin.bmp");
        bmp_to_png("perlin.bmp","perlin.png");
        if(strcmp(argv[2],"-map") == 0)
        {

            struct map *perlin2 = perlin_generate(s,opt_temp);

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
                    opt_alt,t);

            save_image(map,"map.bmp");
            bmp_to_png("map.bmp","map.png");
            SDL_FreeSurface(perlin->map);
            free(perlin->seed);
            free(perlin); 
            SDL_FreeSurface(perlin2->map);
            free(perlin2); 
        }
        /*else if(argc == 2)
        {
            SDL_FreeSurface(perlin->map);
            free(perlin->seed);
            free(perlin); 
        }*/
        else
        {
            errx(EXIT_FAILURE,"The 2nd argument is incorrect (must be -map)");
        }
    }
    else
        errx(EXIT_FAILURE,"The first argument is incorrect (must be -simplex or -perlin)");
    /*struct chunk **chunk_map = define_chunk(perlin->map,
            perlin2->map,opt_alt,t);

    apply_props(map, chunk_map,opt_alt);
    save_image(map,"map_forest.bmp");

    //map = draw_riviere(map,perlin->map,1920,1080);
    //save_image(map,"riviere.png");


    free_chunk(chunk_map,opt_alt);




    free(opt_alt);
    free(opt_temp);

    free(t);*/
    return 0;
}
