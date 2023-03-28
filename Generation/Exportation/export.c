#include "export.h"
#include <stdio.h>
#include <stdlib.h>


int export_3d_map(struct map* pmap, char* path)
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
  SDL_PixelFormat* format = ps->format;

  for(int w = 0; w<width; w++)
  {
    for(int h = 0; h<height; h++)
    {
      Uint8 r,g,b;
      SDL_GetRGB(px[h * width + w],format,&r,&g,&b);
      fprintf(fd,"v %d %02f %d\n", w, ((float)r/255.0)*250.0, h);
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
      fprintf(fd,"f %d %d %d %d\n", calc+height, calc+height+1, calc+1, calc);
    }
  }


  return 1;
}

