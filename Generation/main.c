#include "Utils/utils.h"
#include "Noise/perlin.h"
#include "Color/color.h"

int main(void)
{
    SDL_Surface *perlin = perlin_generate(20000,20000,500);
    save_image(perlin,"perlin.png");
    SDL_Surface *map = apply_biome(perlin, 20000,20000);
    save_image(map,"map.png");
    SDL_FreeSurface(perlin);
    SDL_FreeSurface(map);
    return 0;
}
