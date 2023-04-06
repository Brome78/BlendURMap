#ifndef GENERATE_H_
#define GENERATE_H_


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


void exec_ui(int seed,
                struct options* opt_alt, struct options* opt_temp, struct options* opt_hum,
                int w, int h, char rivers, char props, char structs, char shw);


#endif //GENERATE_H_
