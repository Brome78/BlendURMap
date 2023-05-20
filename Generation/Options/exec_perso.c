#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "../Utils/utils.h"
#include "../Utils/threshold.h"
#include "../Noise/perlin.h"
#include "../Noise/simplex.h"
#include "../Noise/seed.h"
#include "../Noise/ds.h"

#include "../Color/chunk.h"
#include "../Color/biome.h"
#include "../Color/river.h"
#include "../Color/props.h"

#include "../Structure/village.h"

void exec_perso(int seed, struct options* opt_alt, struct options* opt_temp, 
        struct options* opt_hum)
{

    char *buffer = calloc(16,sizeof(char));
    int w = 0;
    int h = 0;

    char props = 0;
    char structure = 0;
    char riv = 0;
    char show = 0;
    char print = 0;

    printf("Width : ");
    int er = scanf("%d",&w);
    if(er<0)
        return;

    printf("Height : ");
    er = scanf("%d",&h);
    if(er<0)
        return;

    opt_alt->sizex = w;
    opt_alt->sizey = h;
    opt_temp->sizex = w;
    opt_temp->sizey = h;
    opt_hum->sizex = w;

    if(h == 0 || w == 0)
    {
        errx(EXIT_FAILURE,"Size must be higher than 0");
    }

    printf("Would you like to create a new seed ? (Y/N)");
    er = scanf("%s",buffer);
    if(er<0)
        return;

    if(strcmp(buffer,"Y")==0)
    {
        seed = -1;
    }

    printf("Would you like to have some rivers? (Y/N)");
    er = scanf("%s",buffer);
    if(er<0)
        return;

    if(strcmp(buffer, "Y")==0)
    {
        riv = 1;
    }


    printf("Would you like to have some props? (Y/N)");
    er = scanf("%s",buffer);
    if(er<0)
        return;

    if(strcmp(buffer, "Y")==0)
    {
        props = 1;
    }

    printf("Would you like to have some structure? (Y/N)");
    er = scanf("%s",buffer);
    if(er<0)
        return;

    if(strcmp(buffer, "Y")==0)
    {
        structure = 1;
    }


    printf("Would you like to show the chunks? (Y/N)");
    er = scanf("%s",buffer);
    if(er<0)
        return;

    if(strcmp(buffer, "Y")==0)
    {
        show = 1;
    }

    printf("Would you like to print the chunks? (Y/N)");
    er = scanf("%s",buffer);
    if(er<0)
        return;

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

    SDL_Surface* ds = generate_diamond(seed,opt_hum);

    struct threshold *t = default_threshold_map();

    printf("\e[1;1H\e[2J");
    printf("[////        ]\nApply Biome\n");

    SDL_Surface *map = apply_biome(perlin->map, simplex->map,ds,
            opt_alt,opt_hum,t,0);

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nSave Map\n");

    save_to_png(map,"map.png");
    if(riv)
    {
        //SDL_Surface *river = draw_riviere(map,opt_alt);
        
        draw_riviere2(map,perlin->map,opt_alt);

        save_to_png(map,"river.png");
    }

    printf("\e[1;1H\e[2J");
    printf("[////////    ]\nCreate Chunks\n");

    struct chunk **chunk_map = define_chunk(perlin->map,
            simplex->map,opt_alt,t);
    struct type_structure** props_l;
    if(props)
    {
        printf("\e[1;1H\e[2J");
        printf("[//////////  ]\nApply props\n");
        props_l = apply_props(map, chunk_map,opt_alt);
        save_to_png(map,"map_forest.png");
    }
    struct type_structure** villages;
    if(structure)
    {
        printf("\e[1;1H\e[2J");
        printf("[//////////  ]\nApply structure\n");
        villages = apply_village(map, chunk_map,opt_alt,10);

        save_to_png(map,"village.png");
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
    free(opt_hum);
    /*for(int i = 0; props_l[i] != NULL; i++) //NOT PERFECT POSSIBLE LEAK
        free(props_l[i]);
    free(props_l);
    for(int i = 0; villages[i] != NULL; i++)
        free(villages[i]);
    free(villages);*/
    SDL_FreeSurface(map);
    SDL_FreeSurface(ds);

    SDL_FreeSurface(simplex->map);
    free(simplex);

    free(buffer);
}
