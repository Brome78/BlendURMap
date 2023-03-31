#include "export.h"
#include <stdio.h>
#include <stdlib.h>


int export_3d_map(struct map* pmap, SDL_Surface* cmap, char* path)
{
  //TODO
  //- Get the perlin surface from the generation
  //- Get the surface and the measure of heights of pixels
  //- Create the .OBJ file
  //- Write into it with the info
  //- Don't forget to free the pointers if needed

  
  FILE* fd = fopen(path,"w");
  SDL_Surface* ps = pmap->map;

  //test

  int width = ps->w;
  int height = ps->h;

  Uint32* px = ps->pixels;
  Uint32* px2 = cmap->pixels;

  SDL_PixelFormat* format = ps->format;
  SDL_PixelFormat* format2 = cmap->format;

  for(int w = 0; w<width; w++)
  {
    for(int h = 0; h<height; h++)
    {
      Uint8 r,g,b,r2,g2,b2;
      SDL_GetRGB(px2[h * width + w], format2, &r2,&g2,&b2);
      SDL_GetRGB(px[h * width + w],format,&r,&g,&b);

      if(r<=118)
          r = 118;

      fprintf(fd,"v %d %02f %d %02f %02f %02f\n", w, ((float)r/255.0)*250.0, h, r2/255.0, g2/255.0, b2/255.0);
    }
  }

  for(float wf = 0; wf<width; wf++)
  {
      for(float hf = height; hf>0; hf--)
      {
        fprintf(fd,"vt %02f %02f\n", wf/(float)width, hf/(float)height);
      }
  }

  for(int w = 0; w<width-1; w++)
  {
    for(int h = 0; h<height-1; h++)
    {
      int calc = (w*width+h)+1;
      fprintf(fd,"f %d %d %d %d\n",calc+height, calc+height+1, calc+1, calc);
    }
  }


  return 1;
}

