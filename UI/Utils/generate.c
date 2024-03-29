#include "generate.h"
#include "../../Generation/Noise/circular_gradient.h"
#include "../../Generation/Exportation/export.h"


struct current_map* exec_ui(int seed,
             struct options* opt_alt, struct options* opt_temp,
             struct options* opt_hum, struct threshold* t, 
             int w, int h, char island, char continent, char mount, char rivers, 
             char props, char structs, char is_3d, char shw, char mindustry,
             GtkAdjustment* seed_adj)
{

    struct current_map* cur = malloc(sizeof(struct current_map));
    cur->opt_alt = opt_alt;
    cur->opt_hum = opt_hum;

    char *buffer = calloc(16,sizeof(char));

    char prop = 0;
    char structure = 0;
    char riv = 0;
    char show = 0;
    char print = 0;
    char isl = 0;
    char mnt = 0;

    opt_alt->sizex = w;
    opt_alt->sizey = h;
    opt_temp->sizex = w;
    opt_temp->sizey = h;

    if(h == 0 || w == 0)
    {
        errx(EXIT_FAILURE,"Size must be higher than 0");
    }
    if(rivers == 1)
        riv = 1;
    if(props == 1)
        prop = 1;

    if(structs == 1)
        structure = 1;

    if(shw == 1)
        show = 1;

    if(island == 1)
    {
        isl = 1;
        riv = 0;
        show = 0;
        print = 0;
    }
    if(mount == 1)
    {
        mnt = 1;
        riv = 0;
        show = 0;
        print = 0;
    }
    if(continent == 1)
    {
        isl = 0;
        riv = 0;
        show = 0;
        print = 0;
    }
    if(mindustry == 1)
    {
        isl = 0;
        riv = 0;
        prop = 0;
        structure = 0;
        show = 0;
        print = 0;
    }

    printf("\e[1;1H\e[2J");
    printf("[            ]\nGenerate Perlin Noise\n");

    struct map* perlin = perlin_generate(seed,opt_alt);

    gtk_adjustment_set_value(seed_adj, perlin->seed);


    printf("\e[1;1H\e[2J");
    printf("[//          ]\nGenerate Simplex Noise\n");

    struct map *simplex = perlin_generate(perlin->seed ,opt_temp);
    //struct map *simplex = generate_simplex(perlin->seed ,opt_temp);

    SDL_Surface* ds = generate_diamond(perlin->seed,opt_hum);

    //struct threshold *t;
    if(isl || mnt)
    {

        apply_island(perlin,opt_alt);
        apply_island(simplex, opt_alt);
    }


    printf("\e[1;1H\e[2J");
    printf("[////        ]\nApply Biome\n");

    SDL_Surface *map = apply_biome(perlin->map, simplex->map,ds,
            opt_alt,opt_hum,t,mindustry);
    
    cur->perlin = perlin->map;
    cur->simplex = simplex->map;
    cur->ds = ds;
    

    printf("\e[1;1H\e[2J");
    printf("[//////      ]\nSave Map\n");

    save_to_png(map,"tmp/map.png");
    //if(is_3d)
    //    export_3d_map(perlin, map,"map.OBJ");
    if(riv)
    {
        //SDL_Surface *river = draw_riviere(map,opt_alt);
        draw_riviere2(map,perlin->map,opt_alt);

        save_to_png(map,"tmp/river.png");
    }

    if(is_3d)
        export_3d_map(perlin, map,"tmp/map.OBJ");


    printf("\e[1;1H\e[2J");
    printf("[////////    ]\nCreate Chunks\n");

    struct chunk **chunk_map = define_chunk(perlin->map,
            simplex->map,opt_alt,t);


    if(prop)
    {
        printf("\e[1;1H\e[2J");
        printf("[//////////  ]\nApply props\n");
        apply_props(map, chunk_map,opt_alt);
        save_to_png(map,"tmp/map_forest.png");
    }
    if(structure)
    {
        printf("\e[1;1H\e[2J");
        printf("[//////////  ]\nApply structure\n");
        apply_village(map, chunk_map,opt_alt,10);

        save_to_png(map,"tmp/village.png");
    }
    if(show)
    {
        printf("\e[1;1H\e[2J");
        printf("[//////////  ]\nCreate Chunk Map\n");
        show_chunk(chunk_map, map, opt_alt);

        save_to_png(map,"tmp/chunk.png");
    }
    save_to_png(map,"tmp/options.png");



    printf("\e[1;1H\e[2J");
    printf("[////////////]\nComplete\n");
    if(print)
        print_chunk(chunk_map, opt_alt);

    free_chunk(chunk_map, opt_alt);
    //SDL_FreeSurface(perlin->map);
    //free(perlin);
    free(t);

    //free(opt_alt);
    free(opt_temp);
    //free(opt_hum);
    SDL_FreeSurface(map);

    //SDL_FreeSurface(simplex->map);
    //free(simplex);

    free(buffer);

    return cur;

}
