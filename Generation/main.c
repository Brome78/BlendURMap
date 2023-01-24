#include "Utils/utils.h"
#include "Noise/perlin.h"
#include "Color/color.h"

int main(void)
{
    SDL_Surface *perlin = generate(1000,1000,500);
    save_image(perlin,"perlin.png");
    SDL_Surface *map = apply_biome(perlin, 1000,1000);
    save_image(map,"map.png");
    SDL_FreeSurface(perlin);
    SDL_FreeSurface(map);
    return 0;
}
