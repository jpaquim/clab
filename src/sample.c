#include "sample.h"

void initializeRNG(void) {
    // pcg32_srandom(42u,52u); // deterministic seed
   uint64_t seeds[2];
   entropy_getbytes((void*)seeds, sizeof(seeds));
   pcg32_srandom(seeds[0], seeds[1]);
}

scalar sample_uniform_standard(void) {
    return ldexp(pcg32_random(),-32);
//    return ldexp(pcg64_random(),-64);
}

scalar sample_uniform(scalar a, scalar b) {
    return a+(b-a)*sample_uniform_standard();
}

scalar sample_exponential(scalar lambda) {
     // simple sampling from inverse cdf
    return -log(1-sample_uniform_standard())/lambda;
}
