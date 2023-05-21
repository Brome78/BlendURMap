#pragma once
#include "../../Generation/Utils/utils.h"

SDL_Surface *resize_image(SDL_Surface *surface,int w2,int h2);
void resize(const char* input_image, const char* output_image, int w, int h);
