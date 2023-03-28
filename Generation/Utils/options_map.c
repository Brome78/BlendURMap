#include <stdlib.h>

#include "utils.h"

struct options* default_options_alt(void)
{
    struct options* opt = malloc(sizeof(struct options));
    opt->sizex = 1920;
    opt->sizey = 1080;
    opt->resolution = 500;
    opt->octave = 5;
    opt->frequence = 2.0;
    opt->persistence = 0.5;

    return opt;
}

struct options* options_alt_3d(void)
{
    struct options* opt = malloc(sizeof(struct options));
    opt->sizex = 1000;
    opt->sizey = 1000;
    opt->resolution = 500;
    opt->octave = 5;
    opt->frequence = 2.0;
    opt->persistence = 0.4;

    return opt;
}

struct options* options_temp_3d(void)
{
    struct options* opt = malloc(sizeof(struct options));
    opt->sizex = 1000;
    opt->sizey = 1000;
    opt->resolution = 700;
    opt->octave = 5;
    opt->frequence = 2.0;
    opt->persistence = 0.4;

    return opt;
}


struct options* default_options_temp(void)
{
    struct options* opt = malloc(sizeof(struct options));
    opt->sizex = 1920;
    opt->sizey = 1080;
    opt->resolution = 800;
    opt->octave = 5;
    opt->frequence = 2.0;
    opt->persistence = 0.5;

    return opt;
}
