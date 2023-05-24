#ifndef GENERATE_H_
#define GENERATE_H_

#include <gtk/gtk.h>
#include "../../Generation/Noise/perlin.h"
#include "../../Generation/Noise/simplex.h"
#include "../../Generation/Noise/seed.h"
#include "../../Generation/Noise/ds.h"

#include "../../Generation/Color/chunk.h"
#include "../../Generation/Color/biome.h"
#include "../../Generation/Color/river.h"
#include "../../Generation/Color/props.h"

#include "../../Generation/Structure/village.h"

#include "../../Generation/Utils/threshold.h"
#include "../../Generation/Utils/utils.h"



struct current_map* exec_ui(int seed,
                struct options* opt_alt, struct options* opt_temp,
                struct options* opt_hum, struct threshold* t, 
                int w, int h,char island,char continent, char mount,
                char rivers, char props, char structs, char is_3d,
                char shw, char mindustry, GtkAdjustment* seed_adj);


#endif
