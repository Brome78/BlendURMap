#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include "Utils/utils.h"
#include "Noise/perlin.h"
#include "Color/color.h"
#include "Noise/simplex.h"
#include "Color/chunk.h"
#include "Noise/diamond_square.h"
#include "Noise/seed.h"
#include "Color/biome.h"
#include "Color/props.h"

int main(int argc, char** argv)
{
    if(argc != 2)
        errx(EXIT_FAILURE,"USAGE: ./main -perlin \n \
                   -simplex \n \
                   -diamond_square \n \
                   -map \n \
                   -perso");

    char *s = read_seed("seed");

    struct options* opt_alt = malloc(sizeof(struct options));
    opt_alt->sizex = 1920;
    opt_alt->sizey = 1080;
    opt_alt->resolution = 500;
    opt_alt->octave = 5;
    opt_alt->frequence = 2.0;
    opt_alt->persistence = 0.5;

    struct options* opt_temp = malloc(sizeof(struct options));
    opt_temp->sizex = opt_alt->sizex;
    opt_temp->sizey = opt_alt->sizey;
    opt_temp->resolution = 800;
    opt_temp->octave = 5;
    opt_temp->frequence = 2.0;
    opt_temp->persistence = 0.5;

    if(strcmp(argv[1],"-simplex") == 0)
    {
        printf("\e[1;1H\e[2J");
        printf("[            ]\nGenerate Simplex Noise\n");

        struct map* simplex = generate_simplex(s,opt_alt);

        printf("\e[1;1H\e[2J");
        printf("[//////      ]\nSave Noise\n");

        save_image(simplex->map,"simplex.bmp");
        bmp_to_png("simplex.bmp","simplex.png");

        printf("\e[1;1H\e[2J");
        printf("[////////////]\nComplete\n");

        free(opt_alt);
        free(opt_temp);
        free(simplex->seed);
        SDL_FreeSurface(simplex->map);
        free(simplex);
        return 0;
    }
    else if(strcmp(argv[1],"-perlin") == 0)
    {
        printf("\e[1;1H\e[2J");
        printf("[            ]\nGenerate Perlin Noise\n");

        struct map* perlin = perlin_generate(s,opt_alt);

        printf("\e[1;1H\e[2J");
        printf("[//////      ]\nSave Noise\n");

        save_image(perlin->map,"perlin.bmp");
        bmp_to_png("perlin.bmp","perlin.png");

        printf("\e[1;1H\e[2J");
        printf("[////////////]\nComplete\n");

        free(opt_alt);
        free(opt_temp);
        free(perlin->seed);
        SDL_FreeSurface(perlin->map);
        free(perlin);
        return 0;
    }
    else if(strcmp(argv[1],"-diamond_square") == 0)
    {
        printf("\e[1;1H\e[2J");
        printf("[            ]\nGenerate Diamond-Square Noise\n");

        struct map* diamond_square = generate_diamond_square(s,opt_alt);

        printf("\e[1;1H\e[2J");
        printf("[//////      ]\nSave Noise\n");

        save_image(diamond_square->map,"diamond_square.bmp");
        bmp_to_png("diamond_square.bmp","diamond_square.png");

        printf("\e[1;1H\e[2J");
        printf("[////////////]\nComplete\n");

        free(opt_alt);
        free(opt_temp);
        free(diamond_square->seed);
        SDL_FreeSurface(diamond_square->map);
        free(diamond_square);
        return 0;
    }

    else if(strcmp(argv[1],"-map") == 0)
    {

        printf("\e[1;1H\e[2J");
        printf("[            ]\nGenerate Perlin Noise\n");

        struct map* perlin = perlin_generate(s,opt_alt);

        printf("\e[1;1H\e[2J");
        printf("[///         ]\nGenerate Simplex Noise\n");

        struct map *simplex = generate_simplex(s,opt_temp);

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
        printf("[//////      ]\nApply Biome\n");

        SDL_Surface *map = apply_biome(perlin->map, simplex->map,
                opt_alt,t);

        printf("\e[1;1H\e[2J");
        printf("[/////////   ]\nSave Map\n");

        save_image(map,"map.bmp");
        bmp_to_png("map.bmp","map.png");

        printf("\e[1;1H\e[2J");
        printf("[////////////]\nComplete\n");

        SDL_FreeSurface(perlin->map);
        free(perlin->seed);
        free(perlin);
        free(t);

        free(opt_alt);
        free(opt_temp);
        SDL_FreeSurface(map);

        SDL_FreeSurface(simplex->map);
        free(simplex);
        return 0;
    }
    else if(strcmp(argv[1],"-perso") == 0)
    {
        char *buffer = calloc(16,sizeof(char));
        int w = 0;
        int h = 0;

        char props = 0;
        char show = 0;

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
            free(s);
            s = NULL;
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

        printf("\e[1;1H\e[2J");
        printf("[            ]\nGenerate Perlin Noise\n");

        struct map* perlin = perlin_generate(s,opt_alt);

        printf("\e[1;1H\e[2J");
        printf("[//          ]\nGenerate Simplex Noise\n");

        struct map *simplex = generate_simplex(s,opt_temp);

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

        save_image(map,"map.bmp");
        bmp_to_png("map.bmp","map.png");



        printf("\e[1;1H\e[2J");
        printf("[////////    ]\nCreate Chunks\n");

        struct chunk **chunk_map = define_chunk(perlin->map,
                simplex->map,opt_alt,t);
        if(props)
        {
            printf("\e[1;1H\e[2J");
            printf("[//////////  ]\nApply props\n");
            apply_props(map, chunk_map,opt_alt);
            save_image(map,"map_forest.bmp");
            bmp_to_png("map_forest.bmp","map_forest.png");
        }
        if(show)
        {
            printf("\e[1;1H\e[2J");
            printf("[//////////  ]\nCreate Chunk Map\n");
            show_chunk(chunk_map, map, opt_alt);
            save_image(map,"chunk.bmp");
            bmp_to_png("chunk.bmp","chunk.png");
        }

        printf("\e[1;1H\e[2J");
        printf("[////////////]\nComplete\n");

        free_chunk(chunk_map, opt_alt);
        SDL_FreeSurface(perlin->map);
        free(perlin->seed);
        free(perlin);
        free(t);

        free(opt_alt);
        free(opt_temp);
        SDL_FreeSurface(map);

        SDL_FreeSurface(simplex->map);
        free(simplex);

        free(buffer);

    }
    else
        errx(EXIT_FAILURE,"The first argument is incorrect (must be -simplex or -perlin or -map or-perso)");

    return 0;
}
