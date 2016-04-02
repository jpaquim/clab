#ifndef SAMPLE_H
#define SAMPLE_H

#include <math.h>
#include <time.h>
#include "pcg_random/pcg_variants.h"
#include "pcg_random/entropy.h"
#include "matrix.h"

// initializes the random number generator
void initializeRNG(void);

// returns a number sampled uniformly between 0 and 1
scalar sample_uniform_standard(void);

// returns a number sampled uniformly between a and b
scalar sample_uniform(scalar a, scalar b);

// returns a number sampled from an exponential distribution of parameter lambda
scalar sample_exponential(scalar lambda);

#endif
