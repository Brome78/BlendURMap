#include "../Utils/utils.h"
#include "color.h"
#include "chunk.h"
#include <time.h>
#include <math.h>



int draw_tree1(SDL_Surface *map, int x, int y, int sizex, int sizey)
{
    if (x-3 < 0 || y-3 < 0 || x+3 > sizex || y+3 > sizey)
    {
        return 0;
    }

    Uint32 *pixels = map->pixels;
    SDL_LockSurface(map);

    SDL_PixelFormat* format = map->format;

    Uint32 c = log_c(format);
    Uint32 c2 = leave_c(format);

    pixels[y*sizex+x] = c;
    pixels[(y-1)*sizex+x] = c;
    pixels[(y-2)*sizex+x] = c2;
    pixels[(y-2)*sizex+x+1] = c2;
    pixels[(y-2)*sizex+x-1] = c2;

    pixels[(y-3)*sizex+x] = c2;

    return 1;
}

int draw_tree2(SDL_Surface *map, int x, int y, int sizex, int sizey)
{
    if (x-3 < 0 || y-3 < 0 || x+3 > sizex || y+3 > sizey)
    {
        return 0;
    }

    Uint32 *pixels = map->pixels;
    SDL_LockSurface(map);

    SDL_PixelFormat* format = map->format;

    Uint32 c = log2_c(format);
    Uint32 c2 = leave2_c(format);

    pixels[y*sizex+x] = c;
    pixels[(y-1)*sizex+x] = c;
    pixels[(y-2)*sizex+x] = c2;
    pixels[(y-2)*sizex+x+1] = c2;
    pixels[(y-2)*sizex+x-1] = c2;

    pixels[(y-3)*sizex+x] = c2;

    return 1;
}

int draw_pine(SDL_Surface *map, int x, int y, int sizex, int sizey)
{
    if (x-3 < 0 || y-3 < 0 || x+3 > sizex || y+3 > sizey)
    {
        return 0;
    }

    Uint32 *pixels = map->pixels;
    SDL_LockSurface(map);

    SDL_PixelFormat* format = map->format;

    Uint32 c = log_pine_c(format);
    Uint32 c2 = leave_pine_c(format);

    pixels[y*sizex+x] = c;
    pixels[(y-1)*sizex+x] = c2;
    pixels[(y-1)*sizex+x-1] = c2;
    pixels[(y-1)*sizex+x+1] = c2;

    pixels[(y-2)*sizex+x] = c2;


    pixels[(y-3)*sizex+x] = c2;

    return 1;
}

int draw_savanna_tree(SDL_Surface *map, int x, int y, int sizex, int sizey)
{
    if (x-3 < 0 || y-4 < 0 || x+3 > sizex || y+3 > sizey)
    {
        return 0;
    }

    Uint32 *pixels = map->pixels;
    SDL_LockSurface(map);

    SDL_PixelFormat* format = map->format;

    Uint32 c = log_savanna_c(format);
    Uint32 c2 = leave_savanna_c(format);

    pixels[y*sizex+x] = c;
    pixels[(y-1)*sizex+x] = c;
    pixels[(y-2)*sizex+x+1] = c;
    pixels[(y-3)*sizex+x-1] = c2;

    pixels[(y-3)*sizex+x+3] = c2;
    pixels[(y-3)*sizex+x+1] = c2;
    pixels[(y-3)*sizex+x+2] = c2;
    pixels[(y-3)*sizex+x] = c2;

    pixels[(y-4)*sizex+x+1] = c2;

    return 1;
}

int draw_bush1(SDL_Surface *map,int x, int y , int sizex, int sizey)
{
    if (x < 0 || y < 0 || x > sizex || y > sizey)
    {
        return 0;
    }

    Uint32 *pixels = map->pixels;
    SDL_LockSurface(map);

    SDL_PixelFormat* format = map->format;

    Uint32 c = bush_c(format);

    pixels[y*sizex+x] = c;
    return 1;

}

int draw_cactus(SDL_Surface *map,int x, int y , int sizex, int sizey)
{
    if (x < 0 || y-1 < 0 || x > sizex || y > sizey)
    {
        return 0;
    }

    Uint32 *pixels = map->pixels;
    SDL_LockSurface(map);

    SDL_PixelFormat* format = map->format;

    Uint32 c = leave_c(format);

    pixels[y*sizex+x] = c;
    pixels[(y-1)*sizex+x] = c;

    return 1;

}


struct type_structure** apply_props(SDL_Surface *map, struct chunk **chunk_map, struct options* opt)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;

    struct type_structure** list = malloc((sizex*sizey)*sizeof(struct type_structure*));
    int n = 0;

    srand(time(NULL));
    int chunk_sizex = sizex/16;
    if(sizex%16>0)
        chunk_sizex++;

    int chunk_sizey = sizey/16;
    if(sizey%16>0)
        chunk_sizey++;
    Uint32* pixels = map->pixels;
    SDL_PixelFormat* format = map->format;
    for(int y = 0;y<chunk_sizey;y++)
    {
        for(int x = 0; x<chunk_sizex;x++)
        {
            struct chunk *curr = chunk_map[y*chunk_sizex+x];
            if(curr->id_biome == FOREST)
            {
                for(int y2 = curr->ymin; y2 < curr->ymax; y2++)
                {
                    for(int x2 = curr->xmin; x2<curr->xmax;x2++)
                    {
                        if(rand()%100 <5 && pixels[y2*sizex+x2] == plains2(format))
                        {
                            struct type_structure* obj = malloc(sizeof(struct type_structure));
                            obj->x = x2;
                            obj->y = y2;
                            if(rand()%100<80)
                            {
                                draw_tree1(map,x2,y2,sizex,sizey);
                                obj->type = TREE;
                            }
                            else
                            {
                                draw_tree2(map,x2,y2,sizex,sizey);
                                obj->type = BIRCH;
                            }
                            list[n] = obj;
                            n++;
                        }

                    }
                }
            }
            if(curr->id_biome == PLAINS)
            {
                for(int y2 = curr->ymin; y2 < curr->ymax; y2++)
                {
                    for(int x2 = curr->xmin; x2<curr->xmax;x2++)
                    {
                        
                        if(rand()%100 <3 && pixels[y2*sizex+x2] == plains(format))
                        {
                            struct type_structure* obj = malloc(sizeof(struct type_structure));
                            obj->x = x2;
                            obj->y = y2;
                            obj->type = BUSH;
                            list[n] = obj;
                            n++;
                            draw_bush1(map,x2,y2,sizex,sizey);
                        }

                    }
                }

            }
            if(curr->id_biome == DESERT)
            {
                for(int y2 = curr->ymin; y2 < curr->ymax; y2++)
                {
                    for(int x2 = curr->xmin; x2<curr->xmax;x2++)
                    {
                        if(rand()%400 <1 && pixels[y2*sizex+x2] == desert(format))
                        {
                            struct type_structure* obj = malloc(sizeof(struct type_structure));
                            obj->x = x2;
                            obj->y = y2;
                            obj->type = CACTUS;
                            list[n] = obj;
                            n++;
                            draw_cactus(map,x2,y2,sizex,sizey);
                        }

                    }
                }

            }
            if(curr->id_biome == SAVANNA)
            {
                for(int y2 = curr->ymin; y2 < curr->ymax; y2++)
                {
                    for(int x2 = curr->xmin; x2<curr->xmax;x2++)
                    {
                        if(rand()%400 <1 && pixels[y2*sizex+x2] == savanna(format))
                        {
                            struct type_structure* obj = malloc(sizeof(struct type_structure));
                            obj->x = x2;
                            obj->y = y2;
                            obj->type = ACACIA;
                            list[n] = obj;
                            n++;
                            draw_savanna_tree(map,x2,y2,sizex,sizey);
                        }

                    }
                }

            }
            if(curr->id_biome == FREEZE_PLAINS)
            {
                for(int y2 = curr->ymin; y2 < curr->ymax; y2++)
                {
                    for(int x2 = curr->xmin; x2<curr->xmax;x2++)
                    {
                        if(rand()%400 <1 && pixels[y2*sizex+x2] == snow(format))
                        {
                            struct type_structure* obj = malloc(sizeof(struct type_structure));
                            obj->x = x2;
                            obj->y = y2;
                            obj->type = SPRUCE;
                            list[n] = obj;
                            n++;
                            draw_pine(map,x2,y2,sizex,sizey);
                        }

                    }
                }

            }
        }
    }
    return list;
}
