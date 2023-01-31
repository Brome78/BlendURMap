#include "../Utils/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include "chunk.h"
#include "color.h"




int set_biome(SDL_Surface *height, SDL_Surface *temp,
        int xmin, int xmax, int ymin, int ymax, int sizex, int sizey)
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

    if(height_med<90)
    {
        return DEEP_OCEAN;
    }
    else if(height_med<110)
    {
        return OCEAN;
    }
    else if(height_med<118)
    {
        return COAST;
    }
    else if(height_med<125)
    {
        return BEACH;
    }
    else if(height_med>=170)
    {
        return PICKS;
    }
    else if(height_med>=160)
    {
        return MOUNTAINS;
    }
    else if(height_med>=155)
    {
        return MID_MOUNTAINS;
    }
    else if(temp_med<115)
    {
        return FREEZE_PLAINS;
    }
    else if(temp_med<140)
    {
        if(height_med>=140 && height_med<155)
            return FOREST;
        return PLAINS;
    }
    else if(temp_med<155)
    {
        return SAVANNA;
    }
    else
    {
        return DESERT;
    }
}

struct chunk **define_chunk(SDL_Surface *height, SDL_Surface *temp,
        int sizex, int sizey)
{
    int chunk_sizex = sizex/16;
    if(sizex%16>0)
        chunk_sizex++;

    int chunk_sizey = sizey/16;
    if(sizey%16>0)
        chunk_sizey++;

    struct chunk **chunk_map = 
        malloc(chunk_sizex*chunk_sizey*sizeof(struct chunk*));
    
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
                    curr->ymin,curr->ymax,sizex,sizey);

            chunk_map[y*chunk_sizex+x] = curr;
        }
    }
    return chunk_map;
}

void print_chunk(struct chunk **chunk_map, int sizex, int sizey)
{
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

                default:
                    printf("BIOME = NULL\n");
            }
            printf("========================\n\n");

        }
    }
}
