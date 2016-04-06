#ifndef SCALAR_H
#define SCALAR_H

// debugging macros
#include <stdio.h>
#define debug_var(f, x) do printf(#x " = " f "\n",x);   while (0)
#define debug_int(x)    do debug_var("%d",  x);         while (0)
#define debug_size_t(x) do debug_var("%lu", x);         while (0)
#define debug_float(x)  do debug_var("%g",  x);         while (0)
#define debug_ptr(x)    do printf(#x " = %p\n", (void *) x); while (0)

#include <math.h>    // for pow, atan2, etc.
#include <stdbool.h> // for bool

#define Inf INFINITY

typedef double scalar;
// typedef float scalar;
typedef bool scalar_l;

typedef scalar (*unary_function)(scalar);
typedef scalar (*binary_function)(scalar, scalar);
typedef scalar_l (*relational_function)(scalar, scalar);
typedef scalar_l (*binary_function_l)(scalar_l, scalar_l);
typedef scalar_l (*unary_function_l)(scalar_l);

// unary operations, for use with arrayfun


// binary operations, for use with bsxfun

// returns a+b
scalar plus(scalar a, scalar b);

// returns a-b
scalar minus(scalar a, scalar b);

// returns a*b
scalar times(scalar a, scalar b);

// returns a/b
scalar divide(scalar a, scalar b);

// integer division, round towards 0
scalar idivide(scalar a, scalar b);

// returns a mod b
scalar mod(scalar a, scalar b);

// returns remainder of integer division
scalar rem(scalar a, scalar b);

// returns a^b
scalar power(scalar a, scalar b);

// binary maximum of two numbers
scalar max(scalar a, scalar b);

// binary minimum of two numbers
scalar min(scalar a, scalar b);

// atan2 in degrees
scalar atan2d(scalar a, scalar b);

/**
 * Boolean functions
 */

scalar_l eq(scalar a, scalar b);
scalar_l ne(scalar a, scalar b);
scalar_l lt(scalar a, scalar b);
scalar_l le(scalar a, scalar b);
scalar_l gt(scalar a, scalar b);
scalar_l ge(scalar a, scalar b);
scalar_l or(scalar_l a, scalar_l b);
scalar_l and(scalar_l a, scalar_l b);
scalar_l xor(scalar_l a, scalar_l b);

#endif
