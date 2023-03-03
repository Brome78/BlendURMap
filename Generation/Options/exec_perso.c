#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "../Utils/utils.h"
#include "../Noise/perlin.h"
#include "../Noise/simplex.h"
#include "../Noise/diamond_square.h"
#include "../Noise/seed.h"
#include "../Noise/ds.h"

#include "../Color/chunk.h"
#include "../Color/biome.h"
#include "../Color/props.h"

void exec_perso(int seed, struct options* opt_alt, struct options* opt_temp)
{

    char *buffer = calloc(16,sizeof(char));
    int w = 0;
    int h = 0;

    char props = 0;
    char show = 0;
    char print = 0;

    printf("Width : ");
    scanf("%d",&w);

    printf("Height : ");
    scanf("%d",&h);

    opt_alt->sizex = w;
    opt_alt->sizey = h;
    opt_temp->sizex = w;
    opt_temp->sizey = h;

    if(h == 0 || w == 0)
    {
        errx(EXIT_FAILURE,"Size must be higher than 0");
    }

    printf("Would you a new seed ? (Y/N)");
    scanf("%s",buffer);

    if(strcmp(buffer,"Y")==0)
    {
        seed = -1;
    }

    printf("Would you some props? (Y/N)");
    scanf("%s",buffer);

    if(strcmp(buffer, "Y")==0)
    {
        props = 1;
    }

    printf("Would you show chunks? (Y/N)");
    scanf("%s",buffer);

    if(strcmp(buffer, "Y")==0)
    {
        show = 1;
    }

    printf("Would you print chunks? (Y/N)");
    scanf("%s",buffer);

    if(strcmp(buffer, "Y")==0)
    {
        print = 1;
    }

    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Perlin Noise\n");

    struct map* perlin = perlin_generate(seed,opt_alt);

    printf("\e[1;1H\e[2J");
    printf("[//          ]\nGenerate Simplex Noise\n");

    struct map *simplex = generate_simplex(seed,opt_temp);

    struct threshold *t = malloc(sizeof(struct threshold));
    t->deep_ocean = 90;
    t->ocean = 110;
    t->coast = 118;
    t->beach = 125;
    t->mid_mountains = 155;
    t->mountains = 160;
    t->picks = 170;
    t->plains = 140;
    t->snow = 65;
    t->savanna = 155;

    printf("\e[1;1H\e[2J");
    printf("[////        ]\nApply Biome\n");

    SDL_Surface *map = apply_biome(perlin->map, simplex->map,
            opt_alt,t);

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nSave Map\n");

    save_to_png(map,"map.png");



    printf("\e[1;1H\e[2J");
    printf("[////////    ]\nCreate Chunks\n");

    struct chunk **chunk_map = define_chunk(perlin->map,
            simplex->map,opt_alt,t);
    if(props)
    {
        printf("\e[1;1H\e[2J");
        printf("[//////////  ]\nApply props\n");
        apply_props(map, chunk_map,opt_alt);

        save_to_png(map,"map_forest.png");
    }
    if(show)
    {
        printf("\e[1;1H\e[2J");
        printf("[//////////  ]\nCreate Chunk Map\n");
        show_chunk(chunk_map, map, opt_alt);

        save_to_png(map,"chunk.png");
    }

    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");
    if(print)
        print_chunk(chunk_map, opt_alt);

    free_chunk(chunk_map, opt_alt);
    SDL_FreeSurface(perlin->map);
    free(perlin);
    free(t);

    free(opt_alt);
    free(opt_temp);
    SDL_FreeSurface(map);

    SDL_FreeSurface(simplex->map);
    free(simplex);

    free(buffer);

}
