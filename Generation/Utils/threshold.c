#include <stdlib.h>

#include "utils.h"

struct threshold* default_threshold_map(void)
{
    struct threshold *t = malloc(sizeof(struct threshold));
    t->deep_ocean = 90;
    t->ocean = 110;
    t->coast = 118;
    t->beach = 125;
    t->mid_mountains = 155;
    t->mountains = 160;
    t->picks = 170;
    t->plains = 140;
    t->snow = 65;
    t->savanna = 180;
    t->plateau = 130;
    t->plateau2 = 150;
    t->plateau3 = 145;
    t->swamp = 200;
    return t;
}

struct threshold* default_threshold_island(void)
{
    struct threshold *t = malloc(sizeof(struct threshold));
    t->deep_ocean = 90;
    t->ocean = 110;
    t->coast = 118;
    t->beach = 125;
    t->mid_mountains = 155;
    t->mountains = 160;
    t->picks = 170;
    t->plains = 255;
    t->snow = 0;
    t->savanna = 0;
    t->plateau = 120;
    t->plateau2 = 140;
    t->plateau3 = 135;
    t->swamp = 255;
    return t;
}

struct threshold* threshold_continent(void)
{
    struct threshold *t = malloc(sizeof(struct threshold));
    t->deep_ocean = 0;
    t->ocean = 0;
    t->coast = 90;
    t->beach = 100;
    t->mid_mountains = 155;
    t->mountains = 160;
    t->picks = 170;
    t->plains = 140;
    t->snow = 65;
    t->savanna = 180;
    t->plateau = 120;
    t->plateau2 = 140;
    t->plateau3 = 135;
    t->swamp = 200;
    return t;
}

struct threshold* threshold_mountains(void)
{
    struct threshold *t = malloc(sizeof(struct threshold));
    t->deep_ocean = 0;
    t->ocean = 0;
    t->coast = 0;
    t->beach = 0;
    t->mid_mountains = 130;
    t->mountains = 140;
    t->picks = 150;
    t->plains = 255;
    t->snow = 0;
    t->savanna = 180;
    t->plateau = 100;
    t->plateau2 = 120;
    t->plateau3 = 115;
    t->swamp = 200;
    return t;
}
