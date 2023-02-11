#include "../Utils/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "chunk.h"
#include "color.h"
#include "biome.h"




int set_biome(SDL_Surface *height, SDL_Surface *temp,
        int xmin, int xmax, int ymin, int ymax, struct threshold* t ,int sizex)
{
    int height_med = 0;
    int temp_med = 0;

    Uint32* height_pixels = height->pixels;
    Uint32* temp_pixels = temp->pixels;

    SDL_PixelFormat* format = height->format;
    for(int y = ymin; y<ymax; y++)
    {
        for(int x = xmin; x<xmax; x++)
        {
            Uint8 rh,gh,bh;
            Uint8 rt,gt,bt;
            SDL_GetRGB(height_pixels[y*sizex+x],format,&rh,&gh,&bh);
            SDL_GetRGB(temp_pixels[y*sizex+x],format, &rt,&gt,&bt);

            height_med+=rh;
            temp_med+=rt;
        }
    }

    height_med /= (xmax-xmin)*(ymax-ymin);
    temp_med /= (xmax-xmin)*(ymax-ymin);

    if(height_med<t->deep_ocean)
    {
        return DEEP_OCEAN;
    }
    else if(height_med<t->ocean)
    {
        return OCEAN;
    }
    else if(height_med<t->coast)
    {
        return COAST;
    }
    else if(height_med<t->beach)
    {
        return BEACH;
    }
    else if(height_med>=t->picks)
    {
        return PICKS;
    }
    else if(height_med>=t->mountains)
    {
        return MOUNTAINS;
    }
    else if(height_med>=t->mid_mountains)
    {
        return MID_MOUNTAINS;
    }
    else if(temp_med<t->snow)
    {
        return FREEZE_PLAINS;
    }
    else if(temp_med<t->plains)
    {
        if(height_med>=t->plains && height_med<t->savanna)
            return FOREST;
        return PLAINS;
    }
    else if(temp_med<t->savanna)
    {
        return SAVANNA;
    }
    else
    {
        return DESERT;
    }
}

struct chunk **define_chunk(SDL_Surface *height, SDL_Surface *temp,
        struct options* opt, struct threshold* t)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;


    int chunk_sizex = sizex/16;
    if(sizex%16>0)
        chunk_sizex++;

    int chunk_sizey = sizey/16;
    if(sizey%16>0)
        chunk_sizey++;

    struct chunk **chunk_map = 
        malloc(chunk_sizex*chunk_sizey*sizeof(struct chunk*));
    if(chunk_map == 0)
        return NULL;
    
    for(int y = 0; y < chunk_sizey; y++)
    {
        for(int x = 0; x<chunk_sizex;x++)
        {
            struct chunk* curr = malloc(sizeof(struct chunk));

            curr->xmin = x*16;
            curr->ymin = y*16;

            if(x==chunk_sizex-1)
                curr->xmax = sizex;
            else
                curr->xmax = (x+1)*16;

            if(y==chunk_sizey-1)
                curr->ymax = sizey;
            else
                curr->ymax = (y+1)*16;

            curr->id_biome = set_biome(height, temp,curr->xmin,curr->xmax,
                    curr->ymin,curr->ymax,t,sizex);

            chunk_map[y*chunk_sizex+x] = curr;
        }
    }
    return chunk_map;
}

void free_chunk(struct chunk **chunk_map,struct options* opt)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;

    int chunk_sizex = sizex/16;
    if(sizex%16>0)
        chunk_sizex++;

    int chunk_sizey = sizey/16;
    if(sizey%16>0)
        chunk_sizey++;


    for(int i = 0;i<chunk_sizex*chunk_sizey;i++)
    {
        free(chunk_map[i]);
    }
    free(chunk_map);
}

void show_chunk(struct chunk **chunk_map, SDL_Surface* map, 
        struct options* opt)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;

    int chunk_sizex = sizex/16;
    if(sizex%16>0)
        chunk_sizex++;

    int chunk_sizey = sizey/16;
    if(sizey%16>0)
        chunk_sizey++;
    SDL_PixelFormat* format = map->format;
    Uint32* pixels = map->pixels;

    SDL_LockSurface(map);

    for(int y = 0;y<chunk_sizey; y++)
    {
        for(int x = 0; x<chunk_sizex;x++)
        {
            struct chunk* c = chunk_map[y*chunk_sizex+x];
            for(int y2 = c->ymin; y2<c->ymax;y2++)
            {
                for(int x2 = c->xmin; x2<c->xmax; x2++)
                {
                    if(x2 == c->xmin || x2 == c->xmax || y2 == c->ymin 
                            || y2 == c->ymax)
                    {
                        pixels[y2*sizex+x2] = SDL_MapRGB(format, 255,0,0);
                    }
                }
            }
        }
    }
    SDL_UnlockSurface(map);
}
    



void print_chunk(struct chunk **chunk_map, struct options* opt)
{
    int sizex = opt->sizex;
    int sizey = opt->sizey;


    if (chunk_map == NULL)
        return;
    int chunk_sizex = sizex/16;
    if(sizex%16>0)
        chunk_sizex++;

    int chunk_sizey = sizey/16;
    if(sizey%16>0)
        chunk_sizey++;

    printf("MAP = %d CHUNK_X\n",chunk_sizex);
    printf("MAP = %d CHUNK_Y\n\n",chunk_sizey);

    for(int y = 0; y < chunk_sizey; y++)
    {
        for(int x = 0; x<chunk_sizex;x++)
        {
            struct chunk* curr = chunk_map[y*chunk_sizex+x];

            printf("=======CHUNK %d/%d=======\n",x,y);
            printf("X_MIN = %d, X_MAX = %d\n", curr->xmin, curr->xmax);
            printf("Y_MIN = %d, Y_MAX = %d\n", curr->ymin, curr->ymax);
            switch(curr->id_biome)
            {
                case PLAINS:
                    printf("BIOME = PLAIN\n");
                    break;
                case DEEP_OCEAN:
                    printf("BIOME = DEEP_OCEAN\n");
                    break;
                case OCEAN:
                    printf("BIOME = OCEAN\n");
                    break;
                case COAST:
                    printf("BIOME = COAST\n");
                    break;
                case MID_MOUNTAINS:
                    printf("BIOME = MID_MOUNTAINS\n");
                    break;
                case MOUNTAINS:
                    printf("BIOME = MOUNTAINS\n");
                    break;
                case PICKS:
                    printf("BIOME = PICKS\n");
                    break;
                case DESERT:
                    printf("BIOME = DESERT\n");
                    break;
                case FREEZE_PLAINS:
                    printf("BIOME = FREEZE_PLAINS\n");
                    break;
                case SAVANNA:
                    printf("BIOME = SAVANNA\n");
                    break;
                case BEACH:
                    printf("BIOME = BEACH\n");
                    break;
                case FOREST:
                    printf("BIOME = FOREST\n");
                    break;
                default:
                    printf("BIOME = NULL\n");
            }
            printf("========================\n\n");

        }
    }
}
