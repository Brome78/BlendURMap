#ifndef COLOR_MINDUSTRY_H__
#define COLOR_MINDUSTRY_H__


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

Uint32 m_plains2(SDL_PixelFormat* format);
Uint32 m_plains(SDL_PixelFormat* format);

Uint32 m_desert(SDL_PixelFormat* format);
Uint32 m_desert2(SDL_PixelFormat* format);
Uint32 m_desert3(SDL_PixelFormat* format);

Uint32 m_deep_ocean(SDL_PixelFormat* format);
Uint32 m_ocean(SDL_PixelFormat* format);
Uint32 m_coast(SDL_PixelFormat* format);
Uint32 m_beach(SDL_PixelFormat* format);
Uint32 m_picks(SDL_PixelFormat* format);
Uint32 m_mountains(SDL_PixelFormat* format);
Uint32 m_mid_mountains(SDL_PixelFormat* format);
Uint32 m_plains3(SDL_PixelFormat* format);

Uint32 m_low_desert(SDL_PixelFormat* format);
Uint32 m_mid_mountains_desert(SDL_PixelFormat* format);
Uint32 m_mountains_desert(SDL_PixelFormat* format);
Uint32 m_savanna(SDL_PixelFormat* format);
Uint32 m_savanna2(SDL_PixelFormat* format);
Uint32 m_savanna3(SDL_PixelFormat* format);

Uint32 m_swamp(SDL_PixelFormat* format);
Uint32 m_swamp2(SDL_PixelFormat* format);
Uint32 m_swamp3(SDL_PixelFormat* format);

Uint32 m_snow(SDL_PixelFormat* format);
Uint32 m_snow2(SDL_PixelFormat* format);
Uint32 m_snow3(SDL_PixelFormat* format);
Uint32 m_freeze_ocean(SDL_PixelFormat* format);
Uint32 m_freeze_coast(SDL_PixelFormat* format);
Uint32 m_freeze_deep_ocean(SDL_PixelFormat* format);







#endif
