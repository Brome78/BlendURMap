//this should be the include to get the different biomes/pixels on the map
#ifndef EXPORT_H
#define EXPORT_H

#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../Utils/utils.h"

int export_3d_map(struct map* pmap, char *path);

#endif
