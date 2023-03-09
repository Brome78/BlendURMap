#include "../Utils/utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

/**********************************************/
/*                  DEFAULT                   */
/**********************************************/

Uint32 deep_ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0,0,180);
}

Uint32 ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0,0,255);
}

Uint32 coast(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,25,173,232);
}

Uint32 beach(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,241,230,186);
}

Uint32 picks(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,255,255,255);
}

Uint32 mountains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,90,90,90);
}

Uint32 mid_mountains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,120,120,120);
}

Uint32 plains2(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0,102,51);
}

Uint32 plains3(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,0, 130, 0 );
}

Uint32 plains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,58, 148, 45);
}

/**********************************************/
/*                  DESERT                    */
/**********************************************/

Uint32 low_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,198, 175, 109);
}

Uint32 desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,198, 175, 109);
}
Uint32 desert3(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,188, 165, 99);
}
Uint32 desert2(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,178, 155, 89);
}

Uint32 mid_mountains_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,183, 149, 11 );
}

Uint32 mountains_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,185, 119, 14);
}

/**********************************************/
/*                  SAVANNA                   */
/**********************************************/

Uint32 savanna(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,146, 164, 90 );
}

Uint32 savanna3(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,111, 127, 68 );
}

Uint32 savanna2(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,90, 107, 48 );
}

/**********************************************/
/*                  SNOW                      */
/**********************************************/

Uint32 snow(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,214, 234, 248);
}

Uint32 snow3(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,204, 224, 238);
}

Uint32 snow2(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,194, 214, 228);
}

Uint32 freeze_ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,127, 179, 213);
}
Uint32 freeze_coast(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,169, 204, 227);
}
Uint32 freeze_deep_ocean(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,42, 128, 185);
}

/**********************************************/
/*                  RELIEF                    */
/**********************************************/

Uint32 relief_mountains(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,70, 70, 70);
}
Uint32 relief_beach(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,41, 128, 185);
}
Uint32 relief_desert(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,165,100,0);
}

/**********************************************/
/*                  PROPS                     */
/**********************************************/

Uint32 log_c(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,  120, 66, 18 );
}
Uint32 log2_c(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format, 245, 241, 209);
}
Uint32 leave_c(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format, 30, 173, 8 );
}
Uint32 leave2_c(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format, 0, 152, 73);
}
Uint32 bush_c(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,58,130,45);
}

/**********************************************/
/*                  VILLAGE                   */
/**********************************************/

Uint32 house_wall(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,118,110,78);
}

Uint32 house_roof(SDL_PixelFormat* format)
{ 
    return SDL_MapRGB(format,95,77,4);
}

Uint32 path(SDL_PixelFormat* format)
{
    return SDL_MapRGB(format,154,143,100);
}

