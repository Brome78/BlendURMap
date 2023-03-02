#ifndef CIRCULAR_GRADIENT_H__
#define CIRCULAR_GRADIENT_H__

#include "../Utils/utils.h"



struct map* generate_circ_gradient(struct options *opt);
void apply_island(struct map* map, struct options *opt);

#endif
