#ifndef COLOR_H__
#define COLOR_H__


#include "../Utils/utils.h"

#define DEEP_OCEAN 1
#define OCEAN 2
#define COAST 3
#define PLAINS 4
#define MID_MOUNTAINS 5
#define MOUNTAINS 6
#define PICKS 7
#define DESERT 8
#define SAVANNA 9
#define FREEZE_PLAINS 10
#define BEACH 11
#define FOREST 12

Uint32 plains2(SDL_PixelFormat* format);
Uint32 plains(SDL_PixelFormat* format);

Uint32 desert(SDL_PixelFormat* format);
Uint32 desert2(SDL_PixelFormat* format);
Uint32 desert3(SDL_PixelFormat* format);

Uint32 deep_ocean(SDL_PixelFormat* format);
Uint32 ocean(SDL_PixelFormat* format);
Uint32 coast(SDL_PixelFormat* format);
Uint32 beach(SDL_PixelFormat* format);
Uint32 picks(SDL_PixelFormat* format);
Uint32 mountains(SDL_PixelFormat* format);
Uint32 mid_mountains(SDL_PixelFormat* format);
Uint32 plains3(SDL_PixelFormat* format);

Uint32 low_desert(SDL_PixelFormat* format);
Uint32 mid_mountains_desert(SDL_PixelFormat* format);
Uint32 mountains_desert(SDL_PixelFormat* format);
Uint32 savanna(SDL_PixelFormat* format);
Uint32 savanna2(SDL_PixelFormat* format);
Uint32 savanna3(SDL_PixelFormat* format);

Uint32 snow(SDL_PixelFormat* format);
Uint32 snow2(SDL_PixelFormat* format);
Uint32 snow3(SDL_PixelFormat* format);
Uint32 freeze_ocean(SDL_PixelFormat* format);
Uint32 freeze_coast(SDL_PixelFormat* format);
Uint32 freeze_deep_ocean(SDL_PixelFormat* format);

Uint32 relief_mountains(SDL_PixelFormat* format);
Uint32 relief_beach(SDL_PixelFormat* format);
Uint32 relief_desert(SDL_PixelFormat* format);

Uint32 log_c(SDL_PixelFormat* format);
Uint32 leave_c(SDL_PixelFormat* format);
Uint32 log2_c(SDL_PixelFormat* format);
Uint32 leave2_c(SDL_PixelFormat* format);
Uint32 bush_c(SDL_PixelFormat* format);



Uint32 house_wall(SDL_PixelFormat* format);
Uint32 house_roof(SDL_PixelFormat* format);
Uint32 path(SDL_PixelFormat* format);


#endif
