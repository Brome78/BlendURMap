#include <stdlib.h>
#include <stdio.h>

#include "../Color/color.h"
#include "../Utils/utils.h"

struct structure* house(void)
{
    struct structure* s = malloc(sizeof(struct structure));

    s->sizex = 3;
    s->sizey = 2;


    SDL_Surface* image = SDL_CreateRGBSurface(0,s->sizex,s->sizey,32,0,0,0,0);
    SDL_LockSurface(image);
    Uint32* pixels = image->pixels;
    SDL_PixelFormat* format = image->format;

    pixels[0*s->sizex+1] = house_roof(format);
    pixels[1*s->sizex+0] = house_roof(format);
    pixels[1*s->sizex+1] = house_wall(format);
    pixels[1*s->sizex+2] = house_roof(format);

    SDL_UnlockSurface(image);
    s->scheme=image;

    return s;
}

void draw_house(SDL_Surface* map, struct options* opt, int x1, int y1)
{
    Uint32* pixels = map->pixels;
    SDL_PixelFormat* format = map->format;
    struct structure* h = house();
    Uint32* pixH = h->scheme->pixels;
    SDL_LockSurface(map);
    SDL_LockSurface(h->scheme);
    int x0 = x1;
    int y0 = y1;

    for(int y = 0; y<h->sizey;y++)
    {
        x0 = x1;
        for(int x = 0; x<h->sizex;x++)
        {
            Uint8 r,g,b;
            SDL_GetRGB(pixH[y*h->sizex+x],format,&r,&g,&b);
            if(r>0)
            {
                pixels[y0*opt->sizex+x0] = pixH[y*h->sizex+x];
            }
            x0++;
        }
        y0++;
    }

    SDL_UnlockSurface(map);
    SDL_UnlockSurface(h->scheme);

}

void draw_path(SDL_Surface* map, struct options* opt, int x1, int y1,
        struct vector2* dir)
{
    Uint32* pixels = map->pixels;
    SDL_PixelFormat* format = map->format;
    SDL_LockSurface(map);

    for(int i = 0; i<4;i++)
    {
        if(pixels[(y1+(dir->y*i))*opt->sizex + x1 +(dir->x*i)]
                != house_roof(format))
            pixels[(y1+(dir->y*i))*opt->sizex+x1+(dir->x*i)] = path(format);
    }

    SDL_UnlockSurface(map);

}

void generate_village(SDL_Surface* map, int x, int y, struct options* opt,
        int nmb)
{
    Uint32* pixels = map->pixels;
    SDL_PixelFormat* format = map->format;
    if(nmb == 0)
        return;
    if(pixels[y*opt->sizex + x] != plains(format))
        return;

    struct vector2* dir = malloc(sizeof(struct vector2));

    int sizex = opt->sizex;
    int sizey = opt->sizey;

    int r = rand()%50;
    if (r<0)
        r = -r;

    dir->x = 1;
    dir->y = 0;

    if(r<10 && x+4 < sizex)
    {
        
        draw_house(map,opt,x,y);
        generate_village(map,x+4,y,opt,nmb-1);
    }
    if(r<20 && x+4 < sizex)
    {
        draw_path(map,opt,x,y,dir);
        generate_village(map,x+4,y,opt,nmb-1);
    }

    r = rand()%50;
    if(r<0)
        r = -r;

    dir->x = -1;
    dir->y = 0;

    if(r<10 && x-4 > 0)
    {
        draw_house(map,opt,x,y);
        generate_village(map,x-4,y,opt,nmb-1);
    }
    if(r<20 && x-4 > 0)
    {
        draw_path(map,opt,x,y,dir);
        generate_village(map,x-4,y,opt,nmb-1);
    }

    r = rand()%50;
    if(r<0)
        r = -r;

    dir->x = 0;
    dir->y = 1;

    if(r<10 && y+4 < sizey)
    {
        draw_house(map,opt,x,y);
        generate_village(map,x,y+4,opt,nmb-1);
    }
    if(r<20 && y+4 < sizey)
    {
        draw_path(map,opt,x,y,dir);
        generate_village(map,x,y+4,opt,nmb-1);
    }

    r = rand()%50;
    if(r<0)
        r = -r;

    dir->x = 0;
    dir->y = -1;

    if(r<10 && y-4 > 0)
    {
        draw_house(map,opt,x,y);
        generate_village(map,x,y-4,opt,nmb-1);
    }
    if(r<20 && y-4 > 0)
    {
        draw_path(map,opt,x,y,dir);
        generate_village(map,x,y-4,opt,nmb-1);
    }
    free(dir);
    return;
}

struct type_structure** apply_village(SDL_Surface* map, struct chunk **chunk_map,
        struct options* opt,int nmb)
{
    /*draw_house(map,opt,400,100);
      draw_house(map,opt,404,100);
      draw_house(map,opt,408,100);
      draw_house(map,opt,412,100);
      draw_house(map,opt,414,103);

      struct vector2* dir = malloc(sizeof(struct vector2));
      dir->x = 1;
      dir->y = 0;

      draw_path(map,opt,400,102,dir);


      draw_path(map,opt,404,102,dir);


      draw_path(map,opt,408,102,dir);


      draw_path(map,opt,412,102,dir);

      draw_path(map,opt,412,105,dir);
      dir->x = 0;
      dir->y = 1;

      draw_path(map,opt,412,102,dir);*/
    int sizex = opt->sizex;
    int sizey = opt->sizey;
    int chunk_sizex = sizex/16;

    struct type_structure** list = malloc(nmb*sizeof(struct type_structure*));
    int n = 0;

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
            if(curr->id_biome == PLAINS)
            {
                for(int y2 = curr->ymin; y2 < curr->ymax; y2++)
                {
                    for(int x2 = curr->xmin; x2<curr->xmax;x2++)
                    {
                        int r = rand()%10000;
                        if(r<0)
                            r = -r;
                        if(r < 1 && nmb > 0 && pixels[y2*sizex+x2] == plains(format))
                        {
                            printf("launch village %d / %d\n",x2,y2);
                            generate_village(map, x2, y2, opt, 10);
                            struct type_structure* obj = malloc(sizeof(struct type_structure));
                            obj->x = x2;
                            obj->y = y2;
                            obj->type = SPRUCE;
                            list[n] = obj;
                            n++;
                            nmb--;
                        }
                        

                    }
                }
            }

        }
    }
    return list;
}
