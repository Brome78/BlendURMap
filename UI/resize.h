#ifndef RESIZE_H_
#define RESIZE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

SDL_Surface *resize_image(SDL_Surface *surface, int w2, int h2);

void resize(const char* input_image, const char* output_image, int w, int h);


#endif // RESIZE_H_
