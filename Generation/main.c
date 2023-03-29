#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#include "Utils/utils.h"
#include "Utils/options_map.h"
#include "Utils/threshold.h"

#include "Options/exec_simplex.h"
#include "Options/exec_perlin.h"
#include "Options/exec_circle.h"
#include "Options/exec_ds.h"
#include "Options/exec_map.h"
#include "Options/exec_island.h"
#include "Options/exec_perso.h"
#include "Options/exec_help.h"
#include "Options/exec_export.h"

#include "Exportation/export.h"

int main(int argc, char** argv)
{
    if(argc != 2)
    {
        exec_help();
        return EXIT_FAILURE;
    }

    int s = 1677768393;

    struct options* opt_alt = default_options_alt();

    struct options* opt_temp = default_options_temp();
    
    struct options* opt_hum = default_options_alt();
    opt_hum->sizex = 2049;
    opt_hum->range = 252;

    if(strcmp(argv[1],"-simplex") == 0 || strcmp(argv[1],"-s") == 0 )
    {
        exec_simplex(s,opt_alt);
        free(opt_temp);
        return 0;
    }
    else if(strcmp(argv[1],"-perlin") == 0|| strcmp(argv[1],"-p") == 0 )
    {
        exec_perlin(s,opt_alt);
        free(opt_temp);
        return 0;
    }
    else if(strcmp(argv[1],"-circle") == 0|| strcmp(argv[1],"-c") == 0 )
    {
        exec_circle(opt_alt);
        free(opt_temp);
        return 0;
    }

    else if(strcmp(argv[1],"-diamond_square") == 0
            || strcmp(argv[1],"-ds") == 0)
    {
        exec_ds(s,opt_alt);
        free(opt_temp);
        return 0;
    }

    else if(strcmp(argv[1],"-map") == 0)
    {
        exec_map(s,opt_alt,opt_temp,opt_hum);
        return 0;
    }
    else if(strcmp(argv[1],"-island") == 0|| strcmp(argv[1],"-i") == 0 )
    {
        exec_island(s,opt_alt,opt_temp);
        return 0;
    }

    else if(strcmp(argv[1],"-perso") == 0|| strcmp(argv[1],"-P") == 0 )
    {
        exec_perso(s,opt_alt,opt_temp,opt_hum);
        return 0;
    }
    else if(strcmp(argv[1],"-h") == 0)
    {
        exec_help();
        return 0;
    }
    else if (strcmp(argv[1],"-export") == 0)
    {
        exec_export(s,opt_alt,opt_temp,opt_hum);
        return 1;
    }
    else
    {
        exec_help();
        return EXIT_FAILURE;
    }

    return 0;
}
